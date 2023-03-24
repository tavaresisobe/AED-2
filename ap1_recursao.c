/* Programa: AP1 - Recursão
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 22/03/2023 - 22:45h
*/
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ###################### Funcoes e Procedimentos do programa ##############

void start() ;
int busca() ;

void start()
{
  int n, num ;
  scanf ("%d", &n) ;
  int *vet, count = 0 ;
  vet = malloc (n * sizeof(int)) ;
  for (int i = 0 ; i < n ; i++)
  {
      scanf ("%d", &vet[i]) ;
  }
  scanf ("%d", &num) ;
  busca (vet,num,n, &count) ;
  printf ("Numero de chamadas recursivas: %d\n", count) ;
}

int busca(int *vet, int num, int n, int *count)
{
  int i = (n+(n/2))/2 ;
  return 0 ;
}

// ############################ Principal ###################################

int main ()
{
  start() ;
  return 0 ;
  
}
