#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#include "lista.h"

int main()
{
   int op;

   system("cls");
   system("clear");

   printf("1 - Concatenar arquivos\n");
   printf("2 - Resumo\n");
   printf("3 - Pesquisar por municipio\n");
   printf("0 - Sair\n");
   printf("\nEscolha: ");
   scanf("%d", &op);

   switch (op)
   {
   case 1:
      concatenarArquivos();
      break;
   case 2:
   {
        system("cls || clear");

        printf("\n===== RESUMO =====\n\n");

        char *tribunais[] = {
            "TRE-TO","TRE-SP","TRE-SE","TRE-SC","TRE-RS","TRE-RR",
            "TRE-RO","TRE-RN","TRE-RJ","TRE-PR","TRE-PI","TRE-PE",
            "TRE-PB","TRE-PA","TRE-MT","TRE-MS","TRE-MG","TRE-MA",
            "TRE-GO","TRE-ES","TRE-DF","TRE-CE","TRE-BA","TRE-AP",
            "TRE-AM","TRE-AL","TRE-AC"
        };

        char nomeArquivo[100];

        for (int i = 0; i < 27; i++) {

            Lista l;
            l.inicio = NULL;

            sprintf(nomeArquivo, "BasedeDados/teste_%s.csv", tribunais[i]);

            carregarDados(&l, nomeArquivo);

            printf(">>> %s\n", tribunais[i]);

            float m1 = calcularMeta1(&l);
            float m2 = calcularMeta2A(&l);

            printf("Meta 1: %.2f%%\n", m1);
            printf("Meta 2A: %.2f%%\n\n", m2);
        }

        printf("\nPressione Enter para voltar...");
        getchar(); getchar();

      break;
   }


   case 3:
      pesquisaPorMunicipio();
      break;
   default:
      printf("Opcao invalida.\n");
   }

    return 0;
}
  
