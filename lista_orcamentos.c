#include "lista_orcamentos.h"
#include "bibliotecas.h"

#define TAM_LISTA 10

static struct elemento_orcamento lista[TAM_LISTA];
static  struct elemento_orcamento vazio = {{"", 0}, 0, -1};
static int primeira_posicao, ultima_posicao;

static int obterPosicaoDisponivel() {
    for(int i = 0; i < TAM_LISTA; i++) if(!lista[i].validade) return i;
    return ERRO_NAO_ENCONTRADO;
}

void inicializarListaOrcamentos() {
    for(int i = 0; i < TAM_LISTA; i++) lista[i] = vazio;
    primeira_posicao = -1;
}

int adicionarOrcamento(struct orcamento orcamento) {
    int posicao_inserir = obterPosicaoDisponivel();
    if(posicao_inserir == ERRO_NAO_ENCONTRADO) return ERRO_ESPACO;                                                      // Lista cheia
    struct elemento_orcamento inserir = {orcamento, 1, primeira_posicao};
    if(ultima_posicao != -1) lista[ultima_posicao].proximo_elemento = posicao_inserir;
    if(primeira_posicao == -1) primeira_posicao = posicao_inserir;
    lista[posicao_inserir] = inserir;
    lista[posicao_inserir].proximo_elemento = primeira_posicao;
    ultima_posicao = posicao_inserir;
    return SUCESSO;
}

void percorrerListaOrcamentos() {
    int pos = primeira_posicao;
    while(1) {
        struct elemento_orcamento atual = lista[pos];

        printf("Orçamento:\n\tTipo:%s\n\tMontant:%.2f\n", atual.orcamento.tipo, atual.orcamento.montante);

        pos = atual.proximo_elemento;
        if(pos == primeira_posicao) break;
    }
}

struct elemento_orcamento * obterPrimeiroOrcamento() {
    if(primeira_posicao == -1) return &vazio;
    return &lista[primeira_posicao];
}

struct elemento_orcamento * obterOrcamento(int i) {
    if(primeira_posicao == -1) return &vazio;
    return &lista[i];
}
