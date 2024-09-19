#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <kutils.h>

int salvar_usuarios(User usuarios[], int *pos);

int registrar_usuario(User usuarios[10], int pos){

    char cpf[12];
    char senha[9];
    char nome[255];

    printf("Registrar usuário\n");


    printf("Qual o seu nome?\n");
    fgets(nome, 254, stdin);

    // Obter CPF válido
    while(1){

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
    while(1){

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


    // Dados iniciais do usuário
    strcpy(usuarios[pos].nome, nome);
    strcpy(usuarios[pos].cpf, cpf);
    strcpy(usuarios[pos].senha, senha);
    usuarios[pos].saldo.bitcoin = 0;
    usuarios[pos].saldo.ethereum = 0;
    usuarios[pos].saldo.reais = 0;
    usuarios[pos].saldo.ripple = 0;

    // Salvar usuário
    salvar_usuarios(usuarios, &pos);

    return 1;
}


int logar_usuario(){

    char cpf[12];
    char senha[9];
    User usuario;

    printf("Insira o seu CPF:\n");
    scanf(" %11s", &cpf);
    getchar();

    printf("Insira sua senha:\n");
    scanf(" %8s", &senha);
    getchar();

    // Ler os usuários


    return 1;
}

// Salva os usuários no arquivo .bin
int salvar_usuarios(User usuarios[], int *pos){
    FILE *f = fopen("usuarios.bin", "wb");
    if (f == NULL){
        return 0;
    }

    int qtd = fwrite(usuarios, sizeof(User), 10, f);
    if (qtd == 0){
        return 0;
    }

    qtd = fwrite(pos, sizeof(int),1 , f);
    if (qtd == 0){
        return 0;
    }

    if (fclose(f)){
        return 0;
    }

    return 1;
}


