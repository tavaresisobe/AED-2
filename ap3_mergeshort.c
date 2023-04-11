/* Programa: 
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 05/4/2023 - :h
*/

//https://www.geeksforgeeks.org/c-program-for-merge-sort/


// ##################### Bibliotecas Externas ##############################
 
#include<stdio.h>
#include<stdlib.h> 

// ########################## TAD X.h ######################################

struct elemento {
  int info ;
  struct elemento *prox ;
};
typedef struct elemento tipoElemento ;

struct estruturaLDDE{
  tipoElemento *primeiro ;
  tipoElemento *ultimo ;
  int tamanhoLista ;
};
typedef struct estruturaLDDE tipoLDDE ;

// ###################### Funcoes e Procedimentos do programa ##############

void mergeShort() ;
void Merge() ;

void inicializaLista (tipoLDDE *listaAux)
{
  listaAux->primeiro = NULL;
  listaAux->ultimo = NULL ;
  listaAux->tamanhoLista = 0 ;
}

void insereElementoFinal (tipoLDDE *listaAux)
{
  tipoElemento *novo = (tipoElemento*) malloc(sizeof(tipoElemento));
  scanf("%d", &novo->info) ;
  if (listaAux->tamanhoLista == 0)
  {
    novo->prox = NULL ;
    listaAux->primeiro = novo ;
    listaAux->ultimo = novo ;
    listaAux->tamanhoLista++; 
  }else{
      novo->prox = NULL;
      listaAux->ultimo->prox = novo;
      listaAux->ultimo=novo;
      listaAux->tamanhoLista++; 
  }
}

//


//

void listarLista(tipoLDDE *listaAux)
{
  tipoElemento *p ;
  if (listaAux->primeiro > 0)
  {
    p = listaAux->primeiro ;
    while (p)
    {
        printf ("%d ", p->info) ;
        p = p->prox ;
    }printf ("\n") ;
  }
   #include <stdio.h>
#include <stdlib.h>
 
void merge(int arr[], int l, int m, int r, int *count)

{
    int i, j, k, counta = 0;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l; 
  
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        //  counta += 1 ;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
      arr[k] = L[i];
      i++;
      k++;
      counta += 1 ;
    }
    while (j < n2) {
      arr[k] = R[j];
      j++;
      k++;
      counta += 1 ;
    }
  printf ("%d\n", counta) ;
}

void mergeSort(int arr[], int l, int r, int *count)
{
    if (l < r) {
      *count +=1 ;
      int m = l + (r - l) / 2;
      mergeSort(arr, l, m, count);
      mergeSort(arr, m + 1, r, count);
      merge(arr, l, m, r, count);
    }
}
 
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main()
{
  int arr[] = { 1, 2, 3, 4, 5, 6, 8, 9, 10, 20 };
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  printf ("Tamanho da array: %d\n", arr_size) ;
  int count = 0 ;
  //printf("Given array is \n");
  printArray(arr, arr_size);
  
  mergeSort(arr, 0, arr_size - 1, &count);
  printf("\nSorted array is \n");
  printArray(arr, arr_size);
  printf ("contador principal: %d\n", count) ;
  return 0;
 
}
//1, 2, 3, 4, 5, 6, 8, 9, 10, 20
//3, 5, 2, 1, 4, 6
}

// ############################ Principal ###################################

int main(void) 
{
  tipoElemento elementoS ;
  tipoLDDE listaDDE ;
  inicializaLista(&listaDDE) ;

  int num_chaves ;
  scanf ("%d", &num_chaves) ;
  for (int i = 0 ; i < num_chaves ; i++)
  {
    insereElementoFinal(&listaDDE) ;
  }
  printf("\n\nLista:\n") ;
  listarLista(&listaDDE) ;
  
  return 0;
}

//teste: 10 1 2 3 4 5 6 8 9 10 20 saida: 4
//teste: 6 3 5 2 1 4 6 saida: 3
//teste: 5 1 5 3 4 2 saida: 3
