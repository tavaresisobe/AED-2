/*
   Programa: ABB

   Autor: Mateus Gomes Ferreira - RA: 140886

   Versao: 2.2 - 03/09/2020
*/

// ##################### Bibliotecas Externas ##############################


#include <stdio.h>
#include <stdlib.h>


// ########################## TAD X.h ######################################


struct Arvore
{
    struct arvoreBinariaBusca *raiz;
    int tam;
    int alt;
};
typedef struct Arvore tipoArvore;

struct arvoreBinariaBusca
{
    int info;
    struct arvoreBinariaBusca *esq;
    struct arvoreBinariaBusca *dir;
    struct arvoreBinariaBusca *pai;
};
typedef struct arvoreBinariaBusca tipoABB;


// ###################### Funcoes e Procedimentos do programa ##############


void inicializaArvore(tipoArvore *arvo)
{
    arvo->raiz = NULL;
    arvo->alt = 0;
    arvo->tam = 0;
}

tipoABB* criaNo(int chave)
{
    tipoABB *no = (tipoABB *) calloc(1, sizeof(tipoABB));

    no->dir = NULL;
    no->esq = NULL;
    no->info = chave;
    no->pai = NULL;

    return no;
}

void insereArvore(tipoArvore *arvo, int chave)
{
    tipoABB *raizAux = arvo->raiz, *paiAux = NULL, *novo = criaNo(chave);

    while(raizAux != NULL)
    {
        paiAux = raizAux;
        if(novo->info < raizAux->info) raizAux = raizAux->esq;
        else raizAux = raizAux->dir;
    }
    novo->pai = paiAux;

    if(paiAux == NULL) arvo->raiz = novo;
    else if(novo->info < paiAux->info) paiAux->esq = novo;
    else paiAux->dir = novo;

    arvo->tam = arvo->tam + 1;
}

tipoABB* busca(tipoABB *raiz, int chave)
{
    if(raiz == NULL || chave == raiz->info) return raiz;

    if(chave < raiz->info) return busca(raiz->esq, chave);
    else return busca(raiz->dir, chave);
}

tipoABB* folhaMinima(tipoABB *raiz)
{
    if(raiz->esq != NULL) return folhaMinima(raiz->esq);
    return raiz;
}

tipoABB* folhaMaxima(tipoABB *raiz)
{
    if(raiz->dir != NULL) return folhaMinima(raiz->dir);
    return raiz;
}

/*tipoABB folhaSucessor(tipoABB *raiz)
{
    if(raiz->dir != NULL) return folhaMinima(raiz->dir);

    tipoABB *paiAux = raiz->pai, *raizAux = raiz;

    while(paiAux != NULL && raizAux == paiAux->dir)
    {
        raizAux = paiAux;
        paiAux = paiAux->pai;
    }
    return paiAux;
}*/

void transplanteArvore(tipoArvore *arvo, tipoABB *no1, tipoABB *no2)
{
    if(no1->pai == NULL) arvo->raiz = no2;
    else if(no1 == no1->pai->esq) no1->pai->esq = no2;
    else no1->pai->dir = no2;

    if(no2 != NULL) no2->pai = no1->pai;
}

void deletaNo(tipoArvore *arvo, tipoABB *deletado)
{
    if(deletado->esq == NULL) transplanteArvore(arvo, deletado, deletado->dir);
    else if( deletado->dir == NULL) transplanteArvore(arvo, deletado, deletado->esq);
    else
    {
        tipoABB *aux = folhaMinima(deletado->dir);

        if(aux->pai != deletado)
        {
            transplanteArvore(arvo, aux, aux->dir);
            aux->dir = deletado->dir;
            aux->dir->pai = deletado->pai; //AQUI
        }
        transplanteArvore(arvo, deletado, aux);
        aux->esq = deletado->esq;
        aux->esq->pai = aux;
    }

    arvo->tam = arvo->tam -1;
}

int alturaArvore(tipoABB *raiz)
{
    if(raiz == NULL) return 0;
    else
    {
        int esq = alturaArvore(raiz->esq), dir = alturaArvore(raiz->dir);
        if(esq > dir) return esq + 1;
        else return dir + 1;
    }
}


// ############################ Principal ###################################


int main()
{
    int num;

    tipoArvore *arvore = (tipoArvore *) calloc(1, sizeof(tipoArvore));

    inicializaArvore(arvore);

    while(1)
    {
        scanf("%d", &num);
        if(num >= 0) insereArvore(arvore, num);
        else break;
    }

    arvore->alt = alturaArvore(arvore->raiz);

    scanf("%d", &num);

    printf("%d %d\n", arvore->tam, arvore->alt);

    tipoABB *deletado /*= (tipoABB *) calloc(1, sizeof(tipoABB))*/;
    deletado = busca(arvore->raiz, num);

    if(deletado != NULL) deletaNo(arvore, deletado);
    else insereArvore(arvore, num);

    arvore->alt = alturaArvore(arvore->raiz);

    printf("%d %d\n", arvore->tam, arvore->alt);
}
