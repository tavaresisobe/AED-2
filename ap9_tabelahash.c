/* Programa: lab 4
   Autor: Gustavo Henrique Tavares Isobe -  RA: 158552 
   Versao: 1.0 - 20/12/2022 - 20:24 h
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

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
    novo->ant = NULL ;
    listaAux->primeiro = novo ;
    listaAux->ultimo = novo ;
    listaAux->tamanhoLista++; 
  }else{
      novo->prox = NULL;
      novo->ant = listaAux->ultimo;
      listaAux->ultimo->prox = novo;
      listaAux->ultimo=novo; 
      listaAux->tamanhoLista++; 
  }
}

int h1 (int k, int m)
{
    return k % m ;
}

int h2 (int k, int m)
{
    return 1 + (k % (m - 1)) ;
}

int f_transformacao(int k, int m)
{
    int i = 1 ;
    return ((h1(k, m) + i * h2(k, m)) % m) ;
}
/*
h1(k) = k mod m
h2(k) = 1 + (k mod (m − 1))
h(k, i) = (h1(k) + ih2(k)) mod m
*/

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

int main ()
{
  tipoElemento elementoS ;
  tipoLDDE listaDDE ;
  inicializaLista(&listaDDE) ;

  int i;
  for (i = 0 ; i < 10 ; i++)
  {
    insereElementoFinal(&listaDDE) ;
  }
  listarLista(&listaDDE) ;
  return 0 ;
}
// 1 6 4 3 2 7 0 5 3 9 2 8 1 0 1 0 4 0 2 0