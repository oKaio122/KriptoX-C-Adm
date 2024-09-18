#include <stdio.h>
#include <locale.h>



int main(){
    setlocale(LC_ALL, "portuguese");

    int opcao;

    // Loop é finalizado se opcao = 0
    do{
        printf("Qual opção você quer rodar?\n"
               "0 - Sair"
               "1 - Consultar Saldo"
               "2 - Consultar Extrato"
               "3 - Depositar Dinheiro"
               "4 - Sacar Dinheiro"
               "5 - Comprar Criptomoedas"
               "6 - Vender Criptomoedas"
               "7 - Atualizar Cotação");
        scanf("%d", &opcao);


        switch (opcao){
            case 0:
                break;
            case 1:
                printf("Saldo consultado!");
                break;
//                consultarSaldo();
            case 2:
                printf("Saldo consultado!");
                break;
//                consultarExtrato();
            case 3:
                printf("Saldo consultado!");
                break;
//                depositarReais();
            case 4:
                printf("Saldo consultado!");
                break;
//                sacarReais();
            case 5:
                printf("Saldo consultado!");
                break;
//                comprarCriptomoedas();
            case 6:
                printf("Saldo consultado!");
                break;
//              venderCriptomoedas();
            case 7:
                printf("Saldo consultado!");
                break;
//              atualizarCotacao();
            default:
                printf("Opção não encontrada");
                break;
        }
    }while (opcao != 0);

    printf("%d", opcao);
//    screen_text("Hello world");
    return 0;
}