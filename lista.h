#ifndef LISTA_H
#define LISTA_H

typedef struct {

    char sigla_tribunal[10];
    char municipio_oj[100];
    int casos_novos_2026;
    int julgados_2026;

}Tribunal;

typedef struct No{
    Tribunal dados;
    struct No* prox;
}No;

typedef struct {
     No *inicio;
}Lista;


void initLista(Lista *L);
void inserirNoFim(Lista *L, Tribunal T);
void lerArquivoCSV(char *nomearq, Lista *L);

#endif
