#include <stdio.h>
#include <stdlib.h>

//https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/quick.html

void troca(int *a, int *b)
{
    int t = *a ;
    *a = *b ;
    *b = t ;
}

void start ()
{
    int tam_vet, i ;
    int *vet, *vet2 ;
    
    scanf ("%d", &tam_vet) ;
    vet = malloc (tam_vet * sizeof(int)) ;
    for (i = 0 ; i < tam_vet ; i++)
    {
        scanf ("%d", &vet[i]) ;
    }
    vet2 = malloc (tam_vet * sizeof(vet)) ;
    for (i = 0 ; i < tam_vet ; i++) //copiando vetor para implementação do quicksort utiliziando a mediana
    {
        vet2[i] = vet[i] ;
    }
    int test = 0 ;
    quick_sort(vet, 0, tam_vet - 1, test);
   // test += 1 ;
   // quick_sort(vet2, 0, tam_vet - 1, test);
	
	for(i = 0; i < tam_vet; i++) //print para auxiliar
	    printf("%d ", vet[i]);
	printf ("\n\n") ;
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet2[i]);
}

int divide(int vet[], int p, int r)
{
    int pivo = vet[r];
    int i = (p - 1);
    for (int j = p ; j < r ; j++)
    {
        if (vet[j] < pivo)
        {
            troca(&vet[++i], &vet[j]);
        }
    }
    troca(&vet[i + 1], &vet[r]);
    return (i + 1);
}

int mediana(int vet[], int p, int r)
{
    int pivo ;
    int mid = (p + r) / 2 ;
    
    if (vet[mid] < vet[p]) 
        troca(&vet[mid], &vet[p]) ;
    
    if (vet[r] < vet[p])
        troca(&vet[r], &vet[p]) ;
    
    if (vet[r] < vet[mid])
        troca(&vet[r], &vet[mid]) ;
    
    troca(&vet[mid], &vet[r-1]) ;
    pivo = vet[r-1] ;
    
    return divide(vet, p, r);
}

void quick_sort(int vet[], int p, int r, int test)
{
    if (p < r) 
    {
        int pi = divide(vet, p, r);
        //ordenando :
        quick_sort(vet, p, pi - 1, test) ; //elementos a esquerda do pivo
        printf ("1: Executou com o pivo sendo ultimo elemento\n") ;
        quick_sort(vet, pi + 1, r, test) ; //elementos a direita do pivo
        printf ("2: Executou com o pivo sendo ultimo elemento\n") ;
    }
}
 
/*void quick_sort(int vet[], int p, int r, int test)
{
    if (p < r) 
    {
        int pi ;
        if (test == 0)
        {
            pi = divide(vet, p, r);
            //ordenando :
            quick_sort(vet, p, pi - 1, test) ; //elementos a esquerda do pivo
            quick_sort(vet, pi + 1, r, test) ; //elementos a direita do pivo
            printf ("Executou com o pivo sendo ultimo elemento\n") ;
        }else
        if (test > 0)
        {
            pi = mediana(vet, p, r) ;
            //ordenando :
            quick_sort(vet, p, pi - 1, test) ; //elementos a esquerda do pivo
            quick_sort(vet, pi + 1, r, test) ; //elementos a direita do pivo
           // printf ("Executou com o pivo sendo a mediana dos elementos\n") ;
        }
    }
}*/

int main()
{
    start() ;
    return 0; 
}

#include <stdio.h>
#include <stdlib.h>

//https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/quick.html

void troca(int *a, int *b)
{
    int t = *a ;
    *a = *b ;
    *b = t ;
}

void start ()
{
    int tam_vet, i ;
    int *vet, *vet2 ;
    
    scanf ("%d", &tam_vet) ;
    vet = malloc (tam_vet * sizeof(int)) ;
    for (i = 0 ; i < tam_vet ; i++)
    {
        scanf ("%d", &vet[i]) ;
    }
    vet2 = malloc (tam_vet * sizeof(vet)) ;
    for (i = 0 ; i < tam_vet ; i++) //copiando vetor para implementação do quicksort utiliziando a mediana
    {
        vet2[i] = vet[i] ;
    }
    printf ("Vet 1:\n") ;
    quick_sort1(vet, 0, 0, tam_vet - 1);
    printf("Vet 2:\n") ;
    quick_sort2(vet2, 0, 0, tam_vet - 1);
	
	for(i = 0; i < tam_vet; i++) //print para auxiliar
	    printf("%d ", vet[i]);
	printf ("\n\n") ;
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet2[i]);
}

