#include "lista.h"

Lista* criar_lista() {
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

void inserir_no_fim(Lista *lista, Dados dados) {
    if (lista == NULL) return;
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return;
    novo->dados = dados;
    novo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    lista->tamanho++;
}

void liberar_lista(Lista *lista) {
    if (lista == NULL) return;
    No *atual = lista->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

void carregar_dados_csv(Lista *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }

    char linha[1024];
    int primeira_linha = 1;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (primeira_linha) {
            primeira_linha = 0;
            continue; // pular cabeçalho
        }

        Dados dados;
        // Parse da linha CSV
        char *token = strtok(linha, ";");
        if (token) strcpy(dados.sigla_tribunal, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.procedimento, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.ramo_justica, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.sigla_grau, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.uf_oj, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.municipio_oj, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.id_ultimo_oj, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.nome, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.mesano_cnm1, token);
        token = strtok(NULL, ";");
        if (token) strcpy(dados.mesano_sent, token);
        token = strtok(NULL, ";");
        if (token) dados.casos_novos_2026 = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.julgados_2026 = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.prim_sent2026 = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.suspensos_2026 = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.dessobrestados_2026 = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.cumprimento_meta1 = atof(token);
        token = strtok(NULL, ";");
        if (token) dados.distm2_a = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.julgados_2026_dup = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.suspm2_a = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.cumprimento_meta2a = atof(token);
        token = strtok(NULL, ";");
        if (token) dados.distm2_ant = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.julgm2_ant = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.suspm2_ant = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.desom2_ant = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.cumprimento_meta2ant = atof(token);
        token = strtok(NULL, ";");
        if (token) dados.distm4_a = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.julgm4_a = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.suspm4_a = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.cumprimento_meta4a = atof(token);
        token = strtok(NULL, ";");
        if (token) dados.distm4_b = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.julgm4_b = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.suspm4_b = atoi(token);
        token = strtok(NULL, ";");
        if (token) dados.cumprimento_meta4b = atof(token);

        inserir_no_fim(lista, dados);
    }

    fclose(arquivo);
}

void exportar_por_municipio(Lista *lista, const char *municipio_alvo) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("A lista de dados esta vazia. Carregue os dados primeiro.\n");
        return;
    }

    // exibir nome do arquivo
    char nome_arquivo[150];
    strcpy(nome_arquivo, municipio_alvo);
    strcat(nome_arquivo, ".csv");

    // escrita do arqiuivo
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s.\n", nome_arquivo);
        return;
    }

    // cabeçalho do arquivo
    fprintf(arquivo, "sigla_tribunal;procedimento;ramo_justica;sigla_grau;uf_oj;municipio_oj;id_ultimo_oj;nome;mesano_cnm1;mesano_sent;casos_novos_2026;julgados_2026;prim_sent2026;suspensos_2026;dessobrestados_2026;cumprimento_meta1;distm2_a;julgm2_a;suspm2_a;cumprimento_meta2a;distm2_ant;julgm2_ant;suspm2_ant;desom2_ant;cumprimento_meta2ant;distm4_a;julgm4_a;suspm4_a;cumprimento_meta4a;distm4_b;julgm4_b;suspm4_b;cumprimento_meta4b\n");


    No *atual = lista->inicio;
    int contador_registros = 0;

    while (atual != NULL) {
        // comparar o campo municipio
        if (strcmp(atual->dados.municipio_oj, municipio_alvo) == 0) {
            
            
            fprintf(arquivo, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%f;%d;%d;%d;%f;%d;%d;%d;%d;%f;%d;%d;%d;%f;%d;%d;%d;%f\n",
                atual->dados.sigla_tribunal,
                atual->dados.procedimento,
                atual->dados.ramo_justica,
                atual->dados.sigla_grau,
                atual->dados.uf_oj,
                atual->dados.municipio_oj,
                atual->dados.id_ultimo_oj,
                atual->dados.nome,
                atual->dados.mesano_cnm1,
                atual->dados.mesano_sent,
                atual->dados.casos_novos_2026,
                atual->dados.julgados_2026,
                atual->dados.prim_sent2026,
                atual->dados.suspensos_2026,
                atual->dados.dessobrestados_2026,
                atual->dados.cumprimento_meta1,
                atual->dados.distm2_a,
                atual->dados.julgados_2026_dup,
                atual->dados.suspm2_a,
                atual->dados.cumprimento_meta2a,
                atual->dados.distm2_ant,
                atual->dados.julgm2_ant,
                atual->dados.suspm2_ant,
                atual->dados.desom2_ant,
                atual->dados.cumprimento_meta2ant,
                atual->dados.distm4_a,
                atual->dados.julgm4_a,
                atual->dados.suspm4_a,
                atual->dados.cumprimento_meta4a,
                atual->dados.distm4_b,
                atual->dados.julgm4_b,
                atual->dados.suspm4_b,
                atual->dados.cumprimento_meta4b
            );
            
            contador_registros++;
        }
        

        atual = atual->prox;
    }

    // dá o retorno da lista
    fclose(arquivo);
    
    if (contador_registros > 0) {
        printf("Sucesso! Arquivo '%s' gerado com %d registro(s).\n", nome_arquivo, contador_registros);
    } else {
        // caso não achar nada
        printf("Nenhum registro encontrado para o municipio '%s'.\n", municipio_alvo);
        remove(nome_arquivo); 
    }
}
