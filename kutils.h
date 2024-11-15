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
} Moeda;

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

void menu_opcoes(User usuarios[10], int pos, Cotacoes *cotacao);

int registrar_usuario(User usuarios[10], int *pos, Cotacoes *cotacao);
int logar_usuario(User usuarios[10]);

float receber_saldo_valido(char nome_saldo[], char operacao[]);
void receber_cpf_valido(char *cpf, int cancelar_autorizado);
void receber_senha_valida(char *senha, int cancelar_autorizado);
int validar_senha(User usuarios[], int pos);
void iniciar_cotacoes(Cotacoes *cotacao);
void mostrar_menu(char nome_menu[]);
void mostrar_opcoes(char titulo[], char *opcoes[]);
void mostrar_opcoes(char titulo[], char *opcoes[]);
void mostrar_cotacoes(char titulo[], Cotacoes cotacoes);

int salvar_usuarios(User usuarios[], int *pos, Cotacoes *cotacao);
int carregar_usuarios(User usuarios[], int *pos, Cotacoes *cotacao);

void depositar_reais(User usuarios[], int pos, Cotacoes cotacao);
void sacar_reais(User usuarios[], int pos, Cotacoes cotacao);
void consultar_saldo(User usuarios[], int pos, Cotacoes cotacao);
void consultar_extrato(User usuarios[], int pos, Cotacoes cotacao);
void comprar_criptomoeda(User usuarios[], int pos, Cotacoes cotacao);
void vender_criptomoeda(User usuarios[], int pos, Cotacoes cotacao);
void salvar_extrato(User usuarios[], int pos, char operacao[],char moeda[], float cotacao,float valor, float taxa);
void atualizar_cotacao(User usuarios[], int pos, Cotacoes *cotacao);
void transferir_saldo(User usuarios[], int pos, Cotacoes cotacao);

int encontrar_usuario(char *ptr_cpf_procurado[], int user, User usuarios[]);
int logar_administrador(Administrador administradores[]);
void menu_opcoes_admin(Moeda *moedas, int *qnt_moedas, User usuarios[]);
int salvar_moedas(Moeda moedas[], int qnt_moedas);
