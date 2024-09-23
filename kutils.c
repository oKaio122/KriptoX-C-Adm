#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <kutils.h>


int registrar_usuario(User usuarios[10], int *pos){

    char cpf[12];
    char senha[9];
    char nome[100];
    int i;

    printf("Registrar usuário\n");


    printf("Qual o seu nome?\n");
    scanf("%s", nome);
    getchar();

    // Obtêm um CPF válido (11 dígitos numéricos)
    receber_cpf_valido(cpf);

    // Obtêm uma senha válida (8 dígitos numéricos)
    receber_senha_valida(senha);

    // Loop para encontrar uma posição vazia de usuários
    for (i=0; i < 10; i++){
        if (strcmp(usuarios[i].cpf, "") == 0){
            printf("Número da array vazia: %d\n", i);
            break;
        }
    }

    // Dados iniciais do usuário
    strcpy(usuarios[i].nome, nome);
    strcpy(usuarios[i].cpf, cpf);
    strcpy(usuarios[i].senha, senha);
    usuarios[i].saldo.bitcoin = 0;
    usuarios[i].saldo.ethereum = 0;
    usuarios[i].saldo.reais = 0;
    usuarios[i].saldo.ripple = 0;
    *pos = i;

    // Salva o novo usuário
    salvar_usuarios(usuarios, pos);

    printf("Registro concluído com sucesso!\n");

    return 1;
}

// Obter CPF válido
void receber_cpf_valido(char *cpf){
    while(1){

        int i;

        printf("Insira um CPF válido, com 11 dígitos:\n");
        scanf("%s", cpf);

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
        scanf("%s", senha);
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
    int user, i;

    for (i=0; i < 10; i++){
        if (strcmp(usuarios[i].cpf, "") == 0){
            break;
        }
        printf("Nome: %s\n", usuarios[i].nome);
        printf("CPF: %s\n", usuarios[i].cpf);
        printf("Senha: %s\n\n\n\n", usuarios[i].senha);
    }

    printf("Login usuário\n");
    do{

        // Obter CPF e senha para checar com a dos outros usuários
        receber_cpf_valido(cpf);
        receber_senha_valida(senha);

        // Itera sobre os usuários para achar o usuario do operador
        for(user = 0; user < 10; user++){
            if (strcmp(usuarios[i].cpf, "") == 0){
            printf("Número da array vazia: %d\n", i);
            break;
            
            }
            printf("\n\nNome: %s\n", usuarios[user].nome);
            printf("CPF igual: %s, CPF: %s\n", strcmp(usuarios[user].cpf, cpf) ? "true" : "false", usuarios[user].cpf);
            printf("Senha igual: %s, Senha: %s\n\n\n", strcmp(usuarios[user].senha, senha) ? "true" : "false", usuarios[user].senha);

            if (strcmp(usuarios[user].cpf, cpf) == 0 && strcmp(usuarios[user].senha, senha) == 0){
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

int validar_senha(User usuarios[], int pos){
    char senha[9];
    int senha_valida = 0; // 0 == false 1 == true

    do{
        receber_senha_valida(senha);

        if (strcmp(usuarios[pos].senha, senha) == 0){
            break;
        }
    } while(senha_valida == 0);
    printf("Senha validade com sucesso!");
    return 1;
}   

void consultarSaldo(User usuarios[], int pos){
    

    printf("Consultar saldo");
    
    // Valida a senha do usuário
    validar_senha(usuarios, pos);
 
    printf("usuarios[pos].saldo[saldo].bitcoin;"); // Fiz isso so pra fazer a branch e o commit, nao sei se da certo :(. mals ae
    printf("usuarios[pos].saldo[saldo].ethereum;");
    printf("usuarios[pos].saldo[saldo].ripple;");
    printf("usuarios[pos].saldo[saldo].reais;");

}