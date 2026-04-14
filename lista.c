#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#include "lista.h"


void concatenarArquivos()
{
    DIR *dir = opendir("BasedeDados/");
    FILE *i = fopen("arquivosConcatenados.csv", "w");

    char path[300];
    char linha[4096];

    int count = 0,
        cabecalho = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".csv") != NULL)
        {
            snprintf(path, sizeof(path), "BasedeDados/%s", entry->d_name);
            FILE *o = fopen(path, "r");
            fgets(linha, sizeof(linha), o);

            if (!cabecalho)
            {
                fprintf(i, "%s", linha); // escreve só na primeira vez
                cabecalho = 1;
            }

            if (i != NULL)
            {
                while (fgets(linha, sizeof(linha), o) != NULL)
                {

                    fprintf(i, "%s", linha);
                    count++;
                }
                fclose(o);
            }
        }
    }
    printf("\nTem %d linhas nesse arquivo\n", count);

    fclose(i);
    closedir(dir);
}

void pesquisaPorMunicipio()
{
    char municipio[200];
    char nomeArquivo[250];
    char *token;

    getchar();
    printf("\nDigite o nome do municipio em maisculo e com acentos se necessario: ");
    fgets(municipio, sizeof(municipio), stdin);
    municipio[strcspn(municipio, "\n")] = '\0';

    // for (int j = 0; municipio[j]; j++)
    // {
    //     municipio[j] = toupper(municipio[j]);
    // }

    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.csv", municipio);

    DIR *dir = opendir("BasedeDados/");
    FILE *i = fopen(nomeArquivo, "w");

    char path[300];
    char linha[4096];
    char copia[4096];

    int count = 0,
        cabecalho = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".csv") != NULL)
        {
            snprintf(path, sizeof(path), "BasedeDados/%s", entry->d_name);
            FILE *o = fopen(path, "r");
            fgets(linha, sizeof(linha), o);

            if (!cabecalho)
            {
                fprintf(i, "%s", linha); // escreve só na primeira vez
                cabecalho = 1;
            }

            if (i != NULL)
            {
                while (fgets(linha, sizeof(linha), o) != NULL)
                {
                    strcpy(copia, linha);

                    token = strtok(copia, ",");
                    for (int i = 0; i < 5; i++)
                    {
                        token = strtok(NULL, ",");
                    }

                    if (token[0] == '"')
                        token++;

                    int len = strlen(token);
                    while (len > 0 && (token[len - 1] == '"' || token[len - 1] == '\r' || token[len - 1] == '\n'))
                    {
                        token[len - 1] = '\0';
                        len--;
                    }

                    if (strcmp(token, municipio) == 0)
                    {
                        fprintf(i, "%s", linha);
                        count++;
                    }
                }
                fclose(o);
            }
        }
    }
    printf("\nArquivo gerado!");
    printf("\nTem %d linhas no arquivo %s\n", count, nomeArquivo);
    fclose(i);
    closedir(dir);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "lista.h"

void limparString(char *str) {
    if (str[0] == '"') {
        memmove(str, str + 1, strlen(str));
    }

    int len = strlen(str);
    while (len > 0 && (str[len - 1] == '"' || str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

void carregarDados(Lista *L, char *nomeArquivo) {

    FILE *arq = fopen(nomeArquivo, "r");
    if (!arq) {
        printf("Erro ao abrir %s\n", nomeArquivo);
        return;
    }

    char linha[4096];
    fgets(linha, sizeof(linha), arq); // pula cabeçalho

    while (fgets(linha, sizeof(linha), arq)) {

        No *novo = malloc(sizeof(No));
        if (!novo) break;

        char *token;
        int coluna = 0;

        token = strtok(linha, ",");

        while (token != NULL) {

            limparString(token);

            switch (coluna) {

                case 0: strcpy(novo->dados.sigla_tribunal, token); break;
                case 5: strcpy(novo->dados.municipio_oj, token); break;

                case 10: novo->dados.casos_novos_2026 = atoi(token); break;
                case 11: novo->dados.julgados_2026 = atoi(token); break;
                case 13: novo->dados.suspensos_2026 = atoi(token); break;
                case 14: novo->dados.dessobrestados_2026 = atoi(token); break;

                case 16: novo->dados.distm2_a = atoi(token); break;
                case 17: novo->dados.julgm2_a = atoi(token); break;
                case 18: novo->dados.suspm2_a = atoi(token); break;
            }

            token = strtok(NULL, ",");
            coluna++;
        }

        novo->prox = L->inicio;
        L->inicio = novo;
    }

    fclose(arq);
}

float calcularMeta1(Lista *L) {

    int Julgados = 0, Casosn = 0, Suspensos = 0, Dessobrestados = 0;

    No *aux = L->inicio;

    while (aux != NULL) {

        Julgados += aux->dados.julgados_2026;
        Casosn += aux->dados.casos_novos_2026;
        Suspensos += aux->dados.suspensos_2026;
        Dessobrestados += aux->dados.dessobrestados_2026;

        aux = aux->prox;
    }

    int result = Casosn + Dessobrestados - Suspensos;

    if (result <= 0) return 0.0;

    return ((float)Julgados / result) * 100;
}

float calcularMeta2A(Lista *L){

    int Julgm2 = 0, Distm2 = 0, Suspm2 = 0;

    No* aux = L->inicio;

    while(aux != NULL){

        Julgm2 += aux->dados.julgm2_a;
        Distm2 += aux->dados.distm2_a;
        Suspm2 += aux->dados.suspm2_a;

        aux = aux->prox;
    }

    int result = Distm2 - Suspm2;

    if (result <= 0) return 0.0;

    return ((float)Julgm2 / result) * (1000.0/7.0);
}