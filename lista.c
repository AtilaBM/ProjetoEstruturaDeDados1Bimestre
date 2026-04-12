#include <stdio.h>   
#include <stdlib.h>
#include "lista.h"

void initLista(Lista *L){
    L->inicio = NULL;
}

void inserirNoFim(Lista *L, Tribunal T){
    No* novo = (No *)malloc(sizeof(No));
    if(novo == NULL) return; 
    novo->dados = T;    
    novo->prox = NULL;
    
    if(L->inicio == NULL){
        L->inicio = novo;
    } 
       else {
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
   
    while (fscanf(f, " %[^,],", T.sigla_tribunal) == 1) {
        
        fscanf(f, " %[^,],", T.procedimento);
        fscanf(f, " %[^,],", T.ramo_justica);
        fscanf(f, " %[^,],", T.sigla_grau);
        fscanf(f, " %[^,],", T.uf_oj);
        fscanf(f, " %[^,],", T.municipio_oj);
        fscanf(f, " %d,", &T.id_ultimo_oj);
        fscanf(f, " %[^,],", T.nome);
        fscanf(f, " %[^,],", T.mesano_cnm1);
        fscanf(f, " %[^,],", T.mesano_sent);
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

        // BLOCO META 4A
        fscanf(f, " %d,", &T.distm4_a);
        fscanf(f, " %d,", &T.julgm4_a);
        fscanf(f, " %d,", &T.suspm4_a);
        fscanf(f, " %f,", &T.cumprimento_meta4a);
        
        // BLOCO META 4B
        fscanf(f, " %d,", &T.distm4_b);
        fscanf(f, " %d,", &T.julgm4_b);
        fscanf(f, " %d,", &T.suspm4_b);
        fscanf(f, " %f\n", &T.cumprimento_meta4b); 

        inserirNoFim(L, T);
    }
    
    fclose(f); 
}
float calcularMeta1(Lista *L) {

    int Julgados = 0;
    int Casosn = 0;
    int Suspensos = 0;
    int Dessobrestados = 0;

    No *aux = L->inicio;
    while (aux != NULL) {
        
        Julgados = aux->dados.julgados_2026 +Julgados;
        Casosn = aux->dados.casos_novos_2026 + Casosn ;
        Suspensos = aux->dados.suspensos_2026 + Suspensos;
        Dessobrestados =aux->dados.dessobrestados_2026 + Dessobrestados ;

        aux = aux->prox;
    }
    
    int result = Casosn + Dessobrestados - Suspensos;
    if (result <= 0) {
        return 0.0;
    }

    float resultadoFinal = ((float)Julgados / result) * 100;
    return resultadoFinal;
}
float calcularMeta2A(Lista *L){

    int Julgm2= 0;
    int Distm2= 0;
    int Suspm2 = 0;

    No* aux = L ->inicio;
    while(aux != NULL){
        Julgm2= aux ->dados.julgm2_a + Julgm2;
        Distm2 = aux ->dados.distm2_a + Distm2;
        Suspm2 = aux ->dados.suspm2_a + Suspm2;

        aux = aux->prox;
    }

    int result = Distm2 - Suspm2;
    if (result <= 0) {
        return 0.0;
    }

    float resultadoFinal = ((float)Julgm2 / result) * (1000.0/7.0);
    return resultadoFinal;

}