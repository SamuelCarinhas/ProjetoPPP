#ifndef PROJETO_PPP_LISTA_ORCAMENTOS_H
#define PROJETO_PPP_LISTA_ORCAMENTOS_H

#endif

#include "constantes.h"

struct orcamento {
    char tipo[MAX_STRING];
    double montante;
};

struct elemento_orcamento {
    struct orcamento orcamento;
    int validade;
    int proximo_elemento;
};

void inicializarListaOrcamentos();
void percorrerListaOrcamentos();
int adicionarOrcamento(struct orcamento);
struct elemento_orcamento * obterPrimeiroOrcamento();
struct elemento_orcamento * obterOrcamento(int);
