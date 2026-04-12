#ifndef LISTA_H
#define LISTA_H

typedef struct {

    char sigla_tribunal[20];
    char procedimento[100];
    char ramo_justica[50];
    char sigla_grau[10];
    char uf_oj[5];
    char municipio_oj[100];

    // --- IDENTIFICAÇÃO 
    int id_ultimo_oj;
    char nome[150];
    char mesano_cnm1[20];
    char mesano_sent[20];

    // --- DADOS GERAIS 2026 
    int casos_novos_2026;
    int julgados_2026;
    int prim_sent2026;
    int suspensos_2026;
    int dessobrestados_2026;

    // --- META 1 e 2A 
    float cumprimento_meta1;
    int distm2_a;
    int julgm2_a;
    int suspm2_a;
    float cumprimento_meta2a;

    // --- META 2 ANT 
    int distm2_ant;
    int julgm2_ant;
    int suspm2_ant;
    int desom2_ant;
    float cumprimento_meta2ant;

    // --- META 4A 
    int distm4_a;
    int julgm4_a;
    int suspm4_a;
    float cumprimento_meta4a;

    // --- META 4B 
    int distm4_b;
    int julgm4_b;
    int suspm4_b;
    float cumprimento_meta4b;

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
