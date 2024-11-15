#include "kutils.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-function-declaration"
int main(){
    setlocale(LC_ALL, "portuguese");

    User usuarios[10];
    Moeda *moedas = NULL;
    int qnt_moedas;
    int opcao;
    int pos;

    // Carrega as moedas na var moedas
    carregar_moedas(&moedas, &qnt_moedas, usuarios);

    // Carrega os usuarios na variavel usuarios
    carregar_usuarios(usuarios, &pos);


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
                if (pos >= 0) menu_opcoes(usuarios, pos, moedas, qnt_moedas);
                break;
            case 2:
                registrar_usuario(usuarios, &pos);
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


void menu_opcoes(User usuarios[10], int pos, Moeda *moedas, int qnt_moedas){
    int opcao;
    char boas_vindas[100];

    // Juntar boas vindas com o nome do usuário
    snprintf(boas_vindas, sizeof(boas_vindas), "Bem-vindo de volta, %s!", usuarios[pos].nome);

    system("cls||clear");

    mostrar_menu(boas_vindas);

// Menu de opcoes
    do{

        // Salva os dados atualizados do usuario apos ele fazer uma operacao
        salvar_usuarios(usuarios, &pos);

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

        switch (opcao)
        {
            case 0:
                return;
            case 1:
                consultar_saldo(usuarios, pos, qnt_moedas);
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
                comprar_criptomoeda(usuarios, pos, moedas, qnt_moedas);
                break;
            case 6:
//                vender_criptomoeda(usuarios, pos);
                break;
            case 7:
                atualizar_cotacao(&moedas, qnt_moedas);
                break;
            case 8:
//                transferir_saldo(usuarios, pos);
                break;

            default:
                printf("Opcao nao encontrada\n");
                printf("Aperte Enter para escolher novamente.\n");
                getchar(); // Recebe o \n do Enter
                break;
        }

        fflush(stdin);
        // Limpar Console
        system("cls||clear");

    }while (opcao != 0);
}
