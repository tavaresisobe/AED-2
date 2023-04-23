/* Programa: AP4 - QuickSort
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 20/04/2023 - 22:31h
   https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/quick.html
*/
 
// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
 
// ###################### Funcoes e Procedimentos do programa ##############
 
void imprime (int vet[], int vet2[], int n) ;
void troca(int *a, int *b) ;
int divide(int vet[], int p, int r) ;
void quick_sort1(int vet[], int p, int r, int count, int *min, int *max) ;
void quick_sort2(int vet[], int p, int r, int count, int *min, int *max) ;
void imprime (int vet[], int vet2[], int n) ;
int mediana(int vet[], int p, int r);
 
void troca(int *a, int *b)
{
    int t = *a ;
    *a = *b ;
    *b = t ;
}
 
void start ()
 
{
    int n, i ;
    int *vet, *vet2 ;
    
    scanf ("%d", &n) ;
    int min = n, max = 0 ;
    vet = malloc (n * sizeof(int)) ;
    vet2 = malloc (n * sizeof(vet)) ;
    for (i = 0 ; i < n ; i++)
    {
        scanf ("%d", &vet[i]) ;
        vet2[i] = vet[i] ;
    }
    quick_sort1(vet, 0, n - 1, 0, &min, &max) ;
    printf ("%d\n", max - min) ;
    
    min = n, max = 0 ;
    quick_sort2(vet2, 0, n - 1, 0, &min, &max) ;
    printf ("%d\n", max - min) ;
//    imprime(vet, vet2, n) ; print p/ testar ordenamento
}
 
int divide(int *vet, int p, int r)
{
    int indice_pivo = r ;
    int valor_pivo = vet[indice_pivo] ;
    troca(&vet[indice_pivo], &vet[r]) ;
    int indice = p ;
    for (int i = p; i < r; i++) 
    {
        if (vet[i] < valor_pivo )
        {
            troca(&vet[i], &vet[indice]) ;
            indice++ ;
        }
    }
    troca(&vet[indice], &vet[r]) ;
    return indice ;
}
 
int divide2(int *vet, int p, int r)
{
    int pivo ;
    int mid = ((r+p)/2) ;
    int i = p-1 ;
 
    if(vet[p] <= vet[mid] && vet[p] >= vet[r]) troca(&vet[p],&vet[r]) ;
    if(vet[p] <= vet[r] && vet[p] >= vet[mid]) troca(&vet[p],&vet[r]) ;
    if(vet[mid] <= vet[p] && vet[mid] >= vet[r]) troca(&vet[mid],&vet[r]) ;
    if(vet[mid] <= vet[r] && vet[mid] >= vet[p]) troca(&vet[mid],&vet[r]) ;
    if(vet[r] <= vet[p] && vet[r] >= vet[mid]) pivo = vet[r] ;
    if(vet[r] <= vet[mid] && vet[r] >= vet[p]) pivo = vet[r] ;
     
    pivo = vet[r] ;
  
    for(int j = p; j <= r-1; j++)
    {
      if(vet[j] <= pivo)
      {
        i++;
        troca(&vet[j], &vet[i]) ;
      }
    }
    troca(&vet[i+1], &vet[r]) ;
    return i+1 ;
}
 
void quick_sort1(int *vet, int p, int r, int count, int *min, int *max)
{
    if (p >= r) 
    {
        if(count < *min) 
            *min = count ;
        if(count > *max) 
            *max = count ;
     //   printf("TESTE %d %d\n", *max, *min);
        return;
    }
    int pi = divide(vet, p, r) ;
    quick_sort1(vet, p, pi - 1, count+1, min, max) ;
    quick_sort1(vet, pi + 1, r, count+1, min, max) ;
}
 
void quick_sort2(int *vet, int p, int r, int count, int *min2, int *max2)
{
    if (p >= r) 
    {
        if(count < *min2) 
            *min2 = count ;
        if(count > *max2) 
            *max2 = count ;
        return;
    }
    int pi = divide2(vet, p, r) ;
    quick_sort2(vet, p, pi - 1, count+1, min2, max2) ;
    quick_sort2(vet, pi + 1, r, count+1, min2, max2) ;
}
 
void imprime (int *vet, int vet2[], int n)
{
    int i ;
    printf ("\nvetor 1:\n") ;
    for (i = 0 ; i < n ; i++)
    {
        printf ("%d ", vet[i]) ;
    }
    printf ("\nvetor 2:\n") ;
    for (i = 0 ; i < n ; i++)
    {
        printf ("%d ", vet2[i]) ;
    }
}
 
// ############################ Principal ###################################
 
int main()
{
    start() ;
    return 0 ; 
}
