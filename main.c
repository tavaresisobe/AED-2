#include <stdio.h>

#include <stdlib.h>



//https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/quick.html


void imprime (int vet[], int vet2[], int n);
void troca(int *a, int *b);
int divide(int vet[], int p, int r);
void quick_sort1(int vet[], int p, int r, int count, int *min, int *max);
void quick_sort2(int vet[], int p, int r, int count, int *min, int *max);
void imprime (int vet[], int vet2[], int n);
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

   

    quick_sort1(vet, 0, n - 1, 0, &min, &max);

    printf ("Vet 1:\n%d\n", max - min) ;

    min = n, max = 0 ;

    quick_sort2(vet2, 0, n - 1, 0, &min, &max);

	printf ("Vet 2:\n%d\n", max - min) ;

	

	imprime(vet, vet2, n) ; //print p/ testar ordenamento

}



int divide(int vet[], int p, int r)

{

    int pivotIndex = r;
        
        int pivotValue = vet[pivotIndex];
        troca(&vet[pivotIndex], &vet[r]);
        int storeIndex = p;
        for (int i = p; i < r; i++) {
            if (vet[i] < pivotValue) {
                troca(&vet[i], &vet[storeIndex]);
                storeIndex++;
            }
        }
        troca(&vet[storeIndex], &vet[r]);
        return storeIndex;

}

/* PARA DESCOMENTAR, Ctrl+K+U no VScode*/

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

void quick_sort1(int vet[], int p, int r, int count, int *min, int *max)

{

    if (p >= r) {

        if(count < *min) 

            *min = count;

        if(count > *max) 

            *max = count ;

        printf("TESTE %d %d\n", *max, *min);

        return;

    }

    int pi = divide(vet, p, r);

    quick_sort1(vet, p, pi - 1, count+1, min, max) ;

    quick_sort1(vet, pi + 1, r, count+1, min, max) ;

    }



void quick_sort2(int vet[], int p, int r, int count, int *min2, int *max2)

{
    if (p >= r) {

        if(count < *min2) 

            *min2 = count;

        if(count > *max2) 

            *max2 = count ;

        printf("TESTE %d %d\n", *max2, *min2);

        return;

    }

    int pi = mediana(vet, p, r);

    quick_sort1(vet, p, pi - 1, count+1, min2, max2) ;

    quick_sort1(vet, pi + 1, r, count+1, min2, max2) ;

    }



void imprime (int vet[], int vet2[], int n)

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



int main()

{

    start() ;

    return 0; 

}

/*

input:

31

95 37 82 31 73 82 45 83 22 50 78 96 77 62 59 22 95 36 94 49 48 69 98 93 37 96 33 29 78 62 16

output:

6

6

input:

12

6 9 17 61 8 46 83 85 19 71 79 19

output:

2

2
*/
