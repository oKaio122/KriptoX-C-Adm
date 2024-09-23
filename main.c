#include <stdio.h>
#include <locale.h>
#include <kutils.h>

void altera_pos(int *pos);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-function-declaration"
int main(){
    setlocale(LC_ALL, "portuguese");

    User usuarios[10];
    int pos;
    int opcao;

    // Carrega os usuários na variável usuarios
    carregar_usuarios(usuarios, &pos);

    // Menu Principal
    do{
        printf("Bem-vindo ao KriptoX\n");
        printf("Menu Principal\n"
               "Selecione uma das opções abaixo:\n"
               "0 - Sair\n"
               "1 - Logar\n"
               "2 - Registrar\n");
        scanf("%d", &opcao);
        getchar(); // Obtêm o \n

        switch (opcao) {
            case 0:
                break;
            case 1:
                // A função retorna a posição do usuário logado
                pos = logar_usuario(usuarios);
                menu_opcoes(usuarios, pos);
                break;
            case 2:
                registrar_usuario(usuarios, &pos);
                break;
            default:
                printf("Opção não encontrada\n");
        }
    }while(opcao != 0);


    printf("Desligando KriptoX, bye bye :(\n");
    return 0;
}


void menu_opcoes(User usuarios[10], int pos){

    int opcao;

// Menu de opcoes
    do{
        printf("Qual opção você quer rodar?\n"
               "0 - Sair\n"
               "1 - Consultar Saldo\n"
               "2 - Consultar Extrato\n"
               "3 - Depositar Dinheiro\n"
               "4 - Sacar Dinheiro\n"
               "5 - Comprar Criptomoedas\n"
               "6 - Vender Criptomoedas\n"
               "7 - Atualizar Cotação\n");
        scanf("%d", &opcao);

        switch (opcao){
            case 0:
                break;
            case 1:
                consultar_saldo(usuarios, pos);
                break;
//                consultarSaldo();
            case 2:
                printf("Saldo consultado!\n");
                break;
//                consultarExtrato();
            case 3:
                printf("Saldo consultado!\n");
                break;
//                depositarReais();
            case 4:
                printf("Saldo consultado!\n");
                break;
//                sacarReais();
            case 5:
                printf("Saldo consultado!\n");
                break;
//                comprarCriptomoedas();
            case 6:
                printf("Saldo consultado!\n");
                break;
//              venderCriptomoedas();
            case 7:
                printf("Saldo consultado!\n");
                break;
//              atualizarCotacao();
            default:
                printf("Opção não encontrada\n");
                break;
        }

    }while (opcao != 0);

}