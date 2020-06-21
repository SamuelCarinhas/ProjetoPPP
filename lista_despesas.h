#ifndef PROJETO_PPP_LISTA_DESPESAS_H
#define PROJETO_PPP_LISTA_DESPESAS_H

#endif

#include "constantes.h"

struct despesa {
    char descricao[MAX_STRING];
    char tipo[MAX_STRING];
    double montante;
};

struct elemento_despesa {
    struct despesa despesa;
    int validade;
    int proximo_elemento;
};

void inicializarListaDespesas();
void percorrerListaDespesas();
int adicionarDespesa(struct despesa);
struct elemento_despesa * obterPrimeiraDespesa();
struct elemento_despesa * obterDespesa(int);
