#include <stdio.h>   
#include <stdlib.h>
#include "lista.h"

void initLista(Lista *L){
    L->inicio = NULL;
}

void inserirNoFim(Lista *L, Tribunal T){
    No* novo = (No *)malloc(sizeof(No));
    novo->dados = T;    
    novo->prox = NULL;
    
   
    if(L->inicio == NULL){
        L->inicio = novo;
    } else {
       
        No* atual = L->inicio; 
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = novo; 
    }
}

void lerArquivoCSV(char *nomearq, Lista *L) {
    FILE *f = fopen(nomearq, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char cabecalho[500];
    fgets(cabecalho, 500, f);

    Tribunal T;
    while (fscanf(f, " \"%[^\"]\",", T.sigla_tribunal) != EOF) {
    
   
    fscanf(f, " \"%[^\"]\",", T.procedimento);
    fscanf(f, " \"%[^\"]\",", T.ramo_justica);
    fscanf(f, " \"%[^\"]\",", T.sigla_grau);
    fscanf(f, " \"%[^\"]\",", T.uf_oj);
    fscanf(f, " \"%[^\"]\",", T.municipio_oj);

    
    fscanf(f, " %d,", &T.id_ultimo_oj);

    // TEXTOS NOVAMENTE
    fscanf(f, " \"%[^\"]\",", T.nome);
    fscanf(f, " \"%[^\"]\",", T.mesano_cnm1);
    fscanf(f, " \"%[^\"]\",", T.mesano_sent);

    fscanf(f, " %d,", &T.casos_novos_2026);
    fscanf(f, " %d,", &T.julgados_2026);
    fscanf(f, " %d,", &T.prim_sent2026);
    fscanf(f, " %d,", &T.suspensos_2026);
    fscanf(f, " %d,", &T.dessobrestados_2026);
    
    
    fscanf(f, " %f,", &T.cumprimento_meta1); 

    // BLOCO META 2A
    fscanf(f, " %d,", &T.distm2_a);
    fscanf(f, " %d,", &T.julgm2_a);
    fscanf(f, " %d,", &T.suspm2_a);
    fscanf(f, " %f,", &T.cumprimento_meta2a);

    // BLOCO META 2 ANT
    fscanf(f, " %d,", &T.distm2_ant);
    fscanf(f, " %d,", &T.julgm2_ant);
    fscanf(f, " %d,", &T.suspm2_ant);
    fscanf(f, " %d,", &T.desom2_ant);
    fscanf(f, " %f,", &T.cumprimento_meta2ant);

   
    fscanf(f, " %d,", &T.distm4_a);
    fscanf(f, " %d,", &T.julgm4_a);
    fscanf(f, " %d,", &T.suspm4_a);
    fscanf(f, " %f,", &T.cumprimento_meta4a);
    
    fscanf(f, " %d,", &T.distm4_b);
    fscanf(f, " %d,", &T.julgm4_b);
    fscanf(f, " %d,", &T.suspm4_b);
    fscanf(f, " %f", &T.cumprimento_meta4b); 

   
    inserirNoFim(L, T);
}