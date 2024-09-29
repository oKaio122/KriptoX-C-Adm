#include "kutils.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-function-declaration"
int main(){
    setlocale(LC_ALL, "portuguese");

    User usuarios[10];
    Cotacoes cotacao;
    int pos;
    int opcao;


    // Carrega os usuários na variável usuarios
    carregar_usuarios(usuarios, &pos, &cotacao);

    // Coloca o preço padrão nas cotações se os valores estiverem como 0.0
    iniciar_cotacoes(&cotacao);

    // Menu Principal
    do{
        // Limpar Console
        system("cls||clear");

        mostrar_menu("KriptoX");
        char *opcoes[] = {
                "Sair",
                "Logar",
                "Registrar",
                NULL
        };
        mostrar_opcoes("Menu Principal", opcoes);
        scanf("%d", &opcao);
        getchar(); // Obtêm o \n

        switch (opcao) {
            case 0:
                break;
            case 1:
                // A função retorna a posição do usuário logado, se for para cancelar login retorna -1
                pos = logar_usuario(usuarios);
                // Caso retorne -1 irá cancelar o login
                if (pos >= 0) menu_opcoes(usuarios, pos, cotacao);
                break;
            case 2:
                registrar_usuario(usuarios, &pos, &cotacao);
                break;
            default:
                printf("Opção não encontrada\n");
        }
    }while(opcao != 0);


    printf("Desligando KriptoX, bye bye :(\n");
    return 0;
}


void menu_opcoes(User usuarios[10], int pos, Cotacoes cotacao){
    int opcao;

// Menu de opcoes
    do{
        // Limpar Console
        system("cls||clear");

        // Salva os dados atualizados do usuário após ele fazer uma operação
        salvar_usuarios(usuarios, &pos, &cotacao);

        mostrar_menu("Menu de Opções");
        char *opcoes[] = {
                "Sair",
                "Consultar Saldo",
                "Consultar Extrato",
                "Depositar Dinheiro",
                "Sacar Dinheiro",
                "Comprar Cripto",
                "Vender Cripto",
                "Atualizar Cotação",
                "Transferir Saldo",
                NULL
        };
        mostrar_opcoes("Menu de opções", opcoes);
        scanf("%d", &opcao);
        getchar();

        void (*opcoes_funcoes[])(User*, int, Cotacoes) =
                {consultar_saldo, consultar_extrato, depositar_reais,
                 sacar_reais, comprar_criptomoeda, vender_criptomoeda,
                 (void (*)(User *, int, Cotacoes)) atualizar_cotacao, transferir_saldo};


        if (opcao < 0 || opcao > 8 ){
            printf("Opção não encontrada\n");
        }
        else if (opcao != 0){
            opcoes_funcoes[opcao-1](usuarios, pos, cotacao);
        }
    }while (opcao != 0);
}
