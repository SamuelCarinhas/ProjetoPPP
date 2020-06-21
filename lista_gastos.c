#include "lista_gastos.h"

#include "bibliotecas.h"

#define TAM_LISTA 10

static struct elemento_gastos lista[TAM_LISTA];
static  struct elemento_gastos vazio = {"", -1, -1};
static int primeira_posicao, ultima_posicao;

static int obterPosicaoDisponivel() {
    for(int i = 0; i < TAM_LISTA; i++) if(!lista[i].validade) return i;
    return ERRO_NAO_ENCONTRADO;
}

void inicializarListaGastos() {
    for(int i = 0; i < TAM_LISTA; i++) lista[i] = vazio;
    primeira_posicao = -1;
}

int adicionarGasto(struct gastos gastos) {
    int posicao_inserir = obterPosicaoDisponivel();
    if(posicao_inserir == ERRO_NAO_ENCONTRADO) return ERRO_ESPACO;                                                      // Lista cheia
    struct elemento_gastos inserir = {gastos, 1, primeira_posicao};
    if(ultima_posicao != -1) lista[ultima_posicao].proximo_elemento = posicao_inserir;
    if(primeira_posicao == -1) primeira_posicao = posicao_inserir;
    lista[posicao_inserir] = inserir;
    lista[posicao_inserir].proximo_elemento = primeira_posicao;
    ultima_posicao = posicao_inserir;
    return SUCESSO;
}

struct elemento_gastos * obterPrimeiroGasto() {
    if(primeira_posicao == -1) return &vazio;
    return &lista[primeira_posicao];
}

struct elemento_gastos * obterGasto(int i) {
    if(primeira_posicao == -1) return &vazio;
    return &lista[i];
}