int divide(int vet[], int p, int r)
{
    int pivo = vet[r];
    int i = (p - 1);
    for (int j = p ; j < r ; j++)
    {
        if (vet[j] < pivo)
        {
            troca(&vet[++i], &vet[j]);
        }
    }
    troca(&vet[i + 1], &vet[r]);
    return (i + 1);
}

int mediana(int vet[], int p, int r)
{
    int pivo ;
    int mid = (p + r) / 2 ;
    
    if (vet[mid] < vet[p]) 
        troca(&vet[mid], &vet[p]) ;
    
    if (vet[r] < vet[p])
        troca(&vet[r], &vet[p]) ;
    
    if (vet[r] < vet[mid])
        troca(&vet[r], &vet[mid]) ;
    
    troca(&vet[mid], &vet[r-1]) ;
    pivo = vet[r-1] ;
    
    return divide(vet, p, r);
}

void quick_sort1(int vet[], int p, int count, int r)
{
    if (p < r) 
    {
        int pi = divide(vet, p, r);
        //ordenando :
        quick_sort1(vet, p, count+1, pi - 1) ; //elementos a esquerda do pivo
        quick_sort1(vet, pi + 1, count+1, r) ; //elementos a direita do pivo
    }else 
        printf("%d\n", count) ;
}

void quick_sort2(int vet[], int p, int count, int r)
{
    if (p < r) 
    {
        int pi = mediana(vet, p, r);
        //ordenando :
        quick_sort2(vet, p, count+1, pi - 1) ; //elementos a esquerda do pivo
        quick_sort2(vet, pi + 1, count+1, r) ; //elementos a direita do pivo
    }else
        printf ("%d\n", count) ;
}

int main()
{
    start() ;
    return 0; 
}

#include <stdio.h>
#include <stdlib.h>

//https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/quick.html

void troca(int *a, int *b)
{
    int t = *a ;
    *a = *b ;
    *b = t ;
}

void start ()
{
    int tam_vet, i ;
    int *vet, *vet2 ;
    
    scanf ("%d", &tam_vet) ;
    vet = malloc (tam_vet * sizeof(int)) ;
    for (i = 0 ; i < tam_vet ; i++)
    {
        scanf ("%d", &vet[i]) ;
    }
    vet2 = malloc (tam_vet * sizeof(vet)) ;
    for (i = 0 ; i < tam_vet ; i++) //copiando vetor para implementação do quicksort utiliziando a mediana
    {
        vet2[i] = vet[i] ;
    }
    printf ("Vet 1:\n") ;
    quick_sort1(vet, 0, 0, tam_vet - 1);
    printf("Vet 2:\n") ;
    quick_sort2(vet2, 0, 0, tam_vet - 1);
	
	for(i = 0; i < tam_vet; i++) //print para auxiliar
	    printf("%d ", vet[i]);
	printf ("\n\n") ;
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet2[i]);
}

int divide(int vet[], int p, int r)
{
    int pivo = vet[r];
    int i = (p - 1);
    for (int k = 0; k <= r ; k++)
    {
        printf ("%d ", vet[k]) ;
    }
    printf ("\n") ;
    for (int j = p ; j < r ; j++)
    {
        if (vet[j] < pivo)
        {
            troca(&vet[++i], &vet[j]);
        }
    }
    troca(&vet[i + 1], &vet[r]);
    return (i + 1);
}

int mediana(int vet[], int p, int r)
{
    int pivo ;
    int mid = (p + r) / 2 ;
    
    if (vet[mid] < vet[p]) 
        troca(&vet[mid], &vet[p]) ;
    
    if (vet[r] < vet[p])
        troca(&vet[r], &vet[p]) ;
    
    if (vet[r] < vet[mid])
        troca(&vet[r], &vet[mid]) ;
    
    troca(&vet[mid], &vet[r-1]) ;
    pivo = vet[r-1] ;
    
    return divide(vet, p, r);
}

