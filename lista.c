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
void gerarResumo(Lista *L)
{
    DIR *dir = opendir("BasedeDados/");
    char path[300];
    char linha[4096];
    char copia[4096];
    char *tokens[33];
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".csv") != NULL)
        {
            snprintf(path, sizeof(path), "BasedeDados/%s", entry->d_name);
            FILE *o = fopen(path, "r");
            fgets(linha, sizeof(linha), o);

            while (fgets(linha, sizeof(linha), o) != NULL)
            {
                strcpy(copia, linha);

                int j = 0;
                char *token = strtok(copia, ",");
                for (; token != NULL; token = strtok(NULL, ","))
                {
                    tokens[j++] = token;
                }

                char sigla[10];
                strcpy(sigla, tokens[0]);
                if (sigla[0] == '"')
                    memmove(sigla, sigla + 1, strlen(sigla));
                int len = strlen(sigla);
                while (len > 0 && (sigla[len - 1] == '"' || sigla[len - 1] == '\r' || sigla[len - 1] == '\n'))
                {
                    sigla[len - 1] = '\0';
                    len--;
                }

                No *atual = L->inicio;
                No *encontrado = NULL;
                while (atual != NULL)
                {
                    if (strcmp(atual->dados.sigla_tribunal, sigla) == 0)
                    {
                        encontrado = atual;
                        break;
                    }
                    atual = atual->prox;
                }

                if (encontrado == NULL)
                {
                    Tribunal t;
                    strcpy(t.sigla_tribunal, sigla);
                    t.casos_novos_2026 = 0;
                    t.julgados_2026 = 0;
                    t.dessobrestados_2026 = 0;
                    t.suspensos_2026 = 0;
                    t.distm2_a = 0;
                    t.julgm2_a = 0;
                    t.suspm2_a = 0;
                    t.distm2_ant = 0;
                    t.julgm2_ant = 0;
                    t.suspm2_ant = 0;
                    t.desom2_ant = 0;
                    t.distm4_a = 0;
                    t.julgm4_a = 0;
                    t.suspm4_a = 0;
                    t.distm4_b = 0;
                    t.julgm4_b = 0;
                    t.suspm4_b = 0;

                    No *novo = (No *)malloc(sizeof(No));
                    novo->dados = t;
                    novo->prox = NULL;
                    if (L->inicio == NULL)
                        L->inicio = novo;
                    else
                    {
                        No *aux = L->inicio;
                        while (aux->prox != NULL)
                            aux = aux->prox;
                        aux->prox = novo;
                    }
                    encontrado = novo;
                }

                // soma os valores
                encontrado->dados.casos_novos_2026 += atoi(tokens[10]);
                encontrado->dados.julgados_2026 += atoi(tokens[11]);
                encontrado->dados.suspensos_2026 += atoi(tokens[13]);
                encontrado->dados.dessobrestados_2026 += atoi(tokens[14]);
                encontrado->dados.distm2_a += atoi(tokens[16]);
                encontrado->dados.julgm2_a += atoi(tokens[17]);
                encontrado->dados.suspm2_a += atoi(tokens[18]);
                encontrado->dados.distm2_ant += atoi(tokens[20]);
                encontrado->dados.julgm2_ant += atoi(tokens[21]);
                encontrado->dados.suspm2_ant += atoi(tokens[22]);
                encontrado->dados.desom2_ant += atoi(tokens[23]);
                encontrado->dados.distm4_a += atoi(tokens[25]);
                encontrado->dados.julgm4_a += atoi(tokens[26]);
                encontrado->dados.suspm4_a += atoi(tokens[27]);
                encontrado->dados.distm4_b += atoi(tokens[29]);
                encontrado->dados.julgm4_b += atoi(tokens[30]);
                encontrado->dados.suspm4_b += atoi(tokens[31]);
            }
            fclose(o);
        }
    }
    closedir(dir);

    FILE *saida = fopen("resumo.csv", "w");
    fprintf(saida, "sigla_tribunal,total_julgados_2026,meta1,meta2a,meta2ant,meta4a,meta4b\n");

    No *atual = L->inicio;
    while (atual != NULL)
    {
        Tribunal t = atual->dados;

        float meta1 = (float)t.julgados_2026 / (t.casos_novos_2026 + t.dessobrestados_2026 + t.suspensos_2026) * 100;
        float meta2a = (float)t.julgm2_a / (t.distm2_a + t.suspm2_a) * 1000;
        float meta2ant = (float)t.julgm2_ant / (t.distm2_ant + t.suspm2_ant + t.desom2_ant) * 100;
        float meta4a = (float)t.julgm4_a / (t.distm4_a + t.suspm4_a) * 100;
        float meta4b = (float)t.julgm4_b / (t.distm4_b + t.suspm4_b) * 100;

        fprintf(saida, "%s,%d,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                t.sigla_tribunal, t.julgados_2026,
                meta1, meta2a, meta2ant, meta4a, meta4b);

        atual = atual->prox;
    }

    fclose(saida);
    printf("\nResumo gerado em resumo.csv\n");
}