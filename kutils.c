#include "kutils.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"
int registrar_usuario(User usuarios[10], int *pos){

    char cpf[12];
    char senha[9];
    char nome[100];
    int cpf_unico;
    int i;

    system("cls||clear");
    mostrar_menu("Registrar usuario");

    printf("Qual o seu nome?\n");
    scanf("%s", nome);
    getchar();

    // Obtem um CPF valido (11 digitos numericos e unico)
    do{
        receber_cpf_valido(cpf, 0);
        cpf_unico = 1;

        // Checa se tem um usuario com o CPF enviado
        for (i=0; i < 10; i++){
            if (strcmp(usuarios[i].cpf, cpf) == 0){
                printf("Esse CPF ja esta sendo utilizado!\n");
                cpf_unico = 0;
                break;
            }
        }
    }while(!cpf_unico);



    // Obtem uma senha valida (8 digitos numericos)
    receber_senha_valida(senha, 0);

    // Loop para encontrar uma posicao vazia de usuarios
    for (i=0; i < 10; i++){
        if (strcmp(usuarios[i].cpf, "") == 0){
            break;
        }
    }

    // Dados iniciais do usuario
    strcpy(usuarios[i].nome, nome);
    strcpy(usuarios[i].cpf, cpf);
    strcpy(usuarios[i].senha, senha);
    usuarios[i].saldo.bitcoin = 0;
    usuarios[i].saldo.ethereum = 0;
    usuarios[i].saldo.reais = 0;
    usuarios[i].saldo.ripple = 0;
    *pos = i;

    // Salva o novo usuario
//    salvar_usuarios(usuarios, pos, cotacao);

    printf("Registro concluido com sucesso!\n");

    return 1;
}

// Obter CPF valido, tambem gerencia acao de CANCELAR do usuario
void receber_cpf_valido(char *cpf, int cancelar_autorizado){
    int i;
    int cpf_valido;

    do{
        cpf_valido = 1;

        printf("Insira um CPF valido, com 11 digitos:\n");
        scanf("%s", cpf);

        // Checa se e para cancelar a operacao
        if ((strcmp(cpf, "CANCELAR") == 0) && (cancelar_autorizado)){
            break;
        }

        if (strlen(cpf) != 11){
            cpf_valido = 0;
            printf("CPF invalido! O CPF deve conter 11 digitos numericos!\n");
            continue;
        }

        for(i=0; i < strlen(cpf); i++){
            if(!isdigit(cpf[i])){
                printf("CPF invalido! O CPF deve conter numeros apenas!\n");
                cpf_valido = 0;
                break;
            }
        }
        while ((getchar()) != '\n' && getchar() != EOF);
    } while (!cpf_valido);
}

// Obter Senha valida
void receber_senha_valida(char *senha, int cancelar_autorizado){
    int i;
    int senha_valida;

    do{
        senha_valida = 1;

        printf("Insira uma Senha valida, com 8 digitos:\n");
        scanf("%s", senha);

        // Checa se e para cancelar a operacao
        if ((strcmp(senha, "CANCELAR") == 0) && (cancelar_autorizado)){
            break;
        }

        if (strlen(senha) != 8){
            printf("Senha invalida! A senha deve conter 8 digitos numericos!\n");
            senha_valida = 0;
            continue;
        }

        for(i=0; i < strlen(senha); i++){
            if(!isdigit(senha[i])){
                printf("Senha invalida! A senha deve conter numeros apenas!\n");
                senha_valida = 0;
                break;
            }
        }
        while ((getchar()) != '\n' && getchar() != EOF);
    } while (!senha_valida);
}

// Retorna a posicao do usuario logado
int logar_usuario(User usuarios[10]){

    int login_valido = 0;
    char cpf[12];
    char senha[9];
    int user;

    system("cls||clear");
    mostrar_menu("Login usuario");
    printf("Digite \"CANCELAR\" para cancelar o login \n");

    do{

        // Obter CPF e senha para checar com a dos outros usuarios
        receber_cpf_valido(cpf, 1);
        if (strcmp(cpf, "CANCELAR") == 0){
            return -1;
        }
        receber_senha_valida(senha, 0);

        // Itera sobre os usuarios para achar o usuario do operador
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
            printf("Usuario nao encontrado! Tente novamente.\n");

    } while(!login_valido);

    return user;
}

// Salva os usuarios no arquivo .bin
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

// Carrega os usuarios na variavel usuarios
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

// Valida a senha do usuario
int validar_senha(User usuarios[], int pos){
    char senha[9];

    do{
        receber_senha_valida(senha, 1);

        // Checa se o usuario cancelou a operacao
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
        while ((getchar()) != '\n' && getchar() != EOF); // Limpa o buffer em caso do usuario enviar muitos caracteres

        if(quantidade <= 0.0){
            printf("A quantidade precisa ser maior que 0!\n");
        }

    }while(quantidade <= 0.0);

    return quantidade;
}

