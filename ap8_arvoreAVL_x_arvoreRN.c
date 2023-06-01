/* Programa: AP8 - Arvore AVL x Arvore RN
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 9.0 - 30/05/2023 - 00:25h
*/
 
// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
 
// ########################## TAD X.h ######################################
 
struct tipoABB_RN{ //Arvore Rubro Negra
    int chave ;
    struct tipoABB_RN* pai ; // noh pai
    struct tipoABB_RN* esq ;
    struct tipoABB_RN* dir ;
    int cor ; // 0 - Negra, 1 - Rubro
};
//ponteiro para a raiz
struct tipoABB_RN* root = NULL;
 
struct ABB_AVL{ //Arvore AVL
    int chave ;
    struct ABB_AVL *esq ;
    struct ABB_AVL *dir ;
    int h ;
};
typedef struct ABB_AVL TipoArvore ;
typedef TipoArvore* TipoABB_AVL ;
 
// ###################### Funcoes e Procedimentos do programa - ABB RUBRO NEGRA ##############
 
//Obs.: Removi todas funcoes que nao serao utilizadas
 
//retorna maior valor entre de 2 elementos
int max(int a, int b)
{
  if(a > b)
    return a ;
  else
    return b ;
}
 
//rotacao para a esquerda:
void rotacionaDir(struct tipoABB_RN* aux)
{
    struct tipoABB_RN* esquerda = aux->esq ;
    aux->esq = esquerda->dir ;
 
    if (aux->esq)
        aux->esq->pai = aux ;
    esquerda->pai = aux->pai ;
    if (!aux->pai)
    {
        root = esquerda ;
    }else if (aux == aux->pai->esq)
    {
        aux->pai->esq = esquerda ;
    }else
        aux->pai->dir = esquerda ;
        
    esquerda->dir = aux ;
    aux->pai = esquerda ;
}
 
//rotacao para a direita
void rotacionaEsq(struct tipoABB_RN* aux)
{
    struct tipoABB_RN* direita = aux->dir ;
    aux->dir = direita->esq ;
    
    if (aux->dir)
        aux->dir->pai = aux ;
    direita->pai = aux->pai ;
    if (!aux->pai)
    {
        root = direita ;
    }else if (aux == aux->pai->esq){
        aux->pai->esq = direita ;
    }else
        aux->pai->dir = direita ;
        
    direita->esq = aux ;
    aux->pai = direita ;
}
 
//busca o No, onde sera inserido o no folha
struct tipoABB_RN* buscaPai(struct tipoABB_RN* raiz, 
                                struct tipoABB_RN* aux)
{
    //caso AbbRN estiver vazia
    if (raiz == NULL)
        return aux ;
 
    if (aux->chave < raiz->chave)
    {
        raiz->esq = buscaPai(raiz->esq, aux) ;
        raiz->esq->pai = raiz ;
    }
    else if (aux->chave > raiz->chave)
    {
        raiz->dir = buscaPai(raiz->dir, aux) ;
        raiz->dir->pai = raiz ;
    }
    return raiz ;
}
 
struct tipoABB_RN* criaNo(int chave)
{
    struct tipoABB_RN* aux
            = (struct tipoABB_RN*)malloc(sizeof(struct tipoABB_RN)) ;
    if (aux)
    {
        aux->esq = NULL ;
        aux->dir = NULL ;
        aux->pai = NULL ;
        aux->chave = chave ;
        aux->cor = 1 ;
    }else
        printf ("Erro ao alocar memoria\n") ;
    return aux ;
}
 
void insereABBRubroNegra(int chave, int *mudacor, int *rotate)
{
    struct tipoABB_RN* temp = criaNo(chave) ;
    if (temp)
    {
        //insere o novo noh, e retorna seu rrespectivo no pai
        root = buscaPai(root, temp) ;
        fixup(root, temp, mudacor, rotate) ;
        root->cor = 0 ;
    }
}
 
