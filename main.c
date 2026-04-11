#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "lista.h"

int main() {
    Lista *lista = criar_lista();
    if (lista == NULL) {
        printf("Erro ao criar lista.\n");
        return 1;
    }

    // Carregar todos os arquivos CSV da pasta BasedeDados
    DIR *dir = opendir("BasedeDados");
    if (dir == NULL) {
        printf("Erro ao abrir a pasta BasedeDados.\n");
        liberar_lista(lista);
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".csv") != NULL) {
            char caminho[256];
            sprintf(caminho, "BasedeDados/%s", entry->d_name);
            carregar_dados_csv(lista, caminho);
        }
    }
    closedir(dir);

    printf("Dados carregados. Total de registros: %d\n", lista->tamanho);

    // Pedir município ao usuário
    char municipio[100];
    printf("Digite o nome do municipio: ");
    fgets(municipio, sizeof(municipio), stdin);
    municipio[strcspn(municipio, "\n")] = 0; // remover newline

    exportar_por_municipio(lista, municipio);

    liberar_lista(lista);
    return 0;
}