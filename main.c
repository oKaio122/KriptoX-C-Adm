#include <stdio.h>
#include <locale.h>


void menu_opcoes();


int main(){
    setlocale(LC_ALL, "portuguese");

    int opcao;
    int login_response = 1;

    // Menu Principal
    do{

        printf("Bem-vindo ao KriptoX\n");
        printf("Menu Principal\n"
               "Selecione uma das opções abaixo:\n"
               "0 - Sair\n"
               "1 - Logar\n"
               "2 - Registrar\n");
        scanf("%d", &opcao);

        printf("%d", opcao);

        switch (opcao) {
            case 0:
                break;
            case 1:
                printf("Logando...\n");
                // se login_response == 1 (True) mandar para o menu de opcoes
                if (login_response == 1){
                    menu_opcoes(/*Informações do usuário*/);
                }
                break;
            case 2:
                printf("Registrando...\n");
                break;
        }
    }while(opcao != 0);


    printf("Desligando KriptoX, bye bye :(\n");
    return 0;
}

void menu_opcoes(/*Informações do Usuário */){
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
                printf("Saldo consultado!\n");
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