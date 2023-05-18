/* Programa: AP7 - Arvore AVL
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 2.0 - 18/05/2023 - :h
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>
 

 
typedef int TChave;
 
typedef struct {
    TChave Chave;
} TItem;
 
typedef struct SNo *TArvBin;
 
typedef struct SNo {
    TItem Item;
    TChave Fat_Balanceamento;
    TArvBin Esquerda, Direita;
} TNo;
 
typedef TArvBin TABB;
 
//Inicia uma árvore binária vazia
TArvBin TArvBin_Inicia()
{
     return NULL;
}
 
//Retorna um apontador para um nó contendo o item x e as subárvores Esq e Dir
TArvBin TArvBin_CriaNo(TItem x, TArvBin Esq, TArvBin Dir)
{
    TArvBin No;
 
    No = (TArvBin) malloc(sizeof(TNo));
    
    No->Item = x;
    No->Fat_Balanceamento = 0;
    No->Esquerda = Esq;
    No->Direita = Dir;
    
    return No;
}

//Retorna 1 se o nó for uma folha, ou 0 se não for.
int TArvBin_EhFolha(TArvBin No)
{
    return ((No == NULL) || ((No->Esquerda == NULL) && (No->Direita == NULL)));
}
 
TArvBin TArvBin_SubarvoreEsquerda(TNo *No) {
    return No->Esquerda;
}
 
TArvBin TArvBin_SubarvoreDireita(TNo *No) {
    return No->Direita;
}
 
//Insere o item x com chave X na árvore binária de busca e retorna true, caso ele não esteja
// na árvore; caso contrário, retorna false
int TABB_Insere(TABB *pNo, TItem x)
{
    if (*pNo == NULL) {
        *pNo = TArvBin_CriaNo(x, TArvBin_Inicia(), TArvBin_Inicia());
        return 1;
    }
    else if (x.Chave < (*pNo)->Item.Chave)
        return TABB_Insere(&(*pNo)->Esquerda, x);
    else if (x.Chave > (*pNo)->Item.Chave)
        return TABB_Insere(&(*pNo)->Direita, x);
    else
        return 0; // retorna 0 caso o item ja estiver na arvore
 
}
 
//Retorna a árvore binaria de busca contendo o item com chave x; caso não haja nenhum item
// com chave x na árvore, retorna uma árvore vazia
TABB TABB_Pesquisa(TABB No, TChave x)
{
    if (No == NULL)
        return NULL; // retorna NULL caso a chave nao seja encontrada
    else if (x < No->Item.Chave)
        return TABB_Pesquisa(No->Esquerda, x);
    else if (x > No->Item.Chave)
        return TABB_Pesquisa(No->Direita, x);
    else
        return No;
}
 
void TABB_Sucessor(TABB *q, TABB *r)
{
    if ((*r)->Esquerda != NULL)
        TABB_Sucessor(q, &(*r)->Esquerda);
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Direita;
    }
}
 
//Retira o item com chave X na árvore binária de busca e retorna true, caso ele esteja na
// árvore; caso contrário, retorna false
int TABB_Remove(TABB *p, TChave x)
{
    TABB q;
 
    if (*p == NULL)
        return 0; // retorna 0 caso o item nao esteja na arvore
    else if (x < (*p)->Item.Chave)
        return TABB_Remove(&(*p)->Esquerda, x);
    else if (x > (*p)->Item.Chave)
        return TABB_Remove(&(*p)->Direita, x);
    else {
        q = *p;
        if (q->Esquerda == NULL)
            *p = q->Direita;
        else if (q->Direita == NULL)
            *p = q->Esquerda;
        else // possui dois filhos
            TABB_Sucessor(&q, &q->Direita); // equivalente a Predecessor(&q, &q->Esq);
        free(q);
        return 1;
    }
}

//Retorna o maior entre os dois valores
int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
 
//Retorna a Altura do Nó
int TArv_Bin_Altura(TABB No)
{
    if(No == NULL)
        return 0;
    else
        return 1 + max(TArv_Bin_Altura(No->Esquerda), TArv_Bin_Altura(No->Direita)); //pega o maior das alturas(direita ou esquerda) do nó
}

//Procedimento que faz o cálculo do fator de balanceamento de cada Nó
void Arv_AVL_AlteraFB(TABB *p) {
    if (*p != NULL) {
        Arv_AVL_AlteraFB(&(*p)->Esquerda);
        Arv_AVL_AlteraFB(&(*p)->Direita);
        (*p)->Fat_Balanceamento = TArv_Bin_Altura((*p)->Esquerda) - TArv_Bin_Altura((*p)->Direita);
    }
}

//RotaçãoLL
TArvBin Arv_AVL_RotacionaDireitaLL(TABB *pA) {
    TABB pB = (*pA)->Esquerda;
    (*pA)->Esquerda = pB->Direita;
    pB->Direita = *pA;
    *pA = pB;

    return *pA;
}

//RotaçãoRR
TArvBin Arv_AVL_RotacionaEsquerdaRR(TABB *pA) {
    TABB pB = (*pA)->Direita; 
    (*pA)->Direita = pB->Esquerda; 
    pB->Esquerda = *pA;
    *pA = pB;

    return *pA;
}
 
//RotaçãoLR
TArvBin Arv_AVL_RotacionaDuplaDireitaLR(TABB *pA) {
    TABB pB = (*pA)->Esquerda;
    TABB pC = pB->Direita;
    pB->Direita = pC->Esquerda;
    pC->Esquerda = pB;
    (*pA)->Esquerda = pC->Direita;
    pC->Direita = *pA;
    *pA = pC;

    return *pA;
}
 
//RotaçãoRL
TArvBin Arv_AVL_RotacionaDuplaEsquerdaRL(TABB *pA) {
    TABB pB = (*pA)->Direita;
    TABB pC = pB->Esquerda;
    pB->Esquerda = pC->Direita;
    pC->Direita = pB;
    (*pA)->Direita = pC->Esquerda;
    pC->Esquerda = *pA;
    *pA = pC;

    return *pA;
}

//Procedimento que Faz o Balanceamento da Árvore
//Possui diversas condições, e cada uma leva à uma rotação específica de cada caso
void Arv_AVL_BalanceiaFB(TABB *p, TABB *raiz) {
    if (*p != NULL) {
        Arv_AVL_BalanceiaFB(&(*p)->Esquerda, raiz); 
        Arv_AVL_BalanceiaFB(&(*p)->Direita, raiz);
        if ((*p)->Fat_Balanceamento > 1) {
            if ((*p)->Esquerda->Fat_Balanceamento >= 0){
                *p = Arv_AVL_RotacionaDireitaLL(&(*p));
                Arv_AVL_AlteraFB(&(*raiz)); //após a rotação recalculamos o FB
            }
            else{
                *p = Arv_AVL_RotacionaDuplaDireitaLR(&(*p)); 
                Arv_AVL_AlteraFB(&(*raiz)); //após a rotação recalculamos o FB
            }
        }
        else if ((*p)->Fat_Balanceamento < -1) {
            if ((*p)->Direita->Fat_Balanceamento <= 0){
                *p = Arv_AVL_RotacionaEsquerdaRR(&(*p));
                Arv_AVL_AlteraFB(&(*raiz)); //após a rotação recalculamos o FB
            }
            else{
                *p = Arv_AVL_RotacionaDuplaEsquerdaRL(&(*p));
                Arv_AVL_AlteraFB(&(*raiz)); //após a rotação recalculamos o FB
            }
        }
    }
}

//Procedimento que exibe a Árvore
void Exibir_TArvore(TABB No)
{
    if(No != NULL)
    {
        printf("(");
        printf("C %d", No->Item.Chave);
        Exibir_TArvore(No->Esquerda);
        Exibir_TArvore(No->Direita);
        printf(")");
    }
    else{
        printf("(");
        printf(")");
    }
}

//Procedimento que libera o espaço de memória que foi alocado por cada nó da árvore 
void TArvBin_Libera(TArvBin No) {
    if (No != NULL) {
    TArvBin_Libera(No->Esquerda);
    TArvBin_Libera(No->Direita);
    free(No);
    }
}
 
//TAD Árvore Binária de Busca.
 
int main(){
 
    TABB Arvore_AVL;
    TItem num_insere;
 
    Arvore_AVL = (TABB)malloc(sizeof(TArvBin));
    
    Arvore_AVL = TArvBin_Inicia(); //inicializando a árvore
 
    scanf("%d", &num_insere.Chave);
    while(num_insere.Chave != -1){
        TABB_Insere(&Arvore_AVL, num_insere); //inserindo o item na árvore
        Arv_AVL_AlteraFB(&Arvore_AVL); //recalculando o fator de balanceamento
        Arv_AVL_BalanceiaFB(&Arvore_AVL, &Arvore_AVL); //balanceando a árvore
        scanf("%d", &num_insere.Chave);
    }
 
    printf("%d, %d, %d\n", TArv_Bin_Altura(Arvore_AVL)-1, TArv_Bin_Altura(Arvore_AVL->Esquerda), TArv_Bin_Altura(Arvore_AVL->Direita));

    TItem chave_pesquisada;
 
    scanf("%d", &chave_pesquisada.Chave);
    while(chave_pesquisada.Chave != -1){
 
        if(TABB_Pesquisa(Arvore_AVL, chave_pesquisada.Chave) != NULL){
            TABB_Remove(&Arvore_AVL, chave_pesquisada.Chave);
            Arv_AVL_AlteraFB(&Arvore_AVL); //recalculando o fator de balanceamento
            Arv_AVL_BalanceiaFB(&Arvore_AVL, &Arvore_AVL); //balanceando a árvore
        }
        else{
            TABB_Insere(&Arvore_AVL, chave_pesquisada); //inserindo a chave que não foi encontrada
            Arv_AVL_AlteraFB(&Arvore_AVL); //recalculando o fator de balanceamento
            Arv_AVL_BalanceiaFB(&Arvore_AVL, &Arvore_AVL); //balanceando a árvore
        }
        scanf("%d", &chave_pesquisada.Chave);
    }
    
    //printf("%d %d %d\n", TArv_Bin_Altura(Arvore_AVL), TArv_Bin_Altura(Arvore_AVL->Esquerda), TArv_Bin_Altura(Arvore_AVL->Direita));
 
    TChave Valor_Buscado;
    scanf("%d", &Valor_Buscado);
    
    TABB noPesquisado = TArvBin_Inicia(); //inicializando o nó
    noPesquisado = TABB_Pesquisa(Arvore_AVL, Valor_Buscado); //pesquisando o nó que contém o valor buscado
 
    if(noPesquisado != NULL)
        printf("%d, %d, %d\n", TArv_Bin_Altura(noPesquisado)-1, TArv_Bin_Altura(noPesquisado->Esquerda), TArv_Bin_Altura(noPesquisado->Direita));
    else{
        printf("Valor nao encontrado");
    }
 
    TArvBin_Libera(Arvore_AVL);
    free(noPesquisado);

    return 0;
}