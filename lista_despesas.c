#include "lista_despesas.h"
#include "bibliotecas.h"

#define TAM_LISTA 1000

static struct elemento_despesa lista[TAM_LISTA];
static int primeira_posicao, ultima_posicao;
struct elemento_despesa vazio = {{"", 0}, 0, -1};

static int obterPosicaoDisponivel() {
    for(int i = 0; i < TAM_LISTA; i++) if(!lista[i].validade) return i;
    return ERRO_NAO_ENCONTRADO;
}

void inicializarListaDespesas() {
    for(int i = 0; i < TAM_LISTA; i++) lista[i] = vazio;
    primeira_posicao = -1;
}

int adicionarDespesa(struct despesa despesa) {
    int posicao_inserir = obterPosicaoDisponivel();
    if(posicao_inserir == ERRO_NAO_ENCONTRADO) return ERRO_ESPACO;                                                      // Lista cheia
    struct elemento_despesa inserir = {despesa, 1, primeira_posicao};
    if(ultima_posicao != -1) lista[ultima_posicao].proximo_elemento = posicao_inserir;
    if(primeira_posicao == -1) primeira_posicao = posicao_inserir;
    lista[posicao_inserir] = inserir;
    lista[posicao_inserir].proximo_elemento = primeira_posicao;
    ultima_posicao = posicao_inserir;
    return SUCESSO;
}

void percorrerListaDespesas() {
    int pos = primeira_posicao;
    while(1) {
        struct elemento_despesa atual = lista[pos];

        printf("Despesa:\n\tDescrição: %s\n\tTipo: %s\n\tMontant: %.2f\n", atual.despesa.descricao, atual.despesa.tipo, atual.despesa.montante);

        pos = atual.proximo_elemento;
        if(pos == primeira_posicao) break;
    }
}

struct elemento_despesa * obterPrimeiraDespesa() {
    if(primeira_posicao == -1) return &vazio;
    return &lista[primeira_posicao];
}

struct elemento_despesa * obterDespesa(int i) {
    if(primeira_posicao == -1) return &vazio;
    return &lista[i];
}
