#include "kutils.h"

int registrar_usuario(User usuarios[10], int *pos, Cotacoes *cotacao){

    char cpf[12];
    char senha[9];
    char nome[100];
    int cpf_unico;
    int i;

    system("cls||clear");
    mostrar_menu("Registrar usuário");

    printf("Qual o seu nome?\n");
    scanf("%s", nome);
    getchar();

    // Obtêm um CPF válido (11 dígitos numéricos e único)
    do{
        receber_cpf_valido(cpf, 0);
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
    receber_senha_valida(senha, 0);

    // Loop para encontrar uma posição vazia de usuários
    for (i=0; i < 10; i++){
        if (strcmp(usuarios[i].cpf, "") == 0){
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
    salvar_usuarios(usuarios, pos, cotacao);

    printf("Registro concluído com sucesso!\n");

    return 1;
}

// Obter CPF válido, também gerencia ação de CANCELAR do usuário
void receber_cpf_valido(char *cpf, int cancelar_autorizado){
    int i;
    int cpf_valido;

    do{
        cpf_valido = 1;

        printf("Insira um CPF válido, com 11 dígitos:\n");
        scanf("%s", cpf);

        // Checa se é para cancelar a operação
        if ((strcmp(cpf, "CANCELAR") == 0) && (cancelar_autorizado)){
            break;
        }

        if (strlen(cpf) != 11){
            cpf_valido = 0;
            printf("CPF inválido! O CPF deve conter 11 dígitos numéricos!\n");
            continue;
        }

        for(i=0; i < strlen(cpf); i++){
            if(!isdigit(cpf[i])){
                printf("CPF inválido! O CPF deve conter números apenas!\n");
                cpf_valido = 0;
                break;
            }
        }
    } while (!cpf_valido);
}

// Obter Senha válida
void receber_senha_valida(char *senha, int cancelar_autorizado){
    int i;
    int senha_valida;

    do{
        senha_valida = 1;

        printf("Insira uma Senha válida, com 8 dígitos:\n");
        scanf("%s", senha);

        // Checa se é para cancelar a operação
        if ((strcmp(senha, "CANCELAR") == 0) && (cancelar_autorizado)){
            break;
        }

        if (strlen(senha) != 8){
            printf("Senha inválida! A senha deve conter 8 dígitos numéricos!\n");
            senha_valida = 0;
            continue;
        }

        for(i=0; i < strlen(senha); i++){
            if(!isdigit(senha[i])){
                printf("Senha inválida! A senha deve conter números apenas!\n");
                senha_valida = 0;
                break;
            }
        }
    } while (!senha_valida);
}

// Retorna a posição do usuário logado
int logar_usuario(User usuarios[10]){

    int login_valido = 0;
    char cpf[12];
    char senha[9];
    int user;

    system("cls||clear");
    mostrar_menu("Login usuário");
    printf("Digite \"CANCELAR\" para cancelar o login \n");

    do{

        // Obter CPF e senha para checar com a dos outros usuários
        receber_cpf_valido(cpf, 1);
        if (strcmp(cpf, "CANCELAR") == 0){
            return -1;
        }
        receber_senha_valida(senha, 0);

        // Itera sobre os usuários para achar o usuario do operador
        for(user = 0; user < 10; user++){

            if (strcmp(usuarios[user].cpf, "") == 0){
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
int salvar_usuarios(User usuarios[], int *pos, Cotacoes *cotacao){
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

    qtd = fwrite(cotacao, sizeof(float),1 , f);
    if (qtd == 0){
        return 0;
    }

    if (fclose(f)){
        return 0;
    }

    return 1;
}

// Carrega os usuários na variável usuários
int carregar_usuarios(User usuarios[], int *pos, Cotacoes *cotacao){
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

    qtd = fread(cotacao, sizeof(float),1 , f);
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
        receber_senha_valida(senha, 1);

        // Checa se o usuário cancelou a operação
        if (strcmp(senha, "CANCELAR") == 0) return 0;

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

        if(quantidade <= 0.0){
            printf("A quantidade precisa ser maior que 0!\n");
        }

    }while(quantidade <= 0.0);

    return quantidade;
}

void consultar_saldo(User usuarios[], int pos){

    system("cls||clear");
    mostrar_menu("Consultar saldo");

    printf("Saldo de Reais: %f\n", usuarios[pos].saldo.reais);
    printf("Saldo de Bitcoin: %f\n", usuarios[pos].saldo.bitcoin);
    printf("Saldo de Ethereum: %f\n", usuarios[pos].saldo.ethereum);
    printf("Saldo em Ripple: %f\n", usuarios[pos].saldo.ripple);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void consultar_extrato(User usuarios[], int pos){
    char *extrato_data;
    int i;


    printf("Consultar Extrato\n");

    // Itera sobre os extratos
    for(i = 0; i < 100; i++){

        // Verifica se o extrato atual é lixo, se for quebrar o loop
        extrato_data = usuarios[pos].extrato[i].data;
        if (strcmp(extrato_data, "") == 0){
            break;
        }
        printf("Extrato:\n");

        printf("Data: %s\t", usuarios[pos].extrato[i].data);
        printf("Operação: %s\t", usuarios[pos].extrato[i].operacao);
        printf("Moeda: %s\t", usuarios[pos].extrato[i].moeda);
        printf("Valor: %.2f\t", usuarios[pos].extrato[i].valor);
        printf("Taxa paga: %.2f\t", usuarios[pos].extrato[i].taxa);
        printf("Cotacao: %.2f\n", usuarios[pos].extrato[i].cotacao);
    }


    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void salvar_extrato(User usuarios[], int pos, char operacao[],
                    char moeda[], float cotacao,float valor, float taxa){
    int i;
    char *extrato_data;
    char datetime[20];
    struct tm *info;

    // Obtem a data atual e salva na variável datetime
    time_t rawtime;
    time( &rawtime );
    info = localtime( &rawtime );
    strftime(datetime,20,"%d/%m/%Y - %H:%M", info);


    for(i = 0; i < 100; i++){

        // Verifica se o extrato atual é lixo, se for quebrar o loop
        extrato_data = usuarios[pos].extrato[i].data;
        if (strcmp(extrato_data, "") == 0){
            break;
        }
    }


    strncpy(usuarios[pos].extrato[i].data, datetime, sizeof(usuarios[pos].extrato[i].data)-1);
    strncpy(usuarios[pos].extrato[i].operacao, operacao, sizeof(usuarios[pos].extrato[i].operacao)-1);
    strncpy(usuarios[pos].extrato[i].moeda, moeda, sizeof(usuarios[pos].extrato[i].moeda)-1);
    usuarios[pos].extrato[i].valor = valor;
    usuarios[pos].extrato[i].taxa = taxa;
    usuarios[pos].extrato[i].cotacao = cotacao;

}

void depositar_reais(User usuarios[], int pos){
    float qnt_deposito;

    printf("Depositar Reais\n");

    // Obtêm um número maior que 0 e que não tem caracteres
    qnt_deposito = receber_saldo_valido("reais", "depositar");


    usuarios[pos].saldo.reais += qnt_deposito;

    printf("Depositado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].saldo.reais);

    salvar_extrato(usuarios, pos, "+", "Real", 1, qnt_deposito, 0);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void sacar_reais(User usuarios[], int pos){
    float qnt_sacar;

    printf("Sacar Reais\n");

    validar_senha(usuarios, pos);

    do{

        // Obtêm um número maior que 0 e que não tem caracteres
        qnt_sacar = receber_saldo_valido("reais", "sacar");

        if (qnt_sacar > usuarios[pos].saldo.reais){
            printf("Você não tem saldo o suficiente para sacar R$ %.2f! Seu saldo em R$: %.2f\n", qnt_sacar, usuarios[pos].saldo.reais);
        }

    } while (qnt_sacar > usuarios[pos].saldo.reais);



    usuarios[pos].saldo.reais -= qnt_sacar;

    printf("Sacado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].saldo.reais);

    salvar_extrato(usuarios, pos, "-", "Real", 1, qnt_sacar, 0);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void comprar_criptomoeda(User usuarios[], int pos, Cotacoes cotacao){
    char criptomoeda[10];
    float qnt_moeda;
    float taxa;
    float preco_operacao;
    float cotacao_cripto;
    int opcao, confirmacao;

    printf("Comprar criptomoeda\n");

    printf("Valide sua senha antes de comprar cripto, para cancelar digite \"CANCELAR\".");

    // Valida a senha antes do usuário poder comprar cripto, se o usuário digitar "CANCELAR" a operação será cancelada
    if (!validar_senha(usuarios, pos)) return;


    // Implementar cotação
    printf("Cotação atual:\n BTC 1 -> R$ %f \nETH 1 -> R$ %f \nXRP 1 -> R$ %f \n", cotacao.bitcoin, cotacao.ethereum,cotacao.ripple);

    do{
        printf("Qual criptomoeda você quer comprar?\n");
        printf("Criptomoedas disponíveis:\n1 - Bitcoin \n2 - Ethereum \n3 - Ripple\n");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                strncpy(criptomoeda, "Bitcoin", sizeof(criptomoeda)-1);
                taxa = 0.02;
                cotacao_cripto = cotacao.bitcoin;
                break;
            case 2:
                strncpy(criptomoeda, "Ethereum", sizeof(criptomoeda)-1);
                taxa = 0.01;
                cotacao_cripto = cotacao.ethereum;
                break;
            case 3:
                strncpy(criptomoeda, "Ripple", sizeof(criptomoeda)-1);
                taxa = 0.01;
                cotacao_cripto = cotacao.ripple;
                break;
            default:
                printf("Opção não encontrada\n");
                break;
        }

    }while(!opcao);
    do{
        // Obtêm um número maior que 0 e que não tem caracteres
        qnt_moeda = receber_saldo_valido(criptomoeda, "comprar");

        preco_operacao = (qnt_moeda * (1 + taxa)  * cotacao_cripto);

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

    printf("Compra realizada com sucesso! Total com taxa: R$ %.2f, Taxa: R$ %.2f\n", preco_operacao, preco_operacao * (taxa));
    printf("Saldo em reais atualizado: R$ %.2f\n", usuarios[pos].saldo.reais);
    // Printa o saldo da criptomoeda selecionada atualizado
    printf("Saldo em %s atualizado: %.2f\n", criptomoeda,
           strcmp(criptomoeda, "Bitcoin") == 0 ? usuarios[pos].saldo.bitcoin :
           strcmp(criptomoeda, "Ethereum") == 0 ? usuarios[pos].saldo.ethereum :
           usuarios[pos].saldo.ripple);

    salvar_extrato(usuarios, pos, "-", "Real", 1, preco_operacao, taxa);
    salvar_extrato(usuarios, pos, "+", criptomoeda, cotacao_cripto, qnt_moeda, 0);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void vender_criptomoeda(User usuarios[], int pos, Cotacoes cotacao){
    char criptomoeda[10];
    float qnt_moeda;
    float taxa;
    float preco_operacao;
    float saldo_cripto;
    float cotacao_cripto;
    int opcao, confirmacao;

    printf("Vender criptomoeda\n");

    printf("Valide sua senha antes de vender cripto, para cancelar digite \"CANCELAR\".");

    // Valida a senha antes do usuário poder vender cripto, se o usuário digitar "CANCELAR" a operação será cancelada
    if (!validar_senha(usuarios, pos)) return;

    // Implementar cotação
    printf("Cotação atual:\n BTC 1 -> R$ %f \nETH 1 -> R$ %f \nXRP 1 -> R$ %f \n", cotacao.bitcoin, cotacao.ethereum,cotacao.ripple);

    do{
        printf("Qual criptomoeda você quer vender?\n");
        printf("Criptomoedas disponíveis:\n1 - Bitcoin \n2 - Ethereum \n3 - Ripple\n");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                strncpy(criptomoeda, "Bitcoin", sizeof(criptomoeda)-1);
                saldo_cripto = usuarios[pos].saldo.bitcoin;
                cotacao_cripto = cotacao.bitcoin;
                taxa = 0.03;
                break;
            case 2:
                strncpy(criptomoeda, "Ethereum", sizeof(criptomoeda)-1);
                saldo_cripto = usuarios[pos].saldo.ethereum;
                cotacao_cripto = cotacao.ethereum;
                taxa = 0.02;
                break;
            case 3:
                strncpy(criptomoeda, "Ripple", sizeof(criptomoeda)-1);
                saldo_cripto = usuarios[pos].saldo.ripple;
                cotacao_cripto = cotacao.ripple;
                taxa = 0.01;
                break;
            default:
                printf("Opção não encontrada\n");
                break;
        }

    }while(!opcao);

    do{
        // Obtêm um número maior que 0 e que não tem caracteres
        qnt_moeda = receber_saldo_valido(criptomoeda, "vender");

        if (qnt_moeda > saldo_cripto){
            printf("Saldo em %s insuficiente!\n", criptomoeda);
        }

    } while (qnt_moeda > saldo_cripto);

    printf("Para confirmar a venda digite 1: ");
    scanf("%d", &confirmacao);
    getchar();

    if (confirmacao != 1){
        return;
    }


    // Parte das operações
    preco_operacao = (qnt_moeda * cotacao_cripto)/ (1 + taxa);
    usuarios[pos].saldo.reais += preco_operacao ;

    // Adiciona a qnt de cripto na moeda selecionada
    if (strcmp(criptomoeda, "Bitcoin") == 0) {
        usuarios[pos].saldo.bitcoin -= qnt_moeda;
    } else if (strcmp(criptomoeda, "Ethereum") == 0) {
        usuarios[pos].saldo.ethereum -= qnt_moeda;
    } else if (strcmp(criptomoeda, "Ripple") == 0) {
        usuarios[pos].saldo.ripple -= qnt_moeda;
    }

    printf("Venda realizada com sucesso! Total ganho com taxa: R$ %.2f, Taxa: R$ %.2f\n", preco_operacao, preco_operacao * (taxa));
    printf("Saldo em reais atualizado: R$ %.2f\n", usuarios[pos].saldo.reais);
    // Printa o saldo da criptomoeda selecionada atualizado
    printf("Saldo em %s atualizado: %.2f\n", criptomoeda,
           strcmp(criptomoeda, "Bitcoin") == 0 ? usuarios[pos].saldo.bitcoin :
           strcmp(criptomoeda, "Ethereum") == 0 ? usuarios[pos].saldo.ethereum :
           usuarios[pos].saldo.ripple);

    salvar_extrato(usuarios, pos, "-", criptomoeda, cotacao_cripto, qnt_moeda, 0);
    salvar_extrato(usuarios, pos, "+", "Real", 1, preco_operacao, taxa);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

float gerar_varicao_cotacao(){
    int num_random;

    // seed aleatória
    srand(time(NULL));

    // Número entre -500 e 500 ( simula o -5 e 5% )
    num_random = (rand() % 1001) - 500;
    return num_random / 10000.0f;
}

void atualizar_cotacao(User usuarios[10], int *pos, Cotacoes *cotacao){

    float variacao;
    int moeda;

    printf("Atualizar cotação\n");

    // Itera sobre as moedas dentro da cotação
    for (moeda = 0; moeda < 3; moeda++){

        // Num entre -5% e 5%
        variacao = gerar_varicao_cotacao();

        switch (moeda) {
            case 0:
                // Pega o valor inicial e soma com o resultado da multiplicação da soma do 1ºrand com o 2ºrand / 100 + 100 da porcentagem
                cotacao->bitcoin += cotacao->bitcoin * variacao;
                break;
            case 1:
                cotacao->ethereum += cotacao->ethereum * variacao;
                break;
            case 2:
                cotacao->ripple += cotacao->ripple * variacao;
                break;
        }
    }
    printf("Cotações atualizadas:\n");
    printf("BTC atualizada: %f\n", cotacao->bitcoin);
    printf("ETH atualizado: %f\n", cotacao->ethereum);
    printf("Ripple atualizado: %f\n", cotacao->ripple);

    salvar_usuarios(usuarios, pos, cotacao);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

// Utilizada em caso das cotações estarem vazias
void iniciar_cotacoes(Cotacoes *cotacao){

    if (cotacao->bitcoin == 0.0){
        cotacao->bitcoin = 351.21;
    }
    if (cotacao->ethereum == 0.0){
        cotacao->ethereum = 26.27;
    }
    if (cotacao->ripple == 0.0){
        cotacao->ripple = 3.24;
    }

}

void transferir_saldo(User usuarios[], int pos, Cotacoes cotacao){

    int opcao_moeda;
    float saldo_moeda;
    char nome_moeda[10];
    float cotacao_moeda;
    float qnt_transferir;

    int pessoa_valida; // 0 inválido 1 válido
    char cpf[12];
    int user;
    printf("Transferir saldo \n");

    // Obtem o usuário que quer transferir o saldo
    do{
        pessoa_valida = 0;
        printf("Para qual CPF você quer transferir o saldo? Para cancelar digite \"CANCELAR\"\n");
        // Obtem o CPF
        receber_cpf_valido(cpf, 1);
        if (strcmp(cpf, "CANCELAR") == 0) return;
        for(user = 0; user < 10; user++){
            if (strcmp(usuarios[user].cpf, cpf) == 0){
                pessoa_valida = 1;
                break;
            }
        }
        if (!pessoa_valida){
            printf("CPF não encontrado!\n");
        }
    } while (pessoa_valida == 0);

    // Obtem a moeda que vai ser utilizada
    do{
        printf("Qual moeda você quer transferir?\n");
        printf("Moedas:\n1 - Real\n2 - Bitcoin\n3 - Ethereum\n4 - Ripple\n");
        scanf("%d", &opcao_moeda);

        switch (opcao_moeda) {
            case 1:
                saldo_moeda = usuarios[pos].saldo.reais;
                strncpy(nome_moeda, "Real", sizeof(nome_moeda)-1);
                cotacao_moeda = 1;
                break;
            case 2:
                saldo_moeda = usuarios[pos].saldo.bitcoin;
                strncpy(nome_moeda, "Bitcoin", sizeof(nome_moeda)-1);
                cotacao_moeda = cotacao.bitcoin;
                break;
            case 3:
                saldo_moeda = usuarios[pos].saldo.ethereum;
                strncpy(nome_moeda, "Ethereum", sizeof(nome_moeda)-1);
                cotacao_moeda = cotacao.ethereum;
                break;
            case 4:
                saldo_moeda = usuarios[pos].saldo.ripple;
                strncpy(nome_moeda, "Ripple", sizeof(nome_moeda)-1);
                cotacao_moeda = cotacao.ripple;
                break;
            default:
                opcao_moeda = 0;
                printf("Opção não encontrada!\n");
        }
    } while (opcao_moeda == 0);

    // Obter valor válido a transferir
    do{
        // Obtêm um número maior que 0 e que não tem caracteres
        qnt_transferir = receber_saldo_valido(nome_moeda, "transferir");

        if (qnt_transferir > saldo_moeda){
            printf("Saldo em %s insuficiente!\n", nome_moeda);
        }

    } while (qnt_transferir > saldo_moeda);

    if (strcmp(nome_moeda, "Real") == 0){
        usuarios[pos].saldo.reais -= qnt_transferir;
        usuarios[user].saldo.reais += qnt_transferir;
    }
    else if (strcmp(nome_moeda, "Bitcoin") == 0){
        usuarios[pos].saldo.bitcoin -= qnt_transferir;
        usuarios[user].saldo.bitcoin += qnt_transferir;
    }
    else if (strcmp(nome_moeda, "Ethereum") == 0){
        usuarios[pos].saldo.ethereum -= qnt_transferir;
        usuarios[user].saldo.ethereum += qnt_transferir;
    }
    else if (strcmp(nome_moeda, "Ripple") == 0){
        usuarios[pos].saldo.ripple -= qnt_transferir;
        usuarios[user].saldo.ripple += qnt_transferir;
    }

    printf("Dinheiro transferido com sucesso!\n");
    printf("Saldo em %s atualizado: %.2f\n", nome_moeda,
           strcmp(nome_moeda, "Real") == 0 ? usuarios[pos].saldo.reais :
           strcmp(nome_moeda, "Bitcoin") == 0 ? usuarios[pos].saldo.bitcoin :
           strcmp(nome_moeda, "Ethereum") == 0 ? usuarios[pos].saldo.ethereum :
           usuarios[pos].saldo.ripple);

    salvar_extrato(usuarios, pos, "-", nome_moeda, cotacao_moeda, qnt_transferir, 0);
    salvar_extrato(usuarios, user, "+", nome_moeda, cotacao_moeda, qnt_transferir, 0);

    printf("Digite Enter para voltar ao menu de opções.\n");
    getchar(); // Recebe o \n do Enter
}

void mostrar_menu(char nome_menu[]){
    int nome_menu_len;
    int i;

    nome_menu_len = strlen(nome_menu) + 3;

    // Altera o padrão de texto para UTF-16 para printar caracteres especiais
    _setmode(_fileno(stdout), _O_U16TEXT);

    wprintf(L"┏━━");
    for (i=0; i < nome_menu_len; i++){
        wprintf(L"━");
    }
    wprintf(L"━┓\n");

    wprintf(L"┃   %s   ┃\n", nome_menu);

    wprintf(L"┗━");
    for (i=0; i < nome_menu_len; i++){
        wprintf(L"━");
    }
    wprintf(L"━━┛\n");

    // Volta o padrão de texto para o modo de texto padrão
    _setmode(_fileno(stdout), _O_TEXT);

}

void mostrar_opcoes(char titulo[], char *opcoes[]){
    int nome_menu_len;
    int i, j;

    nome_menu_len = strlen(titulo) + 3;

    // Altera o padrão de texto para UTF-16 para printar caracteres especiais
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Printa ┏━━「 titulo 」━━┓
    wprintf(L"┏━━");
    wprintf(L"】 %s 【", titulo);
    wprintf(L"━━┓\n");
    // Fim do print

    // Printa o meio do menu (┃ i - Opcao                |)
    i = 0;
    while (opcoes[i] != NULL) {
        wprintf(L"┃   %d - %s", i, opcoes[i]);
        for (j = 0; j < nome_menu_len - strlen(opcoes[i]); j++){
            wprintf(L" ");
        }
        wprintf(L"┃\n");
        i++;
    }
    // Fim do print

    // Printa ┗━━━━━━━━━━━━━┛
    wprintf(L"┗━━━");
    for (i=0; i < nome_menu_len; i++){
        wprintf(L"━");
    }
    wprintf(L"━━━━┛\n");
    // Fim do print

    // Volta o padrão de texto para o modo de texto padrão
    _setmode(_fileno(stdout), _O_TEXT);

}
