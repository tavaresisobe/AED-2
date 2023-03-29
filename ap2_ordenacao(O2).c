#include <stdio.h>
#include <stdlib.h>

void bubblesort(int *, int) ;
int compara (int *, int*, int) ;

void start()
{
  int n, i;
  scanf ("%d", &n) ;
  int *microorganismos, *potencia ;
  microorganismos = malloc (n * sizeof(int)) ;
  for (i = 0 ; i < n ; i++)
  {
      scanf ("%d", &microorganismos[i]) ;
  }
  potencia = malloc (n * sizeof(int)) ;
  for (i = 0 ; i < n ; i++)
  {
      scanf ("%d", &potencia[i]) ;
  }
  bubblesort(microorganismos, n) ;
  bubblesort(potencia, n) ;
  int x = compara (microorganismos, potencia, n) ;
  if (x == 0)
  {
    printf ("sim\n");
  }else
    printf ("nao\n") ;
}

void bubblesort(int *vet, int n)
{
  int aux ;
  for (int i = 0 ; i < n-1 ; i++)
  {
    for (int j = 0 ; j < n-1-i ; j++)
    {
      if (vet[j] > vet[j+1])
      {
        aux = vet[j] ;
        vet[j] = vet[j+1] ;
        vet[j+1] = aux ;
      }
    }
  }
}

int compara(int *micro , int *pot, int n)
{
  int i, count = 0;
  for (i = 0 ; i < n ; i++)
  {
    if (pot[i] > micro[i])
    {
      count += 0 ;
    }else
      count += 1 ;
  }
  return count ;
}

int main(void) 
{
  start() ;
  return 0;
}