void consultar_saldo(User usuarios[], int pos, int qnt_moedas){

    system("cls||clear");
    mostrar_menu("Consultar saldo");

    printf("Saldo de Reais: %f\n", usuarios[pos].reais);
    for (int i = 0; i < qnt_moedas; i++) {
        printf("Saldo de %s: %lf\n", usuarios[pos].saldos[i].nome, usuarios[pos].saldos[i].saldo);
    }

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void consultar_extrato(User usuarios[], int pos){
    char *extrato_data;
    int i;

    system("cls||clear");
    mostrar_menu("Consultar Extrato");

    // Itera sobre os extratos
    for(i = 0; i < 100; i++){

        // Verifica se o extrato atual e lixo, se for quebrar o loop
        extrato_data = usuarios[pos].extrato[i].data;
        if (strcmp(extrato_data, "") == 0){
            break;
        }

        printf("Data: %s\t", usuarios[pos].extrato[i].data);
        printf("Operacao: %s\t", usuarios[pos].extrato[i].operacao);
        printf("Moeda: %s\t", usuarios[pos].extrato[i].moeda);
        printf("Valor: %.2f\t", usuarios[pos].extrato[i].valor);
        printf("Taxa paga: %.2f\t", usuarios[pos].extrato[i].taxa);
        printf("Cotacao: %.2f\n", usuarios[pos].extrato[i].cotacao);
    }


    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void salvar_extrato(User usuarios[], int pos, char operacao[],
                    char moeda[], float cotacao,float valor, float taxa){
    int i;
    char *extrato_data;
    char datetime[20];
    struct tm *info;

    // Obtem a data atual e salva na variavel datetime
    time_t rawtime;
    time( &rawtime );
    info = localtime( &rawtime );
    strftime(datetime,20,"%d/%m/%Y - %H:%M", info);


    for(i = 0; i < 100; i++){

        // Verifica se o extrato atual e lixo, se for quebrar o loop
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

    system("cls||clear");
    mostrar_menu("Depositar Reais");

    // Obtem um numero maior que 0 e que nao tem caracteres
    qnt_deposito = receber_saldo_valido("reais", "depositar");


    usuarios[pos].reais += qnt_deposito;

    printf("Depositado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].reais);

    salvar_extrato(usuarios, pos, "+", "Real", 1, qnt_deposito, 0);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void sacar_reais(User usuarios[], int pos){
    float qnt_sacar;

    system("cls||clear");
    mostrar_menu("Sacar Reais");

    validar_senha(usuarios, pos);

    do{

        // Obtem um numero maior que 0 e que nao tem caracteres
        qnt_sacar = receber_saldo_valido("reais", "sacar");

        if (qnt_sacar > usuarios[pos].reais){
            printf("Voce nao tem saldo o suficiente para sacar R$ %.2f! Seu saldo em R$: %.2f\n", qnt_sacar, usuarios[pos].reais);
        }

    } while (qnt_sacar > usuarios[pos].reais);



    usuarios[pos].reais -= qnt_sacar;

    printf("Sacado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].reais);

    salvar_extrato(usuarios, pos, "-", "Real", 1, qnt_sacar, 0);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void comprar_criptomoeda(User usuarios[], int pos, Moeda *moedas, int qnt_moedas){
    char criptomoeda[10];
    float qnt_moeda;
    float taxa;
    float preco_operacao;
    float cotacao_cripto;
    int opcao, confirmacao;

    system("cls||clear");
    mostrar_menu("Comprar Cripto");

    printf("Valide sua senha antes de comprar criptomoedas, para cancelar digite \"CANCELAR\".");

    // Valida a senha antes do usuario poder comprar cripto, se o usuario digitar "CANCELAR" a operacao sera cancelada
    if (!validar_senha(usuarios, pos)) return;

    do{
        // Mostrar moedas e cotacoes
        for (int i = 0; i < qnt_moedas; ++i) {
            printf("%d - %s: %lf\n", i, moedas[i].nome, moedas[i].cotacao);
        }
        printf("Escolha uma moeda para comprar.\n");
        scanf("%d", &opcao);
        while ((getchar()) != '\n' && getchar() != EOF);

        if(opcao < 0 || opcao > qnt_moedas -1) continue;

        strcpy(criptomoeda, moedas[opcao].nome);
        cotacao_cripto = moedas[opcao].cotacao;
        taxa = moedas[opcao].taxa_compra;


    }while(!opcao && opcao != 0);

    do{
        // Obtem um numero maior que 0 e que nao tem caracteres
        qnt_moeda = receber_saldo_valido(criptomoeda, "comprar");

        preco_operacao = (qnt_moeda * (1 + taxa)  * cotacao_cripto);

        if (preco_operacao > usuarios[pos].reais){
            printf("Saldo em reais insuficiente!");
        }

    } while (preco_operacao > usuarios[pos].reais);

    printf("Para confirmar a compra digite 1: ");
    scanf("%d", &confirmacao);
    while ((getchar()) != '\n' && getchar() != EOF);

    if (confirmacao != 1){
        return;
    }

    // Parte das operacoes
    usuarios[pos].reais -= preco_operacao;
    usuarios[pos].saldos[opcao].saldo += qnt_moeda;


    printf("Compra realizada com sucesso! Total com taxa: R$ %.2f, Taxa: R$ %.2f\n", preco_operacao, preco_operacao * (taxa));
    printf("Saldo em reais atualizado: R$ %.2f\n", usuarios[pos].reais);
    // Printa o saldo da criptomoeda selecionada atualizado
    printf("Saldo em %s atualizado: %.2f\n", criptomoeda, usuarios[pos].saldos[opcao].saldo);

    salvar_extrato(usuarios, pos, "-", "Real", 1, preco_operacao, taxa);
    salvar_extrato(usuarios, pos, "+", criptomoeda, cotacao_cripto, qnt_moeda, 0);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void vender_criptomoeda(User usuarios[], int pos, Moeda *moedas, int qnt_moedas){
    char criptomoeda[10];
    float qnt_moeda;
    float taxa;
    float preco_operacao;
    float saldo_cripto;
    float cotacao_cripto;
    int opcao, confirmacao;

    system("cls||clear");
    mostrar_menu("Vender Cripto");

    printf("Valide sua senha antes de vender cripto, para cancelar digite \"CANCELAR\".");

    // Valida a senha antes do usuario poder vender cripto, se o usuario digitar "CANCELAR" a operacao sera cancelada
    if (!validar_senha(usuarios, pos)) return;

    do{
        // Mostrar moedas e cotacoes
        for (int i = 0; i < qnt_moedas; ++i) {
            printf("%d - %s: %lf\n", i, moedas[i].nome, moedas[i].cotacao);
        }
        printf("Escolha uma moeda para comprar.\n");
        scanf("%d", &opcao);
        while ((getchar()) != '\n' && getchar() != EOF);

        if(opcao < 0 || opcao > qnt_moedas -1) continue;

        strcpy(criptomoeda, moedas[opcao].nome);
        cotacao_cripto = moedas[opcao].cotacao;
        taxa = moedas[opcao].taxa_compra;
        saldo_cripto = usuarios[pos].saldos[opcao].saldo;

    }while(!opcao && opcao != 0);

    do{
        // Obtem um numero maior que 0 e que nao tem caracteres
        qnt_moeda = receber_saldo_valido(criptomoeda, "vender");

        if (qnt_moeda > saldo_cripto){
            printf("Saldo em %s insuficiente!\n", criptomoeda);
        }

    } while (qnt_moeda > saldo_cripto);

    printf("Para confirmar a venda digite 1: ");
    scanf("%d", &confirmacao);
    while ((getchar()) != '\n' && getchar() != EOF);

    if (confirmacao != 1){
        return;
    }


    // Parte das operacoes
    preco_operacao = (qnt_moeda * cotacao_cripto)/ (1 + taxa);
    usuarios[pos].reais += preco_operacao;

    // Adiciona a qnt de cripto na moeda selecionada
    usuarios[pos].saldos[opcao].saldo -= qnt_moeda;

    printf("Venda realizada com sucesso! Total ganho com taxa: R$ %.2f, Taxa: R$ %.2f\n", preco_operacao, preco_operacao * (taxa));
    printf("Saldo em reais atualizado: R$ %.2f\n", usuarios[pos].reais);
    // Printa o saldo da criptomoeda selecionada atualizado
    printf("Saldo em %s atualizado: %.2f\n", criptomoeda, usuarios[pos].saldos[opcao].saldo -= qnt_moeda);

    salvar_extrato(usuarios, pos, "-", criptomoeda, cotacao_cripto, qnt_moeda, 0);
    salvar_extrato(usuarios, pos, "+", "Real", 1, preco_operacao, taxa);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

float gerar_varicao_cotacao(){
    int num_random;

    // Número entre -500 e 500 ( simula o -5 e 5% )
    num_random = (rand() % 1001) - 500;
    return num_random / 10000.0f;
}

void atualizar_cotacao(Moeda **moedas, int qnt_moedas){
    float variacao;
    int moeda;

    system("cls||clear");
    // seed aleatória
    srand(time(NULL));

    mostrar_menu("Atualizar Cotacao");
    // Itera sobre as moedas dentro da cotação
    for (moeda = 0; moeda < qnt_moedas; moeda++) {
        printf("%s - %lf\n", (*moedas)[moeda].nome, (*moedas)[moeda].cotacao);
    }
    for (moeda = 0; moeda < qnt_moedas; moeda++){
        // Num entre -5% e 5%
        variacao = gerar_varicao_cotacao();

        (*moedas)[moeda].cotacao += (*moedas)[moeda].cotacao * variacao;

        printf("%s - %lf\n", (*moedas)[moeda].nome, (*moedas)[moeda].cotacao);
    }

//    mostrar_cotacoes("Cotacoes atualizadas", *cotacao);

    salvar_moedas(*moedas, qnt_moedas);

}

void transferir_saldo(User usuarios[], int pos, Cotacoes cotacao){

    int opcao_moeda;
    float saldo_moeda;
    char nome_moeda[10];
    float cotacao_moeda;
    float qnt_transferir;

    int pessoa_valida; // 0 invalido 1 valido
    char cpf[12];
    int user;
    system("cls||clear");
    mostrar_menu("Transferir Saldo");

    // Obtem o usuario que quer transferir o saldo
    do{
        pessoa_valida = 0;
        printf("Para qual CPF voce quer transferir o saldo? Para cancelar digite \"CANCELAR\"\n");
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
            printf("CPF nao encontrado!\n");
        }
        if (user == pos){
            printf("Você não pode transferir para si mesmo!\n");
            pessoa_valida = 0;
        }
    } while (pessoa_valida == 0);

    // Obtem a moeda que vai ser utilizada
    do{
        char *opcoes[] = {
                "Real",
                "Bitcoin",
                "Ethereum",
                "Ripple",
                NULL
        };
        mostrar_opcoes("Moedas disponiveis a transferir", opcoes);
        scanf("%d", &opcao_moeda);

        switch (opcao_moeda) {
            case 0:
                saldo_moeda = usuarios[pos].saldo.reais;
                strncpy(nome_moeda, "Real", sizeof(nome_moeda)-1);
                cotacao_moeda = 1;
                break;
            case 1:
                saldo_moeda = usuarios[pos].saldo.bitcoin;
                strncpy(nome_moeda, "Bitcoin", sizeof(nome_moeda)-1);
                cotacao_moeda = cotacao.bitcoin;
                break;
            case 2:
                saldo_moeda = usuarios[pos].saldo.ethereum;
                strncpy(nome_moeda, "Ethereum", sizeof(nome_moeda)-1);
                cotacao_moeda = cotacao.ethereum;
                break;
            case 3:
                saldo_moeda = usuarios[pos].saldo.ripple;
                strncpy(nome_moeda, "Ripple", sizeof(nome_moeda)-1);
                cotacao_moeda = cotacao.ripple;
                break;
            default:
                opcao_moeda = -1;
                printf("Opcao nao encontrada!\n");
        }
    } while (opcao_moeda == -1);

    // Obter valor valido a transferir
    do{
        // Obtem um numero maior que 0 e que nao tem caracteres
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

    printf("Moeda selecionada: %s\nQnt Transferida: %.2f\nUsuário que recebeu: %s!\n",
           nome_moeda, qnt_transferir, usuarios[user].nome);
    printf("Saldo em %s atualizado: %.2f\n", nome_moeda,
           strcmp(nome_moeda, "Real") == 0 ? usuarios[pos].saldo.reais :
           strcmp(nome_moeda, "Bitcoin") == 0 ? usuarios[pos].saldo.bitcoin :
           strcmp(nome_moeda, "Ethereum") == 0 ? usuarios[pos].saldo.ethereum :
           usuarios[pos].saldo.ripple);

    salvar_extrato(usuarios, pos, "-", nome_moeda, cotacao_moeda, qnt_transferir, 0);
    salvar_extrato(usuarios, user, "+", nome_moeda, cotacao_moeda, qnt_transferir, 0);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void mostrar_menu(char nome_menu[]){
    int nome_menu_len;
    int i;

    nome_menu_len = strlen(nome_menu) + 3;

#ifdef _WIN32
    // Altera o padrao de texto para UTF-16 para printar caracteres especiais
    _setmode(_fileno(stdout), _O_U16TEXT);

    wprintf(L"┏━━");
    for (i=0; i < nome_menu_len; i++){
        wprintf(L"━");
    }
    wprintf(L"━┓\n");

    wprintf(L"┃   ");
    _setmode(_fileno(stdout), _O_TEXT);
    printf("%s", nome_menu);
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"   ┃\n", nome_menu);

    wprintf(L"┗━");
    for (i=0; i < nome_menu_len; i++){
        wprintf(L"━");
    }
    wprintf(L"━━┛\n");

    // Volta o padrao de texto para o modo de texto padrao
    _setmode(_fileno(stdout), _O_TEXT);

#else // Caso de rodar no linux

    printf("┏━━");
    for (i=0; i < nome_menu_len; i++){
        printf("━");
    }
    printf("━┓\n");

    printf("┃   %s   ┃\n", nome_menu);

    printf("┗━");
    for (i=0; i < nome_menu_len; i++){
        printf("━");
    }
    printf("━━┛\n");

#endif

}

void mostrar_opcoes(char titulo[], char *opcoes[]){
    setlocale(LC_ALL, "");
    setlocale(LC_ALL, "portuguese");

    int nome_menu_len;
    int i, j;

    nome_menu_len = strlen(titulo) + 3;


#ifdef _WIN32
    // Altera o padrao de texto para UTF-16 para printar caracteres especiais
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Printa ┏━━「 titulo 」━━┓
    wprintf(L"┏━━");
    wprintf(L"】 ", titulo);
    _setmode(_fileno(stdout), _O_TEXT);
    printf("%s", titulo);
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L" 【", titulo);
    wprintf(L"━━┓\n");
    // Fim do print

    // Printa o meio do menu (┃ i - Opcao                |)
    i = 0;
    while (opcoes[i] != NULL) {
        wprintf(L"┃ ");
        _setmode(_fileno(stdout), _O_TEXT);
        printf("%d - %s", i, opcoes[i]);
        _setmode(_fileno(stdout), _O_U16TEXT);
        for (j = 0; j < nome_menu_len + 2 - strlen(opcoes[i]); j++){
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

    // Volta o padrao de texto para o modo de texto padrao
    _setmode(_fileno(stdout), _O_TEXT);

#else // Caso de rodar no linux

    // Printa ┏━━「 titulo 」━━┓
    printf("┏━━");
    printf("】 %s 【", titulo);
    printf("━━┓\n");
    // Fim do print

    // Printa o meio do menu (┃ i - Opcao                |)
    i = 0;
    while (opcoes[i] != NULL) {
        printf("┃ %d - %s", i, opcoes[i]);
        for (j = 0; j < nome_menu_len + 2 - strlen(opcoes[i]); j++){
            printf(" ");
        }
        printf("┃\n");
        i++;
    }
    // Fim do print

    // Printa ┗━━━━━━━━━━━━━┛
    printf("┗━━━");
    for (i=0; i < nome_menu_len; i++){
        printf("━");
    }
    printf("━━━━┛\n");
    // Fim do print

#endif
}

void mostrar_cotacoes(char titulo[], Cotacoes cotacoes) {
    setlocale(LC_ALL, "portuguese");
    setlocale(LC_ALL, "");

    int nome_menu_len;
    int i, j;
    float opcoes_cotacoes[] = {cotacoes.bitcoin, cotacoes.ethereum,
                               cotacoes.ripple};
    char *cotacoes_nomes[] = {"Bitcoin", "Ethereum", "Ripple"};
    char cotacao_preco_str[10];

    nome_menu_len = strlen(titulo) + 3;

#ifdef _WIN32
    // Altera o padrao de texto para UTF-16 para printar caracteres especiais
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Printa ┏━━「 titulo 」━━┓
    wprintf(L"┏━━");
    wprintf(L"】 ", titulo);
    _setmode(_fileno(stdout), _O_TEXT);
    printf("%s", titulo);
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L" 【", titulo);
    wprintf(L"━━┓\n");
    // Fim do print

    // Printa o meio do menu (┃ i - Opcao                |)
    for (i = 0; i < 3; i++) {
        sprintf(cotacao_preco_str, "%.2f", opcoes_cotacoes[i]);
        wprintf(L"┃ 1 %s -> R$%s", cotacoes_nomes[i], cotacao_preco_str);

        for (j = 0; j < nome_menu_len - 2 - strlen(cotacao_preco_str) -
                        strlen(cotacoes_nomes[i]);
             j++) {
            wprintf(L" ");
        }
        wprintf(L"┃\n");
    }
    // Fim do print

    // Printa ┗━━━━━━━━━━━━━┛
    wprintf(L"┗━━━");
    for (i = 0; i < nome_menu_len; i++) {
        wprintf(L"━");
    }
    wprintf(L"━━━━┛\n");
    // Fim do print

    // Volta o padrao de texto para o modo de texto padrao
    _setmode(_fileno(stdout), _O_TEXT);

#else // Caso de rodar no linux

    // Printa ┏━━「 titulo 」━━┓
  printf("┏━━");
  printf("】 %s 【", titulo);
  printf("━━┓\n");
  // Fim do print

  // Printa o meio do menu (┃ i - Opcao                |)
  for (i = 0; i < 3; i++) {
    sprintf(cotacao_preco_str, "%.2f", opcoes_cotacoes[i]);
    printf("┃ 1 %s -> R$%s", cotacoes_nomes[i], cotacao_preco_str);

    for (j = 0; j < nome_menu_len - 2 - strlen(cotacao_preco_str) -
                        strlen(cotacoes_nomes[i]);
         j++) {
      printf(" ");
    }
    printf("┃\n");
  }
  // Fim do print

  // Printa ┗━━━━━━━━━━━━━┛
  printf("┗━━━");
  for (i = 0; i < nome_menu_len; i++) {
    printf("━");
  }
  printf("━━━━┛\n");
  // Fim do print

#endif
}

void mostrar_info_user(char titulo[], User usuario) {
    setlocale(LC_ALL, "portuguese");
    setlocale(LC_ALL, "");

    int nome_menu_len;
    int num_extratos = 0;
    int *ptr_num_extratos = &num_extratos;
    int i, j;
    char *opcoes[] = {
            usuario.nome,
            usuario.cpf,
            (char *) ptr_num_extratos,
            NULL
    };

    // Acha a quantidade de extratos do usuario
    for(i = 0; i < 100; i++){
        if(usuario.extrato[i].valor == -1){
            num_extratos = i;
            break;
        }
    }

    nome_menu_len = strlen(titulo) + 3;

#ifdef _WIN32
    // Altera o padrao de texto para UTF-16 para printar caracteres especiais
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Printa ┏━━「 titulo 」━━┓
    wprintf(L"┏━━");
    wprintf(L"】 ", titulo);
    _setmode(_fileno(stdout), _O_TEXT);
    printf("%s", titulo);
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L" 【", titulo);
    wprintf(L"━━┓\n");
    // Fim do print

    // Printa o meio do menu (┃ i - Opcao                |)
    i = 0;
    while (opcoes[i] != NULL) {
        wprintf(L"┃ ");
        _setmode(_fileno(stdout), _O_TEXT);
        printf("%d - %s", i, opcoes[i]);
        for (j = 0; j < nome_menu_len + 2 - strlen(opcoes[i]) ; j++){
            printf(" ");
        }
        _setmode(_fileno(stdout), _O_U16TEXT);
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

    // Volta o padrao de texto para o modo de texto padrao
    _setmode(_fileno(stdout), _O_TEXT);

#else // Caso de rodar no linux

    // Printa ┏━━「 titulo 」━━┓
    printf("┏━━");
    printf("】 %s 【", titulo);
    printf("━━┓\n");
    // Fim do print

    // Printa o meio do menu (┃ i - Opcao                |)
    i = 0;
    while (opcoes[i] != NULL) {
        printf("┃ %d - %s", i, opcoes[i]);
        for (j = 0; j < nome_menu_len + 2 - strlen(opcoes[i]); j++){
            printf(" ");
        }
        printf("┃\n");
        i++;
    }
    // Fim do print

    // Printa ┗━━━━━━━━━━━━━┛
    printf("┗━━━");
    for (i=0; i < nome_menu_len; i++){
        printf("━");
    }
    printf("━━━━┛\n");
    // Fim do print

#endif
}

int encontrar_usuario(int *user_procurado, User usuarios[]){
    char cpf[12];
    int user_valido = 0;
    int user;

    do{
        // Obter CPF e senha para checar com a dos outros usuarios
        receber_cpf_valido(cpf, 1);

        if (strcmp(cpf, "CANCELAR") == 0) return -1;

        // Itera sobre os usuarios para achar o usuario com o CPF
        for(user = 0; user < 10; user++){

            if (strcmp(usuarios[user].cpf, "") == 0){
                break;
            }

            if (strcmp(usuarios[user].cpf, cpf) == 0){
                user_valido = 1;
                break;
            }
        }

        if (!user_valido)
            printf("Usuario nao encontrado! Tente novamente.\n");

    } while(!user_valido);

    *user_procurado = user;

    return 1;
}

int logar_administrador(Administrador administradores[]){

    int login_valido = 0;
    char cpf[12];
    char senha[9];
    int user;

    system("cls||clear");
    mostrar_menu("Login Administrador");
    printf("Digite \"CANCELAR\" para cancelar o login \n");

    do{

        // Obter CPF e senha para checar com a dos outros usuarios
        receber_cpf_valido(cpf, 1);

        if (strcmp(cpf, "CANCELAR") == 0) return -1;

        receber_senha_valida(senha, 0);

        // Itera sobre os usuarios para achar o usuario do operador
        for(user = 0; user < 10; user++){

            if (strcmp(administradores[user].cpf, "") == 0){
                break;
            }

            if (strcmp(administradores[user].cpf, cpf) == 0 && strcmp(administradores[user].senha, senha) == 0){
                login_valido = 1;
                break;
            }
        }

        if (!login_valido)
            printf("Administrador nao encontrado! Tente novamente.\n");

    } while(!login_valido);

    return user;
}

int salvar_moedas(Moeda moedas[], int qnt_moedas){
    FILE *f = fopen("moedas.bin", "wb");
    if (f == NULL){
        printf("Erro ao salvar moedas! f == NULL\n");
        return 0;
    }

    int qtd = fwrite(&qnt_moedas, sizeof(int), 1, f);
    if (qtd == 0){
        printf("ERRO AO SALVAR QNT MOEDAS!! fwrite retornou 0.\n");
        return 0;
    }

    qtd = fwrite(moedas, sizeof(Moeda), qnt_moedas, f);
    if (qtd == 0){
        printf("ERRO AO SALVAR MOEDAS!! fwrite retornou 0.\n");
        return 0;
    }

    if (fclose(f)){
        printf("ERRO AO SALVAR MOEDAS!! fclose retornou 0.\n");
        return 0;
    }

    return 1;
}

int carregar_moedas(Moeda **moedas, int *qnt_moedas, User usuarios[]){
    FILE *f = fopen("moedas.bin", "rb");
    if (f == NULL) {
        // Arquivo não existe, criar moedas padrão
        *qnt_moedas = 4;
        *moedas = (Moeda *)malloc(sizeof(Moeda) * (*qnt_moedas));
        if (*moedas == NULL){
            printf("Erro ao alocar memória para moedas padrão.\n");
            return 0;
        }

        // cria as moedas base
        criar_moeda(*moedas, 0, "KCoin", 34.3, 0.0074, 0.0086);
        criar_moeda(*moedas, 1, "Bitcoin", 425.7, 0.02, 0.03);
        criar_moeda(*moedas, 2, "Ethereum", 124.2, 0.01, 0.02);
        criar_moeda(*moedas, 3, "Ripple", 14.9, 0.01, 0.01);

        // Coloca as moedas para os usuarios
        adicionar_moeda_users(usuarios, "KCoin");
        adicionar_moeda_users(usuarios, "Bitcoin");
        adicionar_moeda_users(usuarios, "Ethereum");
        adicionar_moeda_users(usuarios, "Ripple");

        // Salvar moedas padrão no arquivo
        if (!salvar_moedas(*moedas, *qnt_moedas)){
            printf("Erro ao salvar moedas padrão.\n");
            free(*moedas);
            return 0;
        }

        return 1;
    }

    // Obter qnt moedas
    if (fread(qnt_moedas, sizeof(int), 1, f) != 1){
        printf("Erro ao ler a quantidade de moedas.\n");
        fclose(f);
        return 0;
    }

    // Alocar memória para as moedas
    *moedas = (Moeda *)malloc(sizeof(Moeda) * (*qnt_moedas));

    // Carregar moedas de fato
    fread(*moedas, sizeof(Moeda), *qnt_moedas, f);


    if (fclose(f) != 0){
        free(*moedas);
        return 0;
    }

    return 1;
}

double obter_num_valido(char num_text[]){
    double num;
    do{
        printf("%s\n", num_text);
        scanf("%lf", &num);

        if(num < 0.0){
            printf("Insira um valor maior que 0!\n");
        }
        fflush(stdin);
    } while (num < 0.0);

    return num;
}

void cadastrar_criptomoeda(Moeda **moedas, int *qnt_moedas, User usuarios[]){
    int nome_valido = 0;
    char nome[50];
    double cotacao;
    double taxa_compra;
    double taxa_venda;
    int i;

    *qnt_moedas += 1;

    mostrar_menu("Adicionar Criptomoeda");

    // Salva uma variável com a memoria temporariamente para colocar nas moedas
    Moeda *temp = realloc(*moedas, (sizeof(Moeda) * (*qnt_moedas)));
    *moedas = temp;

    // Colocar um nome válido na moeda
    while(!nome_valido){
        nome_valido = 1;
        // Colocar valores na moeda
        printf("Insira o nome da moeda: \n");
        scanf("%49s", nome);
        for(i = 0; i < *qnt_moedas; i++){
            if(strcmp((*moedas)[i].nome, nome) == 0){
                printf("Ja existe uma moeda com esse nome!\n");
                nome_valido = 0;
            }
        }

    }

    // Obter valores válidos para a moeda
    cotacao = obter_num_valido("Insira a cotacao da moeda:");
    taxa_venda = obter_num_valido("Insira a taxa de compra da moeda:");
    taxa_compra = obter_num_valido("Insira a taxa de venda da moeda:");


    criar_moeda(*moedas, (*qnt_moedas-1), nome, cotacao, taxa_compra, taxa_venda);

    adicionar_moeda_users(usuarios, nome);

    salvar_moedas(*moedas, *qnt_moedas);

    printf("Moeda criada com sucesso!\n");
}

void excluir_criptomoeda(Moeda **moedas, int *qnt_moedas, User usuarios[]){
    char nome[50];
    int moeda_valida = 0;
    int moeda_pos;
    int confirmar;
    int i;
    Moeda moeda_sel;

    mostrar_menu("Remover Criptomoeda");

    if(*qnt_moedas == 1){
        printf("No momento so existe uma criptomoeda no sistema, "
               "adicione mais moedas para remover uma moeda.\n");
        return;
    }
    // Obtem uma moeda válida para remover
    while(!moeda_valida){

        printf("Moedas disponiveis: %d\n", *qnt_moedas);
        for(i = 0; i < *qnt_moedas; i++){
            printf("%s\n",(*moedas)[i].nome);
        }

        printf("Para cancelar a operacao digite \"CANCELAR\".\n");
        printf("Insira o nome da moeda que deseja remover: \n");
        scanf("%49s", nome);

        for(i = 0; i < *qnt_moedas; i++){
            if(strcmp((*moedas)[i].nome, nome) == 0){
                moeda_valida = 1;
                moeda_pos = i;
                break;
            }
        }

        // Se cancelar sai da funcao e volta pro menu
        if(strcmp(nome, "CANCELAR") == 0) return;

        if(!moeda_valida){
            printf("Moeda nao encontrada!\n");
        }

    }

    moeda_sel = (*moedas)[moeda_pos];
    printf("Informacoes da moeda a ser excluida:\n");
    printf("Nome: %s\nCotacao: %lf\nTaxa Compra: %lf\nTaxa Venda: %lf\n",
           moeda_sel.nome, moeda_sel.cotacao,
           moeda_sel.taxa_compra, moeda_sel.taxa_venda);

    printf("Digite 1 para confirmar.\n");
    scanf("%d", &confirmar);

    if(confirmar != 1) {
        printf("Operação cancelada.\n");
        return;
    }

    for(i = moeda_pos; i < *qnt_moedas - 1; i++){
        (*moedas)[i] = (*moedas)[i+1];
    }

    *qnt_moedas -= 1;

    Moeda *temp = realloc(*moedas, (sizeof(Moeda) * (*qnt_moedas)));
    *moedas = temp;

    remover_moeda_users(usuarios, nome);

    salvar_moedas(*moedas, *qnt_moedas);

    printf("Moeda removida com sucesso!\n");
}

int cadastrar_usuario(User usuarios[]){

    char cpf[12];
    char senha[9];
    char nome[100];
    int cpf_unico;
    int i;

    system("cls||clear");
    mostrar_menu("Cadastrar usuario");

    printf("Qual o nome para o usuario?\n");
    scanf("%99s", nome);
    getchar();

    // Obtem um CPF valido (11 digitos numericos e unico)
    do{
        receber_cpf_valido(cpf, 0);
        cpf_unico = 1;

        // Checa se tem um usuario com o CPF enviado
        for (i=0; i < 10; i++){
            if (strcmp(usuarios[i].cpf, "") == 0){
                break;
            }
            else if (strcmp(usuarios[i].cpf, cpf) == 0){
                printf("Esse CPF ja esta sendo utilizado!\n");
                cpf_unico = 0;
                break;
            }
        }
    }while(!cpf_unico);



    // Obtem uma senha valida (8 digitos numericos)
    receber_senha_valida(senha, 0);

    // Loop para encontrar uma posição vazia para o novo usuário
    for (i = 0; i < 10; i++) {
        if (strcmp(usuarios[i].cpf, "") == 0) {
            break;
        }
    }

    // Dados iniciais do usuario
    strcpy(usuarios[i].nome, nome);
    strcpy(usuarios[i].cpf, cpf);
    strcpy(usuarios[i].senha, senha);

    printf("Cadastro concluido com sucesso!\n");

    return 1;
}

void excluir_usuario(User usuarios[]){
    int user;
    int confirmacao;
    int i;

    mostrar_menu("Excluir Usuario");
    printf("Digite \"CANCELAR\" para cancelar a exclusao\n");

    printf("Insira o CPF do usuario que deseja excluir:\n");
    encontrar_usuario(&user, usuarios);

    mostrar_info_user("Infos do usuario", usuarios[user]);

    printf("Para prosseguir digite 1, para cancelar digite 0:\n");
    scanf("%d", &confirmacao);
    if (!confirmacao) return; // Checa se cancelou

    for (i = user; i < 9; i++) {
        usuarios[i] = usuarios[i + 1];
    }

    // Seta todos os bytes da struct para 0 resetando os dados do usuario
    memset(&usuarios[8], 0, sizeof(usuarios[user]));
    printf("Usuario excluido com sucesso!\n");
}

void consultar_extrato_admin(User usuarios[]){
    char *extrato_data;
    int user_valido;
    char cpf[12];
    int user;
    int i;

    do{

        printf("Insira o CPF do usuario para ver seu extrato:\n");
        // Obter CPF e senha para checar com a dos outros usuarios
        receber_cpf_valido(cpf, 1);
        if (strcmp(cpf, "CANCELAR") == 0){
            return;
        }

        // Itera sobre os usuarios para achar o usuario com o CPF
        for(user = 0; user < 10; user++){

            if (strcmp(usuarios[user].cpf, "") == 0){
                break;
            }

            if (strcmp(usuarios[user].cpf, cpf) == 0){
                user_valido = 1;
                break;
            }
        }

        if (!user_valido)
            printf("Usuario nao encontrado! Tente novamente.\n");

    } while(!user_valido);

    // Itera sobre os extratos do usuario
    for(i = 0; i < 100; i++){

        // Verifica se o extrato atual e lixo, se for quebrar o loop
        extrato_data = usuarios[user].extrato[i].data;
        if (strcmp(extrato_data, "") == 0){
            break;
        }

        printf("Data: %s\t", usuarios[user].extrato[i].data);
        printf("Operacao: %s\t", usuarios[user].extrato[i].operacao);
        printf("Moeda: %s\t", usuarios[user].extrato[i].moeda);
        printf("Valor: %.2f\t", usuarios[user].extrato[i].valor);
        printf("Taxa paga: %.2f\t", usuarios[user].extrato[i].taxa);
        printf("Cotacao: %.2f\n", usuarios[user].extrato[i].cotacao);
    }
}

void criar_moeda(Moeda *moedas, int pos_moeda, char *nome,
                 double cotacao, double taxa_compra, double taxa_venda){

    strcpy(moedas[pos_moeda].nome, nome);
    moedas[pos_moeda].cotacao = cotacao;
    moedas[pos_moeda].taxa_compra = taxa_compra;
    moedas[pos_moeda].taxa_venda = taxa_venda;

}

void adicionar_moeda_users(User usuarios[], char *nome_moeda){
    for(int i = 0; i < 10; i++) {

        if (strcmp(usuarios[i].nome, "") == 0){
            break;
        }

        usuarios[i].saldos_size += 1;

        Moedas_User *temp = realloc(usuarios[i].saldos, sizeof(Moedas_User) * usuarios[i].saldos_size);
        if (temp == NULL) {
            perror("Erro ao realocar memória para adicionar saldos dos usuarios");
            exit(EXIT_FAILURE);
        }
        usuarios[i].saldos = temp;

        strcpy(usuarios[i].saldos[usuarios[i].saldos_size - 1].nome, nome_moeda);
        usuarios[i].saldos[usuarios[i].saldos_size - 1].saldo = 0.0;

    }
}

void remover_moeda_users(User usuarios[], char *nome_moeda){
    int i,j;
    int moeda;
    for(i = 0; i < 10; i++) {

        // checar se está vazio
        if (strcmp(usuarios[i].nome, "") == 0){
            break;
        }

        // achar moeda pra remover
        for(j = 0 ; j < usuarios[i].saldos_size; j++){
            if(strcmp(usuarios[i].saldos[j].nome, nome_moeda) == 0){
                moeda = j;
            }
        }

        for (j = moeda; j < usuarios[i].saldos_size - 1; j++) {
            usuarios[i].saldos[j] = usuarios[i].saldos[j+1];
        }

        usuarios[i].saldos_size -= 1;

        Moedas_User *temp = realloc(usuarios[i].saldos, sizeof(Moedas_User) * usuarios[i].saldos_size);
        if (temp == NULL) {
            perror("Erro ao realocar memória para remover saldos dos usuarios");
            exit(EXIT_FAILURE);
        }
        usuarios[i].saldos = temp;
    }
}


#pragma clang diagnostic pop
