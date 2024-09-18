#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>



int registrar_usuario(){
    char cpf[12];
    char senha[9];
    char nome[255];

    printf("Registrar usuário\n");

    printf("Qual o seu nome?\n");
    fgets(nome, 256, stdin);

    // Obter CPF válido
    while(true){

        int i;

        printf("Insira um CPF válido, com 11 dígitos:\n");
        scanf(" %11s", &cpf);
        getchar();



        if (strlen(cpf) != 11){
            printf("CPF inválido! O CPF deve conter 11 dígitos numéricos!\n");
            continue;
        }

        for(i=0; i < strlen(cpf); i++){
            if(!isdigit(cpf[i])){
                printf("CPF inválido! O CPF deve conter números apenas!\n");
                continue;
            }
        }
        break;
    }

    // Obter Senha válida
    while(true){

        int i;

        printf("Insira uma Senha válida, com 8 dígitos:\n");
        scanf(" %8s", &senha);
        getchar();



        if (strlen(senha) != 8){
            printf("Senha inválida! A senha deve conter 11 dígitos numéricos!\n");
            continue;
        }

        for(i=0; i < strlen(senha); i++){
            if(!isdigit(senha[i])){
                printf("Senha inválida! A senha deve conter números apenas!\n");
                continue;
            }
        }
        break;
    }


    // Salvar os dados


    return 0;
}