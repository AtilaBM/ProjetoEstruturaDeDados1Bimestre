#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include "lista.h"


int main() {
    Lista minhaLista;
    initLista(&minhaLista);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char diretorio[] = "BasedeDados\\*.csv"; 

    printf("==========================================\n");
    printf("INICIANDO LEITURA AUTOMATICA: BasedeDados\n");
    printf("==========================================\n");

    // Encontra o primeiro arquivo
    hFind = FindFirstFile(diretorio, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Nao foi possivel abrir a pasta ou nenhum arquivo .csv encontrado!\n");
        return 1;
    }

    do {
        // Ignora pastas e pega apenas arquivos
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char caminhoCompleto[500];
            sprintf(caminhoCompleto, "BasedeDados/%s", findFileData.cFileName);
            
            printf("Lendo arquivo: %s...\n", findFileData.cFileName);
            lerArquivoCSV(caminhoCompleto, &minhaLista);
        }
    } while (FindNextFile(hFind, &findFileData) != 0); // Vai para o próximo arquivo

    FindClose(hFind); // Fecha a busca

    // --- RESULTADOS FINAIS ACUMULADOS ---
    if (minhaLista.inicio == NULL) {
        printf("\n[ERRO] Nenhum dado foi carregado.\n");
    } else {
        float resultadoM1 = calcularMeta1(&minhaLista);
        float resultadoM2A = calcularMeta2A(&minhaLista);

        int contadorGeral = 0;
        No *atual = minhaLista.inicio;
        while (atual != NULL) {
            contadorGeral++;
            atual = atual->prox;
        }

        printf("\n==========================================\n");
        printf("   RESULTADO CONSOLIDADO (TODOS ARQUIVOS)  \n");
        printf("==========================================\n");
        printf("TOTAL DE REGISTROS ACUMULADOS: %d\n", contadorGeral);
        printf("META 1 (Produtividade Geral):  %.2f%%\n", resultadoM1);
        printf("META 2A (Estoque Geral):      %.2f\n", resultadoM2A);
        printf("==========================================\n");
    }

    return 0;
}