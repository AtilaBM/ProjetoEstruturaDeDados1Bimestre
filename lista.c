#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "lista.h"

Lista *criarLista()
{
    Lista *l = (Lista *)malloc(sizeof(Lista));
    if (l == NULL)
        return NULL;
    l->data = malloc(sizeof(Dados) * 100); // capacidade inicial
    l->tamanho = 0;
    l->capacidade = 100;
    return l;
}

void inserir_no_fim(Lista *lista, Dados dados)
{
    if (lista->tamanho == lista->capacidade)
    {
        lista->capacidade *= 2;
        lista->data = realloc(lista->data, sizeof(Dados) * lista->capacidade);
    }
    lista->data[lista->tamanho] = dados;
    lista->tamanho++;
}

void concatenarArquivos()
{
    DIR *dir = opendir("BasedeDados/");
    FILE *i = fopen("arquivosConcatenados.csv", "w");

    char path[300];
    char linha[18000];

    int count = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".csv") != NULL)
        {
            snprintf(path, sizeof(path), "BasedeDados/%s", entry->d_name);
            FILE *o = fopen(path, "r");
            fgets(linha, sizeof(linha), o);

            if (i != NULL)
            {
                while (fgets(linha, sizeof(linha), o) != NULL)
                {

                    fprintf(i, "%s", linha);
                }
                fclose(o);
            }
        }
    }

    fclose(i);
    closedir(dir);
}
