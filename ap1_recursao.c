/*AUTOR: GUSTAVO HENRIQUE TAVARES ISOBE
RA: 158552 DATA: 22/03/2023
*/

#include <stdio.h>
#include <stdlib.h>


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

}

int main ()
{
  start() ;
  return 0 ;
  
}