void quick_sort1(int vet[], int p, int count, int r)
{
    if (p < r) 
    {
        int pi = divide(vet, p, r);
        //ordenando :
        quick_sort1(vet, p, count+1, pi - 1) ; //elementos a esquerda do pivo
        quick_sort1(vet, pi + 1, count+1, r) ; //elementos a direita do pivo
    }
   // else{ 
   //     printf("%d\n", count) ;
   // }
}

void quick_sort2(int vet[], int p, int count, int r)
{
    if (p < r) 
    {
        int pi = mediana(vet, p, r);
        //ordenando :
        quick_sort2(vet, p, count+1, pi - 1) ; //elementos a esquerda do pivo
        quick_sort2(vet, pi + 1, count+1, r) ; //elementos a direita do pivo
    }//else
    //    printf ("%d\n", count) ;
}

int main()
{
    start() ;
    return 0; 
}

esse aqui:

#include <stdio.h>
#include <stdlib.h>

//https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/quick.html

void troca(int *a, int *b)
{
    int t = *a ;
    *a = *b ;
    *b = t ;
}

void start ()
{
    int tam_vet, i ;
    int *vet, *vet2 ;
    
    scanf ("%d", &tam_vet) ;
    vet = malloc (tam_vet * sizeof(int)) ;
    for (i = 0 ; i < tam_vet ; i++)
    {
        scanf ("%d", &vet[i]) ;
    }
    vet2 = malloc (tam_vet * sizeof(vet)) ;
    for (i = 0 ; i < tam_vet ; i++) //copiando vetor para implementação do quicksort utiliziando a mediana
    {
        vet2[i] = vet[i] ;
    }
    printf ("Vet 1:") ;
    quick_sort1(vet, 0, tam_vet - 1, 0);
    printf("\nVet 2:\n") ;
    quick_sort2(vet2, 0, tam_vet - 1, 0);
	
	for(i = 0; i < tam_vet; i++) //print para auxiliar
	    printf("%d ", vet[i]);
	printf ("\n\n") ;
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet2[i]);
}

int divide(int vet[], int p, int r)
{
    int pivo = vet[r];
    int i = (p - 1);
    printf ("\npivo = %d\n", pivo) ;
    for (int k = p; k <= r ; k++)
    {
        printf ("%d ", vet[k]) ;
    }
    for (int j = p ; j < r ; j++)
    {
        if (vet[j] < pivo)
        {
            troca(&vet[++i], &vet[j]);
        }
    }
    troca(&vet[i + 1], &vet[r]);
    printf ("\n") ;
    for (int k = p; k <= r ; k++)
    {
        printf ("%d ", vet[k]) ;
    }
    printf ("\n");
    return (i + 1);
}

int mediana(int vet[], int p, int r)
{
    int pivo ;
    int mid = (p + (r+1))/ 2 ;
    
    if (vet[mid] < vet[p]) 
        troca(&vet[mid], &vet[p]) ;
    
    if (vet[r] < vet[p])
        troca(&vet[r], &vet[p]) ;
    
    if (vet[r] < vet[mid])
        troca(&vet[r], &vet[mid]) ;
    
    troca(&vet[mid], &vet[r-1]) ;
    pivo = vet[r-1] ;
    
    return divide(vet, p, r);
}

void quick_sort1(int vet[], int p, int r, int count)
{
    if (p < r) 
    {
        int pi = divide(vet, p, r);
        //ordenando :
        quick_sort1(vet, p, pi - 1, count+1) ; //elementos a esquerda do pivo
        quick_sort1(vet, pi + 1, r, count+1) ; //elementos a direita do pivo
    }
   // else{ 
   //     printf("%d\n", count) ;
   // }
}

void quick_sort2(int vet[], int p, int r, int count)
{
    if (p < r) 
    {
        int pi = mediana(vet, p, r);
        //ordenando :
        quick_sort1(vet, p, pi - 1, count+1) ; //elementos a esquerda do pivo
        quick_sort1(vet, pi + 1, r, count+1) ; //elementos a direita do pivo
    }
}
int main()
{
    start() ;
    return 0; 
}
