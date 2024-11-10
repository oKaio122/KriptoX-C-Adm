#include "kutils.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-function-declaration"
int main(){
    setlocale(LC_ALL, "portuguese");

    User usuarios[10];
    Cotacoes cotacao;
    int pos;
    int opcao;


    // Carrega os usuarios na variavel usuarios
    carregar_usuarios(usuarios, &pos, &cotacao);

    // Coloca o preco padrao nas cotacoes se os valores estiverem como 0.0
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
        getchar(); // Obtem o \n

        switch (opcao) {
            case 0:
                break;
            case 1:
                // A funcao retorna a posicao do usuario logado, se for para cancelar login retorna -1
                pos = logar_usuario(usuarios);
                // Caso retorne -1 ira cancelar o login
                if (pos >= 0) menu_opcoes(usuarios, pos, &cotacao);
                break;
            case 2:
                registrar_usuario(usuarios, &pos, &cotacao);
                break;
            default:
                printf("Opcao nao encontrada\n");
                printf("Aperte Enter para escolher novamente.\n");
                getchar(); // Recebe o \n do Enter
        }
    }while(opcao != 0);


    printf("Desligando KriptoX, bye bye :(\n");
    return 0;
}


void menu_opcoes(User usuarios[10], int pos, Cotacoes *cotacao){
    int opcao;
    char boas_vindas[100];

    // Juntar boas vindas com o nome do usuário
    snprintf(boas_vindas, sizeof(boas_vindas), "Bem-vindo de volta, %s!", usuarios[pos].nome);

    system("cls||clear");

    mostrar_menu(boas_vindas);

// Menu de opcoes
    do{

        // Salva os dados atualizados do usuario apos ele fazer uma operacao
        salvar_usuarios(usuarios, &pos, cotacao);

        mostrar_menu("Menu de Opcoes");
        char *opcoes[] = {
                "Sair",
                "Consultar Saldo",
                "Consultar Extrato",
                "Depositar Reais",
                "Sacar Reais",
                "Comprar Cripto",
                "Vender Cripto",
                "Atualizar Cotacao",
                "Transferir Saldo",
                NULL
        };
        mostrar_opcoes("Menu de Opcoes", opcoes);
        scanf("%d", &opcao);
        while ((getchar()) != '\n' && getchar() != EOF);

        void (*opcoes_funcoes[])(User*, int, Cotacoes) =
                {consultar_saldo, consultar_extrato, depositar_reais,
                 sacar_reais, comprar_criptomoeda, vender_criptomoeda,
                 (void (*)(User *, int, Cotacoes)) atualizar_cotacao, transferir_saldo};

        if (opcao == 7){
            atualizar_cotacao(usuarios, pos, cotacao);
        }
        else if (opcao < 0 || opcao > 8 ){
            printf("Opcao nao encontrada\n");
            printf("Aperte Enter para escolher novamente.\n");
            getchar(); // Recebe o \n do Enter
        }
        else if (opcao != 0){
            opcoes_funcoes[opcao-1](usuarios, pos, *cotacao);
        }

        // Limpar Console
        system("cls||clear");

    }while (opcao != 0);
}
