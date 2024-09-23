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

int registrar_usuario(User usuarios[10], int *pos);
void receber_cpf_valido(char *cpf);
void receber_senha_valida(char *senha);

int salvar_usuarios(User usuarios[], int *pos);
int carregar_usuarios(User usuarios[], int *pos);

void menu_opcoes(User usuarios[10], int pos);


int validar_senha(User usuarios[], int pos);
void depositar_reais(User usuarios[], int pos);
void sacar_reais(User usuarios[], int pos);
