/* Programa: AP7 - Arvore AVL
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 3.0 - 18/05/2023 - 22:51h
*/
 
// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
 
//testes:
//6 4 3 2 1 -1 4 5 -1 1
//16 14 20 12 11 19 18 15 17 13 -1 14 19 15 20 -1 18
 
// ########################## TAD X.h ######################################
 
typedef int key ;
typedef struct {
    key chave ;
} TItem;
typedef struct No *TArvBin ;
 
typedef struct No {
    TItem Item ;
    key fb ;
    TArvBin esq, dir ;
} TNo;
typedef TArvBin TABB;
 
// ###################### Funcoes e Procedimentos do programa ##############
 
//func para inicializar os ponteiros
TArvBin nulo()
{
     return NULL;
}
 
//Retorna um apontador para um nó contendo o item x e as subárvores Esq e Dir
TArvBin inicializa(TItem info, TArvBin esq, TArvBin dir)
{
    TArvBin novoNo = (TArvBin) malloc(sizeof(TNo)) ;
    if (novoNo)
    {
        novoNo->Item = info ;
        novoNo->fb = 0 ;
        novoNo->esq = esq ;
        novoNo->dir = dir ;
    }else printf ("Erro ao alocar memoria\n") ;
 
    return novoNo;
}
 
int insereAVL(TABB *raiz, TItem info)
{
    if (*raiz == NULL) {
        *raiz = inicializa(info, nulo(), nulo()) ;
        return 1;
    }
    else if (info.chave < (*raiz)->Item.chave)
        return insereAVL(&(*raiz)->esq, info) ;
    else if (info.chave > (*raiz)->Item.chave)
        return insereAVL(&(*raiz)->dir, info) ;
    else
        return 0 ; // retorna 0 se o elemento for repetido
}
 
//realiza a busca bin na AVL e retorna (NULL se elemento nn existir/ Endereço se o elemento existir)
TABB buscaAVL(TABB raiz, key info)
{
    if (raiz == NULL)
        return NULL ;
    else if (info < raiz->Item.chave)
        return buscaAVL(raiz->esq, info) ;
    else if (info > raiz->Item.chave)
        return buscaAVL(raiz->dir, info) ;
    else
        return raiz ;
}
 
void sucessorAVL(TABB *q, TABB *r)
{
  if ((*r)->esq != NULL)
    sucessorAVL(q, &(*r)->esq) ;
  else
  {
    (*q)->Item = (*r)->Item;
    *q = *r ;
    *r = (*r)->dir ;
  }
}
 
int removeAVL(TABB *p, key x)
{
  TABB q ;
  if (*p == NULL)
    return 0 ;
  else if (x < (*p)->Item.chave)
    return removeAVL(&(*p)->esq, x) ;
  else if (x > (*p)->Item.chave)
    return removeAVL(&(*p)->dir, x) ;
  else {
    q = *p ;
    if (q->esq== NULL)
      *p = q->dir ;
    else if (q->dir == NULL)
            *p = q->esq ;
    else // caso o noh possua dois filhos
      sucessorAVL(&q, &q->dir) ;
      free(q) ;
      return 1 ;
  }
}
 
//funcao aux para retornar maior elemento
int max(int a, int b)
{
  if(a > b)
    return a;
  else
    return b;
}
 
//retorna altura do no
int alturaAVL(TABB No)
{
  if(No == NULL)
    return 0 ;
  else
    return 1 + max(alturaAVL(No->esq), alturaAVL(No->dir)) ;
}
 
//retorna o fb
void fatorbalanciamento(TABB *p)
{
  if (*p != NULL)
  {
    fatorbalanciamento(&(*p)->esq) ;
    fatorbalanciamento(&(*p)->dir) ;
    (*p)->fb = alturaAVL((*p)->esq) - alturaAVL((*p)->dir) ;
  }
}
 
//RotaçãoLL
TArvBin rotaciona_dir_LL(TABB *pA) 
{
    TABB pB = (*pA)->esq ;
    (*pA)->esq = pB->dir ;
    
    pB->dir = *pA ;
    *pA = pB ;
 
    return *pA ;
 
}
 
