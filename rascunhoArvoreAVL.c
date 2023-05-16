/* Programa: lab 5
   Autor: Gustavo Henrique Tavares Isobe -  RA: 158552 
   Versao: 2.0 - 20/11/2022 - 22:02 h
*/

//https://wagnergaspar.com/testando-nossa-arvore-binaria-de-busca-balanceada-arvore-avl/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

struct noArvoreBB {
  int chave ;
  struct noArvoreBB* esq;
  struct noArvoreBB* dir;
  int altura ;
};
typedef struct noArvoreBB tipoABB;

// ###################### Funcoes e Procedimentos do programa ##############

void inicializa(int c, tipoABB *arvoreAux)
{
    arvoreAux->chave = c;
    arvoreAux->esq = NULL;
    arvoreAux->dir=NULL;
}

tipoABB* insereNo(int c)
{
    tipoABB* novo = malloc(sizeof(tipoABB));
    if (novo)
    {
        novo->chave = c ;
        novo->dir = NULL;
        novo->esq= NULL;
    }else
        printf ("Erro ao alocar memória\n") ;
    return novo;
}

void insereABB (int chave, tipoABB *Aux)
{
    if (chave < Aux->chave)
    {
        if (Aux->esq == NULL)
            Aux->esq = insereNo (chave);
        else insereABB (chave, Aux->esq);
    }else 
        if (chave > Aux->chave)
            if (Aux->dir == NULL)
                Aux->dir = insereNo (chave) ;
            else insereABB (chave, Aux->dir) ;
        else printf("Elemento Existente!") ;
}

/*
tipoABB* removeABB(tipoABB *Aux, int info)
{
    tipoABB *temp ;
    if (Aux == NULL)
        return NULL ;
    else
        if (Aux->chave > info)
        {
            Aux-> esq = removeABB(Aux->esq, info) ; 
        }else 
        if (Aux->chave < info)
        {
            Aux->dir = removeABB(Aux->dir, info) ;
        }else{
        if ((Aux->esq != NULL) && (Aux->dir != NULL))
        {
            temp = maiorValor(Aux->esq) ;
            Aux->chave = temp->chave ;
            temp->chave = info ;
            Aux->esq = removeABB(Aux->esq, info) ;
        }else if (Aux->esq != NULL){
                temp = Aux ;
                Aux = Aux->esq ;
                free(temp) ;
        }else if (Aux->dir != NULL){
                temp = Aux ;
                Aux = Aux->dir ;
                free(temp) ;
        }else
            free(Aux) ;
            return NULL ;
  }
}
*/

void imprime (tipoABB *aux)
{
    if (aux!= NULL)
        printf("%d ", aux->chave);
    if (aux->dir!= NULL)
        imprime(aux->dir);
    if (aux->esq!= NULL)
        imprime(aux->esq);
}

// ############################ Principal ###################################

int main(void)
{
    int entrada, chave, i, raiz ;
    tipoABB *arvore = (tipoABB *) calloc(1, sizeof(tipoABB));
    scanf ("%d", &entrada) ;
    if (entrada > 0)
    {
        scanf ("%d", &chave) ;
        inicializa(chave, arvore);
    }
    for (i = 0 ; i < entrada ; i++)
    {
        scanf("%d", &chave) ;
        insereABB(chave, arvore) ;
    }
    imprime(arvore) ;
    return 0;
}
