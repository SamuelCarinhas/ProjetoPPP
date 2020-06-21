#include "funcoes.h"

int lerLinha(FILE * ficheiro, char * linha, int tamanhoMax) {
    int c, i = 0;

    while((c = fgetc(ficheiro)) != '\n' && c != '\r') {
        if(c == EOF) return c;
        if(i == tamanhoMax) break;
        linha[i++] = (char) c;
    }

    if(i >= tamanhoMax - 1) {
        if(c != '\n')
            while(fgetc(ficheiro) != '\n');                                                                             // Ler o resto da linha até o \n
        return ERRO_ESPACO;
    } else if(c == '\r') fgetc(ficheiro);                                                                               // Ler o \n

    linha[i] = '\0';
    return 1;
}

void prepararFicheiros(char ** ficheiroDespesas, char ** ficheiroOrcamentos) {
    FILE * ficheiroConfig = fopen("config.txt", "r");
    if(ficheiroConfig == NULL) {
        fprintf(stderr, "O programa não conseguiu encontrar o ficheiro config.txt");
        return;
    }

    char linha[MAX_STRING];
    int resultado = lerLinha(ficheiroConfig, linha, MAX_STRING);
    if(resultado == ERRO_ESPACO) {
        fprintf(stderr, "Nome do ficheiro despesas demasiado longo.");
        fclose(ficheiroConfig);
        return;
    } else if(resultado == EOF) {
        fprintf(stderr, "Nome do ficheiro despesas não encontrado.");
        fclose(ficheiroConfig);
        return;
    }

    *ficheiroDespesas = malloc(MAX_STRING);
    strcpy(*ficheiroDespesas, linha);

    resultado = lerLinha(ficheiroConfig, linha, MAX_STRING);
    if(resultado == ERRO_ESPACO) {
        fprintf(stderr, "Nome do ficheiro orçamento demasiado longo.");
        fclose(ficheiroConfig);
        return;
    } else if(resultado == EOF) {
        fprintf(stderr, "Nome do ficheiro orçamento não encontrado.");
        fclose(ficheiroConfig);
        return;
    }

    *ficheiroOrcamentos = malloc(MAX_STRING);
    strcpy(*ficheiroOrcamentos, linha);

    fclose(ficheiroConfig);
}