//RotaçãoRR
TArvBin rotaciona_esq_RR(TABB *pA) 
{
    TABB pB = (*pA)->dir ;
    (*pA)->dir = pB->esq ; 
 
    pB->esq = *pA ;
    *pA = pB ;
 
    return *pA ;
}
 
//RotaçãoLR
TArvBin rotaciona_dir_LR(TABB *pA) 
{
    TABB pB = (*pA)->esq ;
    TABB pC = pB->dir ;
    
    pB->dir = pC->esq ;
    pC->esq = pB;
 
    (*pA)->esq = pC->dir ;
    pC->dir = *pA;
    *pA = pC;
 
    return *pA;
}
 
//RotaçãoRL
TArvBin rotaciona_esq_RL(TABB *pA) {
 
    TABB pB = (*pA)->dir ;
    TABB pC = pB->esq ;
    
    pB->esq = pC->dir ;
    pC->dir = pB;
    
    (*pA)->dir = pC->esq ;
    pC->esq = *pA;
 
    *pA = pC;
 
    return *pA;
}
 
void balanceiaAVL(TABB *p, TABB *raiz)
{
  if (*p != NULL)
  {
    balanceiaAVL(&(*p)->esq, raiz) ; 
    balanceiaAVL(&(*p)->dir, raiz) ;
    if ((*p)->fb > 1) 
    {
      if ((*p)->esq->fb >= 0)
      {
        *p = rotaciona_dir_LL(&(*p)) ;
        fatorbalanciamento(&(*raiz)) ;
      }
      else{
        *p = rotaciona_dir_LR(&(*p)) ; 
        fatorbalanciamento(&(*raiz)) ; 
      }
    }else 
      if ((*p)->fb < -1) 
      {
        if ((*p)->dir->fb <= 0)
        {
          *p = rotaciona_esq_RR(&(*p)) ;
          fatorbalanciamento(&(*raiz)) ;
        }else{
          *p = rotaciona_esq_RL(&(*p)) ;
          fatorbalanciamento(&(*raiz)) ; 
        }
      }
  }
}
 
/*void imprimir(TABB *aux)
{
  if (aux!= NULL)
        printf("%d ", aux->Item.chave) ;
    if (aux->dir != NULL)
        imprimir(aux->dir) ;
    if (aux->esq != NULL)
        imprimir(aux->esq) ;
}*/
 
void desaloca(TArvBin No) 
{
  if (No != NULL) 
  {
    desaloca(No->esq) ;
    desaloca(No->dir) ;
    free(No);
  }
}
 
// ############################ Principal ###################################
 
int main()
{
  TABB raiz;
  raiz = (TABB)malloc(sizeof(TArvBin)) ;
  raiz = nulo() ;
  TItem valor ;
 
  scanf("%d", &valor.chave);
  while(valor.chave > 0)
  {
    insereAVL(&raiz, valor) ; 
    fatorbalanciamento(&raiz) ; 
    balanceiaAVL(&raiz, &raiz) ; 
    scanf("%d", &valor.chave) ;
  }
  printf("%d,%d,%d\n", alturaAVL(raiz)-1, alturaAVL(raiz->esq), alturaAVL(raiz->dir)) ;
  TItem x ;
  scanf("%d", &x.chave) ;
    
  while(x.chave > 0)
  {
    if(buscaAVL(raiz, x.chave) != NULL)
    {
      removeAVL(&raiz, x.chave) ;
      fatorbalanciamento(&raiz) ; 
      balanceiaAVL(&raiz, &raiz) ;
    }
    else{
      insereAVL(&raiz, x) ;
      fatorbalanciamento(&raiz) ;
      balanceiaAVL(&raiz, &raiz) ;
    }
      scanf("%d", &x.chave) ;
  }
  
  key i;
  scanf("%d", &i) ;
  TABB result = nulo() ;
  result = buscaAVL(raiz, i) ;
 
  if(result != NULL)
    printf("%d,%d,%d\n", alturaAVL(result)-1, alturaAVL(result->esq), alturaAVL(result->dir)) ;
    //printf ("Valor encontrado\n") ;
  else{
    printf("Valor nao encontrado") ;
  }
//  imprimir(&raiz) ;
  desaloca(raiz);
  free(result);
 
  return 0;
}