/* Programa: AP1 - Recursão
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 22/03/2023 - 22:45h
*/
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ###################### Funcoes e Procedimentos do programa ##############

void start() ;
void busca() ;

void start()
{
  int n, num ;
  scanf ("%d", &n) ;
  int *vet ;
  vet = malloc (n * sizeof(int)) ;
  for (int i = 0 ; i < n ; i++)
  {
      scanf ("%d", &vet[i]) ;
  }
  scanf ("%d", &num) ;
  busca (vet,num,n) ;
}

void busca(int *vet, int num, int n)
{
  for (int i = 0 ; i < n ; i++)
  {
    printf ("%d ", vet[i]) ;  
  }
}

// ############################ Principal ###################################

int main ()
{
  start() ;
  return 0 ;
  
}
