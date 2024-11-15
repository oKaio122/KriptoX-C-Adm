#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#ifdef _WIN32
#include <io.h>     // Setar UTF 16
#include <fcntl.h>  // Setar UTF 16
#endif

typedef struct {
    char nome[50];
    double cotacao;
    double taxa_compra;
    double taxa_venda;
} Moeda;

typedef struct {
    char nome[50];
    double saldo;
} Moedas_User;

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
    float valor;
    float taxa;
} Extrato;

typedef struct {
    char nome[255];
    char cpf[12];
    char senha[9];
    double reais;
    Moedas_User *saldos;
    int saldos_size;
    Saldo saldo;
    Extrato extrato[100];
} User;

typedef struct {
    float bitcoin;
    float ethereum;
    float ripple;
} Cotacoes;

typedef struct {
    char nome[255];
    char cpf[12];
    char senha[9];
} Administrador;

// Funções gerais
int registrar_usuario(User usuarios[10], int *pos);
int logar_usuario(User usuarios[10]);
float receber_saldo_valido(char nome_saldo[], char operacao[]);
void receber_cpf_valido(char *cpf, int cancelar_autorizado);
void receber_senha_valida(char *senha, int cancelar_autorizado);
int validar_senha(User usuarios[], int pos);
void mostrar_menu(char nome_menu[]);
void mostrar_opcoes(char titulo[], char *opcoes[]);
void mostrar_opcoes(char titulo[], char *opcoes[]);
void mostrar_cotacoes(char titulo[], Cotacoes cotacoes);
int salvar_usuarios(User usuarios[], int *pos);
int carregar_usuarios(User usuarios[], int *pos);
void menu_opcoes(User usuarios[10], int pos, Moeda *moedas, int *qnt_moedas);
void atualizar_cotacao(Moeda **moedas, int qnt_moedas); // Geral pq tá em usuário e admin também
void salvar_extrato(User usuarios[], int pos, char operacao[],char moeda[], float cotacao,float valor, float taxa);

// Funções usuário
void depositar_reais(User usuarios[], int pos);
void sacar_reais(User usuarios[], int pos);
void consultar_saldo(User usuarios[], int pos, int qnt_moedas);
void consultar_extrato(User usuarios[], int pos);
void comprar_criptomoeda(User usuarios[], int pos, Moeda *moedas, int qnt_moedas);
void vender_criptomoeda(User usuarios[], int pos, Cotacoes cotacao);
void transferir_saldo(User usuarios[], int pos, Cotacoes cotacao);

// Parte de Admin
int encontrar_usuario(int *user_procurado, User usuarios[]);
int logar_administrador(Administrador administradores[]);
void menu_opcoes_admin(Moeda *moedas, int *qnt_moedas, User usuarios[]);
int salvar_moedas(Moeda moedas[], int qnt_moedas);
int carregar_moedas(Moeda **moedas, int *qnt_moedas, User usuarios[]);
void cadastrar_criptomoeda(Moeda **moedas, int *qnt_moedas, User usuarios[]);
void excluir_criptomoeda(Moeda **moedas, int *qnt_moedas, User usuarios[]);
double obter_num_valido(char num_text[]);
int cadastrar_usuario(User usuarios[]);
void excluir_usuario(User usuarios[]);
void consultar_extrato_admin(User usuarios[]);
void mostrar_info_user(char titulo[], User usuario);
void criar_moeda(Moeda *moedas, int pos_moeda, char *nome, double cotacao, double taxa_compra, double taxa_venda);
void adicionar_moeda_users(User usuarios[], char *nome_moeda);
void remover_moeda_users(User usuarios[], char *nome_moeda);
