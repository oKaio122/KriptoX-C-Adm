#include "kutils.h"

int main(){

    Administrador administradores[10];
    User usuarios[10];
    int user;

    // carregar dados do programa

    // Cria um usuário adm padrão
    strcpy(administradores[0].nome, "default");
    strcpy(administradores[0].cpf, "12345678900");
    strcpy(administradores[0].senha, "63423594");

    while(1){
        system("cls||clear");
        mostrar_menu("Menu Principal Admin");
        printf("Pressione Enter para logar.");
        getchar();

        user = logar_administrador(administradores);
        if (user == -1) break;

        // abrir menu de adm
    }

    printf("Desligando KriptoX-Admin, bye bye :(\n");
}