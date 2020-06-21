#include "bibliotecas.h"
#include "lista_orcamentos.h"
#include "lista_despesas.h"
#include "lista_gastos.h"
#include "funcoes.h"

void prepararOrcamentos(char *);
void prepararDespesas(char *);
void prepararGastos(void);
void mostrarGastosFinais(void);
void mostrarGastos10(void);

int main(void) {
    char * ficheiroDespesas = NULL, * ficheiroOrcamentos = NULL;

    prepararFicheiros(&ficheiroDespesas, &ficheiroOrcamentos);

    if(ficheiroDespesas == NULL || ficheiroOrcamentos == NULL) return ERRO_GERAL;


    prepararOrcamentos(ficheiroOrcamentos);
    prepararDespesas(ficheiroDespesas);
    prepararGastos();

    mostrarGastosFinais();
    mostrarGastos10();

    return 0;
}

void prepararDespesas(char * ficheiroDespesas) {
    FILE * ficheiro = fopen(ficheiroDespesas, "rb");

    inicializarListaDespesas();

    while(1) {
        struct despesa despesa;
        fread(&despesa, sizeof(struct despesa), 1, ficheiro);
        if(feof(ficheiro)) break;

        if(adicionarDespesa(despesa) != SUCESSO) {
            fprintf(stderr, "Lista de orçamentos cheia.\n");
            break;
        }
    }

    fclose(ficheiro);
}

void prepararOrcamentos(char * ficheiroOrcamentos) {
    FILE * ficheiro = fopen(ficheiroOrcamentos, "rb");

    inicializarListaOrcamentos();

    while(1) {
        struct orcamento orcamento;
        fread(&orcamento, sizeof(struct orcamento), 1, ficheiro);
        if(feof(ficheiro)) break;

        if(adicionarOrcamento(orcamento) != SUCESSO) {
            fprintf(stderr, "Lista de orçamentos cheia.\n");
            break;
        }
    }

    fclose(ficheiro);
}

void prepararGastos(void) {

    inicializarListaGastos();

    struct elemento_orcamento * orcamento_atual = obterPrimeiroOrcamento();
    double gastos;
    do {
        gastos = 0;
        struct elemento_despesa * despesa_atual = obterPrimeiraDespesa();
        do {
            if(strcasecmp(despesa_atual->despesa.tipo, orcamento_atual->orcamento.tipo) == 0)
                gastos += despesa_atual->despesa.montante;
            despesa_atual = obterDespesa(despesa_atual->proximo_elemento);
        } while(despesa_atual != obterPrimeiraDespesa());

        struct gastos gasto;
        strcpy(gasto.tipo, orcamento_atual->orcamento.tipo);
        gasto.orcamento = orcamento_atual->orcamento.montante;
        gasto.gastosFinais = gastos;

        adicionarGasto(gasto);

        orcamento_atual = obterOrcamento(orcamento_atual->proximo_elemento);
    } while(orcamento_atual != obterPrimeiroOrcamento());

}

void mostrarGastosFinais(void) {
    FILE * ficheiro_escrita = NULL;

    printf("Introduza o nome do ficheiro a guardar os dados gerais sobre os gastos: ");
    while(ficheiro_escrita == NULL) {
        char linha[MAX_STRING];
        int resultado;
        resultado = lerLinha(stdin, linha, MAX_STRING);
        while (resultado != 1) {
            if(resultado == ERRO_ESPACO) {
                fprintf(stderr, "Nome do ficheiro demasiado grande\n");
            } else if(resultado == EOF) {
                fprintf(stderr, "Nome do ficheiro não encontrado\n");
            }
            resultado = lerLinha(stdin, linha, MAX_STRING);
        }

        ficheiro_escrita = fopen(linha, "w");
        if(ficheiro_escrita == NULL) {
            fprintf(stderr, "Erro ao escrever no ficheiro\n");
        }
    }

    struct elemento_gastos * gasto_atual = obterPrimeiroGasto();
    do {
        fprintf(ficheiro_escrita, "%s#%.2f\n", gasto_atual->gastos.tipo, gasto_atual->gastos.gastosFinais);
        gasto_atual = obterGasto(gasto_atual->proximo_elemento);
    } while(gasto_atual != obterPrimeiroGasto());

    fclose(ficheiro_escrita);
}

void mostrarGastos10(void) {
    FILE * ficheiro_escrita = NULL;

    printf("Introduza o nome do ficheiro a guardar os dados sobre os gastos que excederam 10%% do orçamento: ");
    while(ficheiro_escrita == NULL) {
        char linha[MAX_STRING];
        int resultado;
        resultado = lerLinha(stdin, linha, MAX_STRING);
        while (resultado != 1) {
            if(resultado == ERRO_ESPACO) {
                fprintf(stderr, "Nome do ficheiro demasiado grande\n");
            } else if(resultado == EOF) {
                fprintf(stderr, "Nome do ficheiro não encontrado\n");
            }
            resultado = lerLinha(stdin, linha, MAX_STRING);
        }

        ficheiro_escrita = fopen(linha, "w");
        if(ficheiro_escrita == NULL) {
            fprintf(stderr, "Erro ao escrever no ficheiro\n");
        }
    }

    struct elemento_gastos * gasto_atual = obterPrimeiroGasto();
    do {
        if(gasto_atual->gastos.gastosFinais >= gasto_atual->gastos.orcamento*1.1) {
            fprintf(ficheiro_escrita, "%s#%.2f\n", gasto_atual->gastos.tipo, gasto_atual->gastos.gastosFinais-gasto_atual->gastos.orcamento);
        }
        gasto_atual = obterGasto(gasto_atual->proximo_elemento);
    } while(gasto_atual != obterPrimeiroGasto());
}
