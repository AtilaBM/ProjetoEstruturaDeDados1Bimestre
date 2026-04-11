#ifndef LISTA_H
#define LISTA_H

typedef struct {

    char sigla_tribunal[10];
    char municipio_oj[100];
    
    // Variáveis da Meta 1
    int casos_novos_2026;
    int julgados_2026;
    int dessobrestados_2026;
    int suspensos_2026;

    // Variáveis da Meta 2A e 2Ant
    int julgm2_a;
    int distm2_a;
    int suspm2_a;
    int julgm2_ant;
    int distm2_ant;
    int suspm2_ant;
    int desom2_ant;

    // Variáveis da Meta 4A e 4B
    int julgm4_a;
    int distm4_a;
    int suspm4_a;
    int julgm4_b;
    int distm4_b;
    int suspm4_b;

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

float calcularMeta1(Lista *L);
float calcularMeta2A(Lista *L);
float calcularMeta2Ant(Lista *L);
float calcularMeta4A(Lista *L);
float calcularMeta4B(Lista *L);

#endif
