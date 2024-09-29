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
                "Registrar"
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


        printf("Qual opção você quer rodar?\n"
               "0 - Sair\n"
               "1 - Consultar Saldo\n"
               "2 - Consultar Extrato\n"
               "3 - Depositar Dinheiro\n"
               "4 - Sacar Dinheiro\n"
               "5 - Comprar Criptomoedas\n"
               "6 - Vender Criptomoedas\n"
               "7 - Atualizar Cotação\n"
               "8 - Transferir Saldo\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
            case 0:
                break;
            case 1:
                consultar_saldo(usuarios, pos);
                break;
            case 2:
                consultar_extrato(usuarios, pos);
                break;
            case 3:
                depositar_reais(usuarios, pos);
                break;
            case 4:
                sacar_reais(usuarios, pos);
                break;
            case 5:
                comprar_criptomoeda(usuarios, pos, cotacao);
                break;
            case 6:
                vender_criptomoeda(usuarios, pos, cotacao);
                break;
            case 7:
                atualizar_cotacao(usuarios, &pos, &cotacao);
                break;
          case 8:
              transferir_saldo(usuarios, pos, cotacao);
                break;
            default:
                printf("Opção não encontrada\n");
                break;
        }

    }while (opcao != 0);

}