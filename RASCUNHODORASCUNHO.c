/* Programa: AP7 - Arvore AVL
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 18/05/2023 - 02:05h
*/
// ##################### Bibliotecas Externas ##############################

#include<stdio.h>
#include<stdlib.h>

//6 4 3 2 1 -1 4 5 -1 1
//16 14 20 12 11 19 18 15 17 13 -1 14 19 15 20 -1 18

// ########################## TAD X.h ######################################

struct node
{
    int data ;
    struct node* esq ;
    struct node* dir ;
    int ht ;
};
struct node* raiz = NULL;
 
// function prototyping
struct node* inicializa(int);
struct node* insereAVL(struct node*, int);
struct node* removeNo(struct node*, int);
struct node* busca(struct node*, int);
struct node* rotaciona_esq(struct node*);
struct node* rotaciona_dir(struct node*);
int fator_balanceamento(struct node*);
int altura(struct node*);
void imprimir(struct node*);

// ############################ Principal ###################################

int main()
{
    int chave, i ;
    struct node* result = NULL ;
 
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
        result = busca(raiz, chave) ;
        if (result == NULL)
        {
            raiz = insereAVL(raiz, chave) ;
        }else
            raiz = removeNo(raiz, chave) ;
    }while(1) ;
    scanf ("%d", &i) ;
    
    result = busca(raiz, i) ;
    printf ("%d,%d,%d\n", altura(raiz), altura(raiz->esq), altura(raiz->dir)) ;
    if (result)
    {
        printf ("%d,%d,%d\n", altura(result), altura(result->esq), altura(result->dir)) ;
        printf ("Valor encontrado\n") ;
    }else
        printf ("Valor nao encontrado\n") ;
    imprimir(raiz) ;
    return 0 ;
}

// ###################### Funcoes e Procedimentos do programa ##############
 
struct node* inicializa(int data)
{
    struct node* novo = (struct node*) malloc (sizeof(struct node));
    if (novo)
    {
        novo->data = data ;
        novo->esq = NULL ;
        novo->dir = NULL ;
    }else
        printf("\nERRO ao alocar nó em novoNo!\n") ;
    return novo ;
}
 
struct node* rotaciona_esq(struct node* raiz)
{
    struct node* right_child = raiz->dir ;
    raiz->dir = right_child->esq ;
    right_child->esq = raiz ;

    raiz->ht = altura(raiz);
    right_child->ht = altura(right_child) ;
 
    // return the new node after rotation
    return right_child ;
}

struct node* rotaciona_dir(struct node* raiz)
{
    struct node* left_child = raiz->esq ;
    raiz->esq = left_child->dir ;
    left_child->dir = raiz ;
 
    // atualiza altura do noh
    raiz->ht = altura(raiz) ;
    left_child->ht = altura(left_child) ;
 
    return left_child ;
}
 
int fator_balanceamento(struct node* raiz)
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
 
int altura(struct node* raiz)
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

    //Função para calcular a altura de uma árvore binária
/*
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
 
struct node* insereAVL(struct node* raiz, int data)
{
    if (raiz == NULL)
    {
        struct node* new_node = inicializa(data) ;
        if (new_node == NULL)
        {
            return NULL ;
        }
        raiz = new_node ;
    }
    else if (data > raiz->data)
    {
        raiz->dir = insereAVL(raiz->dir, data) ;
 

        if (fator_balanceamento(raiz) == -2)
        {
            if (data > raiz->dir->data)
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
        // insert the new node to the left
        raiz->esq = insereAVL(raiz->esq, data) ;
 
        // tree is unbalanced, then rotate it
        if (fator_balanceamento(raiz) == 2)
        {
            if (data < raiz->esq->data)
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
    //atualiza tam alt do noh
    raiz->ht = altura(raiz) ;
    return raiz ;
}
 
// deletes a node from the AVL tree
struct node * removeNo(struct node *raiz, int x)
{
    struct node * temp = NULL ;
 
    if (raiz == NULL)
    {
        return NULL ;
    } 
 
    if (x > raiz->data)
    {
        raiz->dir = removeNo(raiz->dir, x) ;
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
    else if (x < raiz->data)
    {
        raiz->esq = removeNo(raiz->esq, x) ;
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
 
            raiz->data = temp->data ;
            raiz->dir = removeNo(raiz->dir, temp->data) ;
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
 
// search a node in the AVL tree
struct node* busca(struct node* raiz, int chave)
{
  if (raiz == NULL)
    {
        return NULL ;
    }
 
    if(raiz->data == chave)
    {
        return raiz ;
    }
 
    if(chave > raiz->data)
    {
        busca(raiz->dir, chave) ;
    }
    else
    {
        busca(raiz->esq, chave) ; 
    } 
}
 
void imprimir(struct node* aux) //pos-ordem
{
  if (aux!= NULL)
        printf("%d ", aux->data) ;
    if (aux->dir != NULL)
        imprimir(aux->dir) ;
    if (aux->esq != NULL)
        imprimir(aux->esq) ;
}
