#include<stdio.h>
#include<stdlib.h>

struct ABB_AVL{
    int chave ;
    struct ABB_AVL *esq ;
    struct ABB_AVL *dir ;
    int h ;
};
typedef struct ABB_AVL TipoArvore ;
typedef TipoArvore* TipoABB_AVL ;


int arvoreVazia(TipoABB_AVL aux)
{
    return aux == NULL ;
}

TipoABB_AVL inicializaArvore()
{
    return NULL ;
}

int max(int a, int b)
{
    if(a > b)
        return a ;
    else
        return b ;
}

TipoABB_AVL insereNo(int num)
{
    TipoABB_AVL novo = (TipoABB_AVL)malloc(sizeof(TipoArvore)) ;
    if (novo)
    {
        novo->chave = num ;
        novo->esq = NULL ;
        novo->dir = NULL ;
        novo->h = 1 ;
    }else
        printf ("Erro ao alocar memoria\n") ;
    return novo ;
}

int altura(TipoABB_AVL aux)
{
    if(aux == NULL) return 0 ;
    return aux->h ;
}

TipoABB_AVL rotaciona_dir_avl(TipoABB_AVL aux)
{
    TipoABB_AVL x = aux->esq ; 
    aux->esq = x->dir ;
    x->dir = aux ;
    
    aux->h = max(altura(aux->esq),altura(aux->dir)) + 1 ;
    x->h = max(altura(x->esq),altura(x->dir)) + 1 ;
 
    return x ;
  
}

TipoABB_AVL rotaciona_esq_avl(TipoABB_AVL aux)
{
    TipoABB_AVL x = aux->dir ; 
    aux ->dir = x->esq ;
    x->esq = aux ;
    
    aux->h = max(altura(aux->esq),altura(aux->dir)) + 1 ;
    x->h = max(altura(x->esq),altura(x->dir)) + 1 ;

    return x ;
  
}

TipoABB_AVL rotaciona_esq_dir(TipoABB_AVL aux)
{
    aux->esq = rotaciona_esq_avl(aux->esq) ;
    return rotaciona_dir_avl(aux) ;
}

TipoABB_AVL rotaciona_dir_esq(TipoABB_AVL aux)
{
    aux->dir = rotaciona_dir_avl(aux->dir) ;
    return rotaciona_esq_avl(aux) ;
}

int fb(TipoABB_AVL aux)
{
    if (aux == NULL)
        return 0 ;
    return altura(aux->esq) - altura(aux->dir) ;
}


TipoABB_AVL insereAVL(TipoABB_AVL aux, int info, int* rotate_avl)
{
    if (aux == NULL)
        return insereNo(info) ;
    if (info < aux->chave)
        aux->esq = insereAVL(aux->esq, info, rotate_avl) ;
    else if (info > aux->chave)
        aux->dir = insereAVL(aux->dir, info, rotate_avl) ;
    else
        return aux ; 

    aux->h = max(altura(aux->esq), altura(aux->dir))+1 ;

    // verifica o fator de balanceamento da arvore avl
    int x = fb(aux) ;

    if (x > 1 && fb(aux->esq) >= 0)
    {
        *rotate_avl += 1 ;
        return rotaciona_dir_avl(aux) ;
    }
    if (x < -1 && fb(aux->dir) <= 0)
    {
        *rotate_avl += 1 ;
        return rotaciona_esq_avl(aux) ;
    }
    if (x > 1 && fb(aux->esq) < 0)
    {
        *rotate_avl += 1 ;
        return rotaciona_esq_dir(aux) ;
    }
    if (x < -1 && fb(aux->dir) > 0) 
    {
        *rotate_avl += 1 ;
        return rotaciona_dir_esq(aux) ;
    }
    return aux ;
}

int alturaAVL(TipoABB_AVL aux)
{
    if(aux == NULL)
            return 0 ;
        else
            return 1 + max(alturaAVL(aux->esq), alturaAVL(aux->dir)) ;
}


int main() 
{
    TipoABB_AVL raiz = inicializaArvore(),aux ;
    int i = 0, j, n ;
    int vet[20] ;
	scanf ("%d", &n) ;
    while (n != -1)
    {
        vet[i] = n ;
        scanf ("%d", &n) ;
        i++ ;
    }
    int rotate_avl = 0 ;
	for (j = 0 ; j < i ; j++)
	{
	    raiz = insereAVL(raiz, vet[j], &rotate_avl) ;
	}
	
    printf("%d,%d,%d\n",alturaAVL(raiz)-1, 
            alturaAVL(raiz->esq),alturaAVL(raiz->dir)) ;
    printf ("%d", rotate_avl) ;
    return 0 ;
}