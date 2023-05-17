/*
   Programa: ABB
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

#include <stdio.h> #include <stdlib.h> typedef struct no{ int valor; struct no *esquerdo, *direito; short altura; }No; /* Função que cria um novo nó x -> valor a ser inserido no nó Retorna: o endereço do nó criado */ No* novoNo(int x){ No *novo = malloc(sizeof(No)); if(novo){ novo->valor = x; novo->esquerdo = NULL; novo->direito = NULL; novo->altura = 0; } else printf("\nERRO ao alocar nó em novoNo!\n"); return novo; } /* Retorna o maior dentre dois valores a, b -> altura de dois nós da árvore */ short maior(short a, short b){ return (a > b)? a: b; } // Retorna a altura de um nó ou -1 caso ele seja null short alturaDoNo(No *no){ if(no == NULL) return -1; else return no->altura; } // Calcula e retorna o fator de balanceamento de um nó short fatorDeBalanceamento(No *no){ if(no) return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito)); else return 0; } // --------- ROTAÇÕES --------------------------- // função para a rotação à esquerda No* rotacaoEsquerda(No *r){ No *y, *f; y = r->direito; f = y->esquerdo; y->esquerdo = r; r->direito = f; r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1; y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1; return y; } // função para a rotação à direita No* rotacaoDireita(No *r){ No *y, *f; y = r->esquerdo; f = y->direito; y->direito = r; r->esquerdo = f; r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1; y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1; return y; } No* rotacaoEsquerdaDireita(No *r){ r->esquerdo = rotacaoEsquerda(r->esquerdo); return rotacaoDireita(r); } No* rotacaoDireitaEsquerda(No *r){ r->direito = rotacaoDireita(r->direito); return rotacaoEsquerda(r); } /* Função para realizar o balanceamento da árvore após uma inserção ou remoção Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento */ No* balancear(No *raiz){ short fb = fatorDeBalanceamento(raiz); // Rotação à esquerda if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0) raiz = rotacaoEsquerda(raiz); // Rotação à direita else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0) raiz = rotacaoDireita(raiz); // Rotação dupla à esquerda else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0) raiz = rotacaoEsquerdaDireita(raiz); // Rotação dupla à direita else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0) raiz = rotacaoDireitaEsquerda(raiz); return raiz; } /* Insere um novo nó na árvore raiz -> raiz da árvore x -> valor a ser inserido Retorno: endereço do novo nó ou nova raiz após o balanceamento */ No* inserir(No *raiz, int x){ if(raiz == NULL) // árvore vazia return novoNo(x); else{ // inserção será à esquerda ou à direita if(x < raiz->valor) raiz->esquerdo = inserir(raiz->esquerdo, x); else if(x > raiz->valor) raiz->direito = inserir(raiz->direito, x); else printf("\nInsercao nao realizada!\nO elemento %d a existe!\n", x); } // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1; // verifica a necessidade de rebalancear a árvore raiz = balancear(raiz); return raiz; } /* Função para remover um nó da Árvore binária balanceada Pode ser necessário rebalancear a árvore e a raiz pode ser alterada por isso precisamos retornar a raiz */ No* remover(No *raiz, int chave) { if(raiz == NULL){ printf("Valor nao encontrado!\n"); return NULL; } else { // procura o nó a remover if(raiz->valor == chave) { // remove nós folhas (nós sem filhos) if(raiz->esquerdo == NULL && raiz->direito == NULL) { free(raiz); printf("Elemento folha removido: %d !\n", chave); return NULL; } else{ // remover nós que possuem 2 filhos if(raiz->esquerdo != NULL && raiz->direito != NULL){ No *aux = raiz->esquerdo; while(aux->direito != NULL) aux = aux->direito; raiz->valor = aux->valor; aux->valor = chave; printf("Elemento trocado: %d !\n", chave); raiz->esquerdo = remover(raiz->esquerdo, chave); return raiz; } else{ // remover nós que possuem apenas 1 filho No *aux; if(raiz->esquerdo != NULL) aux = raiz->esquerdo; else aux = raiz->direito; free(raiz); printf("Elemento com 1 filho removido: %d !\n", chave); return aux; } } } else { if(chave < raiz->valor) raiz->esquerdo = remover(raiz->esquerdo, chave); else raiz->direito = remover(raiz->direito, chave); } // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1; // verifica a necessidade de rebalancear a árvore raiz = balancear(raiz); return raiz; } } void imprimir(No *raiz, int nivel){ int i; if(raiz){ imprimir(raiz->direito, nivel + 1); printf("\n\n"); for(i = 0; i < nivel; i++) printf("\t"); printf("%d", raiz->valor); imprimir(raiz->esquerdo, nivel + 1); } } int main(){ int opcao, valor; No *raiz = NULL; do{ printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n"); scanf("%d", &opcao); switch(opcao){ case 0: printf("Saindo!!!"); break; case 1: printf("\tDigite o valor a ser inserido: "); scanf("%d", &valor); raiz = inserir(raiz, valor); break; case 2: printf("\tDigite o valor a ser removido: "); scanf("%d", &valor); raiz = remover(raiz, valor); break; case 3: imprimir(raiz, 1); break; default: printf("\nOcao invalida!!!\n"); } }while(opcao != 0); return 0; }
