/* Programa: AP7 - Arvore AVL
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 2.0 - 18/05/2023 - 02:53h
*/
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

//testes:
//6 4 3 2 1 -1 4 5 -1 1
//16 14 20 12 11 19 18 15 17 13 -1 14 19 15 20 -1 18

// ########################## TAD X.h ######################################

struct No
{
    int info ;
    struct No *esq ;
    struct No *dir ;
    int ht ;
};
struct No *raiz = NULL;

// ###################### Funcoes e Procedimentos do programa ##############
 
struct No *inicializa(int chave)
{
    struct No *novo = (struct No*) malloc (sizeof(struct No));
    if (novo)
    {
        novo->info = chave ;
        novo->esq = NULL ;
        novo->dir = NULL ;
    }else
        printf("\nerro ao alocar memoria\n") ;
    return novo ;
}
 
struct No *rotaciona_esq(struct No *raiz)
{
    struct No *right_child = raiz->dir ;
    raiz->dir = right_child->esq ;
    right_child->esq = raiz ;
    
    // atualiza altura do noh
    raiz->ht = altura(raiz);
    right_child->ht = altura(right_child) ;
 
    // retorna novo noh apos a rotacao
    return right_child ;
}

struct No *rotaciona_dir(struct No *raiz)
{
    struct No *left_child = raiz->esq ;
    raiz->esq = left_child->dir ;
    left_child->dir = raiz ;
 
    // atualiza altura do noh
    raiz->ht = altura(raiz) ;
    left_child->ht = altura(left_child) ;
    
    // retorna novo noh apos a rotacao
    return left_child ;
}
 
int fator_balanceamento(struct No* raiz)
{
    int lh, rh ;
    if (raiz == NULL)
        return 0 ;
    if (raiz->esq == NULL)
        lh = 0 ;
    else
        lh = 1 + raiz->esq->ht ;
    if (raiz->dir == NULL)
        rh = 0 ;
    else
        rh = 1 + raiz->dir->ht ;
    return lh - rh ;
}
 
int altura(struct No* raiz)
{
    int lh, rh ;
    if (raiz == NULL)
    {
        return 0 ;
    }
    if (raiz->esq == NULL)
        lh = 0 ;
    else
        lh = 1 + raiz->esq->ht ;
    if (raiz->dir == NULL)
        rh = 0 ;
    else
        rh = 1 + raiz->dir->ht ;
 
    if (lh > rh)
      return (lh) ;
    return (rh) ;
}

/*  //Função para calcular a altura de uma árvore binária
int height(struct node* raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = height(raiz->left);
        int dir = height(raiz->right);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}
*/
 
struct No *insereAVL(struct No *raiz, int chave)
{
    if (raiz == NULL)
    {
        struct No *novoNo = inicializa(chave) ;
        if (novoNo == NULL)
        {
            return NULL ;
        }
        raiz = novoNo ;
    }
    else if (chave > raiz->info)
    {
        // insere noh na direita
        raiz->dir = insereAVL(raiz->dir, chave) ;
        // se AVL estiver desbalanceada, havera rotacao
        if (fator_balanceamento(raiz) == -2)
        {
            if (chave > raiz->dir->info)
            {
                raiz = rotaciona_esq(raiz) ;
            }
            else
            {
                raiz->dir = rotaciona_dir(raiz->dir) ;
                raiz = rotaciona_esq(raiz) ;
            }
        }
    }
    else
    {
        // insere noh na esquerda
        raiz->esq = insereAVL(raiz->esq, chave) ;
        // se AVL estiver desbalanceada, havera rotacao
        if (fator_balanceamento(raiz) == 2)
        {
            if (chave < raiz->esq->info)
            {
                raiz = rotaciona_dir(raiz) ;
            }
            else
            {
                raiz->esq = rotaciona_esq(raiz->esq) ;
                raiz = rotaciona_dir(raiz) ;
            }
        }
    }
    //atualiza altura do noh
    raiz->ht = altura(raiz) ;
    return raiz ;
}

struct No *removeNo(struct No *raiz, int chave)
{
    struct No *temp = NULL ;
 
    if (raiz == NULL)
    {
        return NULL ;
    } 
 
    if (chave > raiz->info)
    {
        raiz->dir = removeNo(raiz->dir, chave) ;
        if (fator_balanceamento(raiz) == 2)
        {
            if (fator_balanceamento(raiz->esq) >= 0)
            {
                raiz = rotaciona_dir(raiz) ;
            }
            else
            {
                raiz->esq = rotaciona_esq(raiz->esq) ;
                raiz = rotaciona_dir(raiz) ;
            }
        }
    }
    else if (chave < raiz->info)
    {
        raiz->esq = removeNo(raiz->esq, chave) ;
        if (fator_balanceamento(raiz) == -2)
        {
            if (fator_balanceamento(raiz->dir) <= 0)
            {
                raiz = rotaciona_esq(raiz) ; 
            }
            else
            {
                raiz->dir = rotaciona_dir(raiz->dir) ;
                raiz = rotaciona_esq(raiz) ;
            }
        }
    }
    else
    {
        if (raiz->dir != NULL)
        { 
            temp = raiz->dir ;
            while (temp->esq != NULL)
                temp = temp->esq ;
 
            raiz->info = temp->info ;
            raiz->dir = removeNo(raiz->dir, temp->info) ;
            if (fator_balanceamento(raiz) == 2)
            {
                if (fator_balanceamento(raiz->esq) >= 0)
                {
                    raiz = rotaciona_dir(raiz) ;
                }
                else
                {
                    raiz->esq = rotaciona_esq(raiz->esq) ;
                    raiz = rotaciona_dir(raiz) ;
                }
            }
        }
        else
        {
            return (raiz->esq) ;
        }
    }
    raiz->ht = altura(raiz) ;
    return (raiz) ;
}

struct No* busca(struct No* raiz, int chave)
{
    if (raiz == NULL)
    {
        return NULL ;
    }
 
    if(raiz->info == chave)
    {
        return raiz ;
    }
 
    if(chave > raiz->info)
    {
        busca(raiz->dir, chave) ;
    }
    else
    {
        busca(raiz->esq, chave) ; 
    } 
}
 
void imprimir(struct No *aux) //pos-ordem
{
    if (aux!= NULL)
        printf("%d ", aux->info) ;
    if (aux->dir != NULL)
        imprimir(aux->dir) ;
    if (aux->esq != NULL)
        imprimir(aux->esq) ;
}

// ############################ Principal ###################################

int main()
{
    int chave, i ;
    struct No *resultado = NULL ;
 
    do{
        scanf("%d", &chave) ;
        if (chave == -1)
            break ;
        raiz = insereAVL(raiz, chave) ;
    }while (1) ;

    do{
        scanf("%d", &chave) ;
        if (chave == -1)
            break ;
        resultado = busca(raiz, chave) ;
        if (resultado == NULL)
        {
            raiz = insereAVL(raiz, chave) ;
        }else
            raiz = removeNo(raiz, chave) ;
    }while(1) ;
    scanf ("%d", &i) ;
    
    resultado = busca(raiz, i) ;
    printf ("%d,%d,%d\n", altura(raiz), altura(raiz->esq), altura(raiz->dir)) ;
    if (resultado)
    {
        printf ("%d,%d,%d\n", altura(resultado), altura(resultado->esq), altura(resultado->dir)) ;
        //printf ("Valor encontrado\n") ;
    }else
        printf ("Valor nao encontrado\n") ;
    imprimir(raiz) ;
    return 0 ;
}
