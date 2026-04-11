#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct Dados
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
    int julgados_2026_dup; // duplicado
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

// Definição do nó da lista
typedef struct No {
    Dados dados;
    struct No *prox;
} No;

// Definição da lista
typedef struct {
    No *inicio;
    int tamanho;
} Lista;

// Funções da lista
Lista* criar_lista();
void inserir_no_fim(Lista *lista, Dados dados);
void liberar_lista(Lista *lista);
void carregar_dados_csv(Lista *lista, const char *nome_arquivo);
void exportar_por_municipio(Lista *lista, const char *municipio_alvo);

#endif