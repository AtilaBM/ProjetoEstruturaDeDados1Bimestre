#include <stdio.h> 
#include <string.h>  
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

    char linha[4096];
    fgets(linha, sizeof(linha), f); 

    while (fgets(linha, sizeof(linha), f)) {
       
        if (strlen(linha) < 10 || strstr(linha, "sigla") != NULL) {
            continue;
        }

        Tribunal T;
        
        int lidos = sscanf(linha, " %[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%f,%d,%d,%d,%f,%d,%d,%d,%d,%f,%d,%d,%d,%f,%d,%d,%d,%f",
            T.sigla_tribunal, T.procedimento, T.ramo_justica, T.sigla_grau, T.uf_oj, T.municipio_oj,
            &T.id_ultimo_oj, T.nome, T.mesano_cnm1, T.mesano_sent,
            &T.casos_novos_2026, &T.julgados_2026, &T.prim_sent2026, &T.suspensos_2026, &T.dessobrestados_2026,
            &T.cumprimento_meta1,
            &T.distm2_a, &T.julgm2_a, &T.suspm2_a, &T.cumprimento_meta2a,
            &T.distm2_ant, &T.julgm2_ant, &T.suspm2_ant, &T.desom2_ant, &T.cumprimento_meta2ant,
            &T.distm4_a, &T.julgm4_a, &T.suspm4_a, &T.cumprimento_meta4a,
            &T.distm4_b, &T.julgm4_b, &T.suspm4_b, &T.cumprimento_meta4b);

        
        if (lidos >= 1) {
            inserirNoFim(L, T);
        }
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