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
    printf("\nTem %d linhas nesse arquivo\n",count);

    fclose(i);
    closedir(dir);
}

void pesquisaPorMunicipio()
{
    char municipio[200];
    char nomeArquivo[250];
    char *token;

    printf("\nDigite o nome do municipio em maisculo e com acentos se necessario: ");
    scanf("%s", municipio);

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
