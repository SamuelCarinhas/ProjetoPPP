#ifndef PROJETO_PPP_LISTA_GASTOS_H
#define PROJETO_PPP_LISTA_GASTOS_H

#endif

#include "constantes.h"

struct gastos {
    char tipo[MAX_STRING];
    double orcamento;
    double gastosFinais;
};

struct elemento_gastos {
    struct gastos gastos;
    int validade;
    int proximo_elemento;
};

void inicializarListaGastos();
int adicionarGasto(struct gastos);
struct elemento_gastos * obterPrimeiroGasto();
struct elemento_gastos * obterGasto(int);