//funcao para concertar desbalanceamento causado pela insercao
void fixup(struct tipoABB_RN* raiz, struct tipoABB_RN* aux, 
            int *mudacor, int *rotate)
{
    struct tipoABB_RN* pai = NULL ;
    struct tipoABB_RN* avo = NULL ;
 
    while ((aux != raiz) && (aux->cor != 0)
        && (aux->pai->cor == 1))
    {
        pai = aux->pai ;
        avo = aux->pai->pai ;
        if (pai != NULL && avo != NULL)
        {
            //rotacoes para esquerda:
            if (pai == avo->esq)
            {
                struct tipoABB_RN* tio_esq_aux = avo->dir ;
                if (tio_esq_aux != NULL && tio_esq_aux->cor == 1)
                {
                    if (avo->cor != 1)
                    {
                        avo->cor = 1 ;
                        *mudacor += 1 ;
                    }
                    if (pai->cor != 0)
                    {
                        pai->cor = 0 ;
                        *mudacor += 1 ;
                    }
                    if (tio_esq_aux->cor != 0)
                    {
                        tio_esq_aux->cor = 0 ;
                        *mudacor += 1 ;
                    }
                    aux = avo ;
                }else{
                    if (aux == pai->dir)
                    {
                        rotacionaEsq(pai) ;
                        *rotate += 1 ;
                        aux = pai ;
                        pai = aux->pai ;
                    }
                    rotacionaDir(avo) ;
                    *rotate += 1 ;
                    int t = pai->cor ;
                    if (pai->cor != avo->cor)
                    {
                        pai->cor = avo->cor ;
                        *mudacor += 1 ;
                    }
                    if (avo->cor != t)
                    {
                        avo->cor = t ;
                        *mudacor += 1 ;
                    }
                    aux = pai ;
                }
        }
 
        //rotacoes para direita:
        else{
            struct tipoABB_RN* tio_dir_aux = avo->esq ;
            if ((tio_dir_aux != NULL) && (tio_dir_aux->cor == 1))
            {
                if (avo->cor != 1)
                {
                    avo->cor =  1 ;
                    *mudacor += 1 ;
                }
                if (pai->cor != 0)
                {
                    pai->cor = 0 ;
                    *mudacor += 1 ;
                }
                if (tio_dir_aux->cor != 0)
                {
                    tio_dir_aux->cor = 0 ;
                    *mudacor += 1 ;
                }
                aux = avo ;
            }else{
                if (aux == pai->esq)
                {
                    rotacionaDir(pai) ;
                    *rotate += 1 ;
                    aux = pai ;
                    pai = aux->pai ;
                }
                rotacionaEsq(avo) ;
                *rotate += 1 ;
                int t = pai->cor ;
                if (pai->cor != avo->cor)
                {
                    pai->cor = avo->cor ;
                    *mudacor += 1 ;
                }
                if (avo->cor != t)
                {
                    avo->cor = t ;
                    *mudacor += 1 ;
                }
                aux = pai ;
            }
        }
        }
    }
}
 
int alturaNoPreto(struct tipoABB_RN* aux)
{
    if (aux == NULL)
        return 0 ;
    else{
        int left = alturaNoPreto(aux->esq) ;
        int right = alturaNoPreto(aux->dir) ;
        if (aux->cor == 0)
        {
            if (left > right)
                return left + 1 ;
            else 
                return right + 1 ;
        }else
            if (left > right)
                return left ;
            else
                return right ;
    }
}
 
//funcao para calcular altura da AbbRN
int alturaRN(struct tipoABB_RN* aux)
{
        if(aux == NULL)
            return 0 ;
        else
            return 1 + max(alturaRN(aux->esq), alturaRN(aux->dir)) ;
}
 
void preordem(struct tipoABB_RN* aux)
{
    if (aux!= NULL)
        printf("%d-%d  ", aux->chave, aux->cor) ;
    if (aux->dir != NULL)
        preordem(aux->dir) ;
    if (aux->esq != NULL)
        preordem(aux->esq) ;
}
 
// ###################### Funcoes e Procedimentos do programa - ABB AVL ##############
 
int arvoreVazia(TipoABB_AVL aux)
{
    return aux == NULL ;
}
 
TipoABB_AVL inicializaArvore()
{
    return NULL ;
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
 
// ############################ Principal ###################################
 
 
 
int main()
{
    TipoABB_AVL raiz = inicializaArvore(),aux ;
    int i = 0, j, n, y = 0 ;
    int vet[100000] ;
    scanf ("%d", &n) ;
    while (n != -1)
    {
        vet[i] = n ;
        i++ ;
        scanf ("%d", &n) ;
    }
    int rotate_avl = 0 ;
    int mudacor = 0, rotate = 0, c_esq = 0, c_dir = 0 ;
    
    if (i > 0)
    {
        for (j = 0 ; j < i ; j++)
        {
            raiz = insereAVL(raiz, vet[j], &rotate_avl) ;
        }
 
        for (j = 0 ; j < i ; j++)
        {
            insereABBRubroNegra(vet[j], &mudacor, &rotate) ;
        }
        //preordem(root) ;
    }
    printf("%d,%d,%d\n",alturaAVL(raiz)-1, 
            alturaAVL(raiz->esq),alturaAVL(raiz->dir)) ;
    printf ("%d,%d,%d\n", alturaRN(root)-1, alturaRN(root->esq),
                    alturaRN(root->dir)) ;
    printf("%d\n", max(alturaNoPreto(root->dir), alturaNoPreto(root->esq)) + 1) ;
    printf ("%d,%d,%d\n", mudacor, rotate, rotate_avl) ;
 
    return 0 ;
}
