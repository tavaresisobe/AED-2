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
