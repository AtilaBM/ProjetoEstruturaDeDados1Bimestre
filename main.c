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
      printf("Nao disponivel");
      break;
   case 3:
      pesquisaPorMunicipio();
      break;
   default:
      printf("Opcao invalida.\n");
   }
   return 0;
}
