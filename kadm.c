#include "kutils.h"

int main(){

    Administrador administradores[10];
    User usuarios[10];
    Moeda *moedas = NULL;
    int qnt_moedas;
    int opcao;
    int user;

    carregar_moedas(&moedas, &qnt_moedas);
    // Carregar usuarios tmb

    // Cria um usuário adm padrão
    strcpy(administradores[0].nome, "default");
    strcpy(administradores[0].cpf, "12345678900");
    strcpy(administradores[0].senha, "63423594");

    while(1){
        system("cls||clear");
        mostrar_menu("Menu Principal Admin");
        printf("Digite 0 para sair ou 1 para logar.\n");
        scanf("%d", &opcao);
        if(opcao == 0) break;

        user = logar_administrador(administradores);
        if (user == -1) break;

        menu_opcoes_admin(moedas, &qnt_moedas, usuarios);
    }

    printf("Desligando KriptoX-Admin, bye bye :(\n");
}

void menu_opcoes_admin(Moeda *moedas, int *qnt_moedas, User usuarios[]){
    int opcao;

    system("cls||clear");

    do{

        // Salvar dados atualizados de usuarios e administradores
        // salvar_usuarios(usuarios, &pos, cotacao);
        salvar_moedas(moedas, *qnt_moedas);

        char *opcoes[] = {
                "Sair",
                "Cadastrar Investidor",
                "Excluir Investidor",
                "Cadastrar Criptomoeda",
                "Excluir Criptomoeda",
                "Consultar Saldo",
                "Consultar Extrato",
                "Atualizar Cotacao",
                NULL
        };
        mostrar_opcoes("Menu de Opcoes Admin", opcoes);
        scanf("%d", &opcao);

        while ((getchar()) != '\n' && getchar() != EOF);


        switch (opcao)
        {
            case 0:
                return;
            case 1:
                cadastrar_usuario(usuarios);
                break;
            case 2:
                excluir_usuario(usuarios);
                break;
            case 3:
                cadastrar_criptomoeda(&moedas, qnt_moedas);
                break;
            case 4:
                excluir_criptomoeda(&moedas, qnt_moedas);
                break;
            case 5:
//                consultar_saldo_admin();
                break;
            case 6:
//                consultar_extrato_admin();
                break;
            case 7:
                // atualizar_cotacao();
                break;

            default:
                printf("Opcao nao encontrada\n");
                printf("Aperte Enter para escolher novamente.\n");
                getchar(); // Recebe o \n do Enter
                break;
        }

        if (!(opcao < 0 || opcao > 7)){
            printf("Aperte Enter para voltar ao menu de opcoes admin.\n");
            getchar(); // Recebe o \n do Enter
        }

        // Limpar Console
        system("cls||clear");

    }while (opcao != 0);
}