#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <kutils.h>

typedef struct {
    float ethereum;
    float bitcoin;
    float ripple;
    float reais;
} Saldo;

typedef struct {
    char data[255];
    char operacao[255];
    char moeda[10];
    float cotacao;
    float taxa;
} Extrato;

typedef struct {
    char nome[255];
    char cpf[12];
    char senha[9];
    Saldo saldo;
    Extrato extrato[100];
} User;

int registrar_usuario(){

    char cpf[12];
    char senha[9];
    char nome[255];
    User usuario;

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


    // Dados iniciais do usuário
    strcpy(usuario.nome, nome);
    strcpy(usuario.cpf, cpf);
    strcpy(usuario.senha, senha);
    usuario.saldo.bitcoin = 0;
    usuario.saldo.ethereum = 0;
    usuario.saldo.reais = 0;
    usuario.saldo.ripple = 0;

    // Salvar usuário



    return 0;
}

int logar_usuario(){

    char cpf[12];
    char senha[9];
    int login_resposta; // Se 0 quer dizer que falhou, se 1 quer dizer que foi aprovado
    User usuario;

    printf("Insira o seu CPF:\n");
    scanf(" %11s", &cpf);
    getchar();

    printf("Insira sua senha:\n");
    scanf(" %8s", &senha);
    getchar();

    // Ler os usuários


    return login_resposta;
}