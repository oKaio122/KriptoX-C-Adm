#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <kutils.h>


int registrar_usuario(User usuarios[10], int *pos){

    char cpf[12];
    char senha[9];
    char nome[100];
    int cpf_unico;
    int i;

    printf("Registrar usuário\n");


    printf("Qual o seu nome?\n");
    scanf("%s", nome);
    getchar();

    // Obtêm um CPF válido (11 dígitos numéricos e único)
    do{
        receber_cpf_valido(cpf);
        cpf_unico = 1;

        // Checa se tem um usuário com o CPF enviado
        for (i=0; i < 10; i++){
            if (strcmp(usuarios[i].cpf, cpf) == 0){
                printf("Esse CPF já está sendo utilizado!\n");
                cpf_unico = 0;
                break;
            }
        }
    }while(!cpf_unico);



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

// Retorna a posição do usuário logado
int logar_usuario(User usuarios[10]){

    int login_valido = 0;
    char cpf[12];
    char senha[9];
    int user;

    printf("Login usuário\n");
    do{

        // Obter CPF e senha para checar com a dos outros usuários
        receber_cpf_valido(cpf);
        receber_senha_valida(senha);

        // Itera sobre os usuários para achar o usuario do operador
        for(user = 0; user < 10; user++){

            if (strcmp(usuarios[user].cpf, "") == 0){
                printf("Número da array vazia: %d\n", user);
                break;

            }

            if (strcmp(usuarios[user].cpf, cpf) == 0 && strcmp(usuarios[user].senha, senha) == 0){
                login_valido = 1;
                break;
            }
        }

        if (!login_valido)
            printf("Usuário não encontrado! Tente novamente.\n");

    } while(!login_valido);

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

// Valida a senha do usuário
int validar_senha(User usuarios[], int pos){
    char senha[9];

    do{
        receber_senha_valida(senha);
    } while(strcmp(usuarios[pos].senha, senha) != 0);


    printf("Senha validada com sucesso!\n");
    return 1;
}

float receber_saldo_valido(char nome_saldo[], char operacao[]){
    float quantidade;

    do{

        printf("Insira a quantidade de %s que deseja %s:", nome_saldo, operacao);
        scanf("%f", &quantidade);
        fflush(stdin); // Limpa o buffer em caso do usuário enviar muitos caracteres

        if(quantidade <= 0){
            printf("A quantidade precisa ser maior que 0!\n");
        }

    }while(quantidade <= 0);

    return quantidade;
}

void consultar_saldo(User usuarios[], int pos){

    printf("Consultar saldo\n");

    validar_senha(usuarios, pos);

    printf("Saldo de Reais: %f\n", usuarios[pos].saldo.reais);
    printf("Saldo de Bitcoin: %f\n", usuarios[pos].saldo.bitcoin);
    printf("Saldo de Ethereum: %f\n", usuarios[pos].saldo.ethereum);
    printf("Saldo em Ripple: %f\n", usuarios[pos].saldo.ripple);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void depositar_reais(User usuarios[], int pos){
    float qnt_deposito;

    printf("Depositar Reais\n");

    // Obtêm um número maior que 0 e que não tem caracteres
    qnt_deposito = receber_saldo_valido("reais", "depositar");


    usuarios[pos].saldo.reais += qnt_deposito;

    printf("Depositado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].saldo.reais);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void sacar_reais(User usuarios[], int pos){
    float qnt_sacar;

    printf("Sacar Reais\n");

    // Obtêm um número maior que 0 e que não tem caracteres
    qnt_sacar = receber_saldo_valido("reais", "sacar");


    usuarios[pos].saldo.reais -= qnt_sacar;

    printf("Sacado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].saldo.reais);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void comprar_criptomoeda(User usuarios[], int pos){
    char criptomoeda[10];
    float qnt_moeda;
    float taxa;
    float preco_operacao;
    int opcao, confirmacao;

    printf("Comprar criptomoeda\n");

    // Valida a senha antes do usuário poder comprar cripto
    validar_senha(usuarios, pos);

    // Implementar cotação
    printf("Cotação atual: BTC 1 -> R$ Implementar \nETH 1 -> R$ Implementar \nXRP 1 -> R$ Implementar\n");

    do{
        printf("Qual criptomoeda você quer comprar?");
        printf("Criptomoedas disponíveis:\n1 - Bitcoin \n2 - Ethereum \n3 - Ripple\n");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                strncpy(criptomoeda, "Bitcoin", sizeof(criptomoeda)-1);
                taxa = 0.02;
                break;
            case 2:
                strncpy(criptomoeda, "Ethereum", sizeof(criptomoeda)-1);
                taxa = 0.01;
                break;
            case 3:
                strncpy(criptomoeda, "Ripple", sizeof(criptomoeda)-1);
                taxa = 0.01;
                break;
            default:
                printf("Opção não encontrada\n");
                break;
        }

    }while(!opcao);
    do{
        // Obtêm um número maior que 0 e que não tem caracteres
        qnt_moeda = receber_saldo_valido(criptomoeda, "comprar");

        preco_operacao = (qnt_moeda * (1 + taxa) /* * cotacao */) ;

        if (preco_operacao > usuarios[pos].saldo.reais){
            printf("Saldo em reais insuficiente!");
        }

    } while (preco_operacao > usuarios[pos].saldo.reais);

    printf("Para confirmar a compra digite 1: ");
    scanf("%d", &confirmacao);
    getchar();

    if (confirmacao != 1){
        return;
    }

    // Parte das operações
    usuarios[pos].saldo.reais -= preco_operacao;
    // Adiciona a qnt de cripto na moeda selecionada
    if (strcmp(criptomoeda, "Bitcoin") == 0) {
        usuarios[pos].saldo.bitcoin += qnt_moeda;
    } else if (strcmp(criptomoeda, "Ethereum") == 0) {
        usuarios[pos].saldo.ethereum += qnt_moeda;
    } else if (strcmp(criptomoeda, "Ripple") == 0) {
        usuarios[pos].saldo.ripple += qnt_moeda;
    }

    printf("Compra realizada com sucesso! Total com taxa: R$ %.2f, Taxa: R$ %.2f\n", preco_operacao, qnt_moeda * (taxa));
    printf("Saldo em reais atualizado: R$ %.2f\n", usuarios[pos].saldo.reais);
    // Printa o saldo da criptomoeda selecionada atualizado
    printf("Saldo em %s atualizado: %.2f\n", criptomoeda,
           strcmp(criptomoeda, "Bitcoin") == 0 ? usuarios[pos].saldo.bitcoin :
           strcmp(criptomoeda, "Ethereum") == 0 ? usuarios[pos].saldo.ethereum :
           usuarios[pos].saldo.ripple);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}