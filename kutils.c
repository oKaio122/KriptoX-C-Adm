#include "kutils.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"
int registrar_usuario(User usuarios[10], int *pos, Cotacoes *cotacao){

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
    salvar_usuarios(usuarios, pos, cotacao);

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

    printf("Logado com sucesso!\n");

    return user;
}

// Salva os usuarios no arquivo .bin
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

// Carrega os usuarios na variavel usuarios
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
        fflush(stdin); // Limpa o buffer em caso do usuario enviar muitos caracteres

        if(quantidade <= 0.0){
            printf("A quantidade precisa ser maior que 0!\n");
        }

    }while(quantidade <= 0.0);

    return quantidade;
}

void consultar_saldo(User usuarios[], int pos, Cotacoes cotacao){

    system("cls||clear");
    mostrar_menu("Consultar saldo");

    printf("Saldo de Reais: %f\n", usuarios[pos].saldo.reais);
    printf("Saldo de Bitcoin: %f\n", usuarios[pos].saldo.bitcoin);
    printf("Saldo de Ethereum: %f\n", usuarios[pos].saldo.ethereum);
    printf("Saldo em Ripple: %f\n", usuarios[pos].saldo.ripple);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void consultar_extrato(User usuarios[], int pos, Cotacoes cotacao){
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

void depositar_reais(User usuarios[], int pos, Cotacoes cotacao){
    float qnt_deposito;

    system("cls||clear");
    mostrar_menu("Depositar Reais");

    // Obtem um numero maior que 0 e que nao tem caracteres
    qnt_deposito = receber_saldo_valido("reais", "depositar");


    usuarios[pos].saldo.reais += qnt_deposito;

    printf("Depositado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].saldo.reais);

    salvar_extrato(usuarios, pos, "+", "Real", 1, qnt_deposito, 0);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void sacar_reais(User usuarios[], int pos, Cotacoes cotacao){
    float qnt_sacar;

    system("cls||clear");
    mostrar_menu("Sacar Reais");

    validar_senha(usuarios, pos);

    do{

        // Obtem um numero maior que 0 e que nao tem caracteres
        qnt_sacar = receber_saldo_valido("reais", "sacar");

        if (qnt_sacar > usuarios[pos].saldo.reais){
            printf("Voce nao tem saldo o suficiente para sacar R$ %.2f! Seu saldo em R$: %.2f\n", qnt_sacar, usuarios[pos].saldo.reais);
        }

    } while (qnt_sacar > usuarios[pos].saldo.reais);



    usuarios[pos].saldo.reais -= qnt_sacar;

    printf("Sacado com sucesso!\n");
    printf("Saldo em reais atualizado: %.2f\n", usuarios[pos].saldo.reais);

    salvar_extrato(usuarios, pos, "-", "Real", 1, qnt_sacar, 0);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

void comprar_criptomoeda(User usuarios[], int pos, Cotacoes cotacao){
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


    // Implementar cotacao
    mostrar_cotacoes("Cotacao Atual", cotacao);

    do{
        char *opcoes[] = {
                "Bitcoin",
                "Ethereum",
                "Ripple",
                NULL
        };
        mostrar_opcoes("Criptomoedas disponiveis", opcoes);
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 0:
                strncpy(criptomoeda, "Bitcoin", sizeof(criptomoeda)-1);
                taxa = 0.02;
                cotacao_cripto = cotacao.bitcoin;
                break;
            case 1:
                strncpy(criptomoeda, "Ethereum", sizeof(criptomoeda)-1);
                taxa = 0.01;
                cotacao_cripto = cotacao.ethereum;
                break;
            case 2:
                strncpy(criptomoeda, "Ripple", sizeof(criptomoeda)-1);
                taxa = 0.01;
                cotacao_cripto = cotacao.ripple;
                break;
            default:
                printf("Opcao nao encontrada\n");
                break;
        }

    }while(!opcao && opcao != 0);
    do{
        // Obtem um numero maior que 0 e que nao tem caracteres
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

    // Parte das operacoes
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

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
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

    system("cls||clear");
    mostrar_menu("Vender Cripto");

    printf("Valide sua senha antes de vender cripto, para cancelar digite \"CANCELAR\".");

    // Valida a senha antes do usuario poder vender cripto, se o usuario digitar "CANCELAR" a operacao sera cancelada
    if (!validar_senha(usuarios, pos)) return;

    // Implementar cotacao
    mostrar_cotacoes("Cotacao Atual", cotacao);

    do{
        char *opcoes[] = {
                "Bitcoin",
                "Ethereum",
                "Ripple",
                NULL
        };
        mostrar_opcoes("Criptomoedas disponiveis", opcoes);
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 0:
                strncpy(criptomoeda, "Bitcoin", sizeof(criptomoeda)-1);
                saldo_cripto = usuarios[pos].saldo.bitcoin;
                cotacao_cripto = cotacao.bitcoin;
                taxa = 0.03;
                break;
            case 1:
                strncpy(criptomoeda, "Ethereum", sizeof(criptomoeda)-1);
                saldo_cripto = usuarios[pos].saldo.ethereum;
                cotacao_cripto = cotacao.ethereum;
                taxa = 0.02;
                break;
            case 2:
                strncpy(criptomoeda, "Ripple", sizeof(criptomoeda)-1);
                saldo_cripto = usuarios[pos].saldo.ripple;
                cotacao_cripto = cotacao.ripple;
                taxa = 0.01;
                break;
            default:
                printf("Opcao nao encontrada\n");
                break;
        }

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
    getchar();

    if (confirmacao != 1){
        return;
    }


    // Parte das operacoes
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

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

float gerar_varicao_cotacao(){
    int num_random;

    // seed aleatoria
    srand(time(NULL));

    // Numero entre -500 e 500 ( simula o -5 e 5% )
    num_random = (rand() % 1001) - 500;
    return num_random / 10000.0f;
}

void atualizar_cotacao(User usuarios[10], int pos, Cotacoes *cotacao){

    float variacao;
    int moeda;

    system("cls||clear");
    mostrar_menu("Atualizar Cotacao");

    // Itera sobre as moedas dentro da cotacao
    for (moeda = 0; moeda < 3; moeda++){

        // Num entre -5% e 5%
        variacao = gerar_varicao_cotacao();

        switch (moeda) {
            case 0:
                // Pega o valor inicial e soma com o resultado da multiplicacao da soma do 1ºrand com o 2ºrand / 100 + 100 da porcentagem
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
    printf("Cotacoes atualizadas:\n");
    printf("BTC atualizada: %f\n", cotacao->bitcoin);
    printf("ETH atualizado: %f\n", cotacao->ethereum);
    printf("Ripple atualizado: %f\n", cotacao->ripple);

    salvar_usuarios(usuarios, &pos, cotacao);

    printf("Aperte Enter para voltar ao menu de opcoes.\n");
    getchar(); // Recebe o \n do Enter
}

// Utilizada em caso das cotacoes estarem vazias
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
    } while (pessoa_valida == 0);

    // Obtem a moeda que vai ser utilizada
    do{
        printf("Qual moeda voce quer transferir?\n");
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
                printf("Opcao nao encontrada!\n");
        }
    } while (opcao_moeda == 0);

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

    printf("Dinheiro transferido com sucesso!\n");
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

    wprintf(L"┃   %s   ┃\n", nome_menu);

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
    wprintf(L"】 %s 【", titulo);
    wprintf(L"━━┓\n");
    // Fim do print

    // Printa o meio do menu (┃ i - Opcao                |)
    i = 0;
    while (opcoes[i] != NULL) {
        wprintf(L"┃ %d - %s", i, opcoes[i]);
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
    wprintf(L"】 %s 【", titulo);
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

#pragma clang diagnostic pop
