#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <kutils.h>



int registrar_usuario(User usuarios[10], int pos){

    char cpf[12];
    char senha[9];
    char nome[255];

    printf("Registrar usuário\n");


    printf("Qual o seu nome?\n");
    fgets(nome, 254, stdin);

    // Obtêm um CPF válido (11 dígitos numéricos)
    receber_cpf_valido(cpf);

    // Obtêm uma senha válida (8 dígitos numéricos)
    receber_senha_valida(senha);

    // Dados iniciais do usuário
    strcpy(usuarios[pos].nome, nome);
    strcpy(usuarios[pos].cpf, cpf);
    strcpy(usuarios[pos].senha, senha);
    usuarios[pos].saldo.bitcoin = 0;
    usuarios[pos].saldo.ethereum = 0;
    usuarios[pos].saldo.reais = 0;
    usuarios[pos].saldo.ripple = 0;

    // Salva o novo usuário
    salvar_usuarios(usuarios, &pos);

    printf("Registro concluído com sucesso!\n");

    return 1;
}

// Obter CPF válido
void receber_cpf_valido(char *cpf){
    while(1){

        int i;

        printf("Insira um CPF válido, com 11 dígitos:\n");
        scanf(" %11s", cpf);
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
}

// Obter Senha válida
void receber_senha_valida(char *senha){
    while(1){

        int i;

        printf("Insira uma Senha válida, com 8 dígitos:\n");
        scanf(" %8s", senha);
        getchar();



        if (strlen(senha) != 8){
            printf("Senha inválida! A senha deve conter 8 dígitos numéricos!\n");
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
}

int logar_usuario(User usuarios[10]){

    int login_valido = 0;
    char cpf[12];
    char senha[9];
    int user;

    printf("%s", usuarios[0].nome);

    printf("Login usuário\n");
    do{

        // Obter CPF e senha para checar com a dos outros usuários
        receber_cpf_valido(cpf);
        receber_senha_valida(senha);

        // Itera sobre os usuários para achar o usuario do operador
        for(user = 0; user < 10; user++){
            printf("CPF: %s Senha: %s", usuarios[user].cpf, usuarios[user].senha);
            if (strcmp(usuarios[user].cpf, cpf) && strcmp(usuarios[user].senha, senha)){
                login_valido = 1;
                break;
            }
        }
        if (login_valido == 0)
            printf("Usuário não encontrado! Tente novamente.\n");

    } while(login_valido != 1);

    printf("Logado com sucesso!\n");

    return user;
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

// Carrega os usuários na variável usuários
int carregar_usuarios(User usuarios[], int *pos){
    FILE *f = fopen("usuarios.bin", "rb");
    if (f == NULL){
        return 0;
    }

    int qtd = fread(usuarios, sizeof(User), 10, f);
    if (qtd == 0){
        return 0;
    }

    qtd = fread(pos, sizeof(int), 1, f);
    if (qtd == 0){
        return 0;
    }

    if (fclose(f)){
        return 0;
    }

    return 1;
}
