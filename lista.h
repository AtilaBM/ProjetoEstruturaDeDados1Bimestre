#ifndef LISTA_H
#define LISTA_H

typedef struct {
    char sigla_tribunal[50];
    char procedimento[100];
    char ramo_justica[50];
    char sigla_grau[10];
    char uf_oj[5];
    char municipio_oj[100];
    char id_ultimo_oj[20];
    char nome[200];
    char mesano_cnm1[20];
    char mesano_sent[20];
    int casos_novos_2026;
    int julgados_2026;
    int prim_sent2026;
    int suspensos_2026;
    int dessobrestados_2026;
    float cumprimento_meta1;
    int distm2_a;
    int julgm2_a;
    int suspm2_a;
    float cumprimento_meta2a;
    int distm2_ant;
    int julgm2_ant;
    int suspm2_ant;
    int desom2_ant;
    float cumprimento_meta2ant;
    int distm4_a;
    int julgm4_a;
    int suspm4_a;
    float cumprimento_meta4a;
    int distm4_b;
    int julgm4_b;
    int suspm4_b;
    float cumprimento_meta4b;
} Dados;

typedef struct{
    Dados *data;
    int tamanho;
    int capacidade;
}Lista;

Lista *criarLista();
void inserirNoFim(Lista *lista, Dados dados);




//  FUNÇÕES PRINCIPAIS
void concatenarArquivos();

#endif

