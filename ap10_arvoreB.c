/* Programa: AP 10 -  Arvore B
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 16/06/2023 - 23:25h
   Teste: 3/10
*/
 
// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ########################## TAD X.h ######################################

struct NoABB_B
{
    int *info ; // Vetor de chaves
    int t ; // Grau mínimo (define a faixa de número de chaves)
    struct NoABB_B **C ; // Vetor de ponteiros para os filhos
    int n ; // Número atual de chaves
    bool folha ; // Verdadeiro se o nó é folha, falso caso contrário
};
 
// ###################### Funcoes e Procedimentos do programa ##############

struct NoABB_B* NovoNo(int t, bool folha)
{
    struct NoABB_B* novo = (struct NoABB_B*)malloc(sizeof(struct NoABB_B));
    if (novo)
    {
        novo->t = t ;
        novo->folha = folha ;
        novo->info = (int*)malloc(sizeof(int) * ((2*t)-1)) ;
        novo->C = (struct NoABB_B**)malloc(sizeof(struct NoABB_B*) * (2*t)) ;
        novo->n = 0 ;
    }else printf ("Erro ao alocar memoria\n") ;
    
    return novo ;
}
 
// Fnção para buscar uma chave em uma subárvore enraizada em um nó
struct NoABB_B* Busca(struct NoABB_B* Aux, int k)
{
    int i = 0 ;
    // Encontra a primeira chave maior ou igual a k
    while (i < Aux->n && k > Aux->info[i])
    {
        i++ ;
    }
    // Se a chave for encontrada no nó, retorna o nó
    if (i < Aux->n && k == Aux->info[i])
    {
        return Aux ;
    }
    // Se o nó é folha, a chave não está na árvore
    if (Aux->folha)
    {
        return NULL;
    }
    // Caso contrário, busca no filho apropriado
    return Busca(Aux->C[i], k) ;
}
 
// Função auxiliar para inserir uma nova chave em um nó que não está cheio
void insereVazio(struct NoABB_B* Aux, int k)
{
    int i = Aux->n - 1 ;
    // Se o nó é folha, encontra a posição da nova chave e move as outras chaves para frente
    if (Aux->folha) 
    {
        while (i >= 0 && k < Aux->info[i])
        {
            Aux->info[i+1] = Aux->info[i] ;
            i-- ;
        }
        Aux->info[i+1] = k ;
        Aux->n++ ;
    }
    else{
        // Se o nó não é folha, encontra o filho que vai receber a nova chave
        while (i >= 0 && k < Aux->info[i])
        {
            i-- ;
        }
        i++ ;
        // Se o filho está cheio, divide ele e muda uma chave para o nó atual
        if (Aux->C[i]->n == 2*Aux->t - 1)
        {
            divideFilho(Aux, i) ;
            // Decide qual dos dois filhos vai receber a nova chave
            if (k > Aux->info[i])
            {
                i++;
            }
        }
        // Insere a chave no filho escolhido
        insereVazio(Aux->C[i], k) ;
    }
}
 
// Função auxiliar para dividir um filho y do nó x que está cheio
void divideFilho(struct NoABB_B* x, int i)
{
    struct NoABB_B* y = x->C[i] ; // O filho a ser dividido
    struct NoABB_B* z = NovoNo(y->t, y->folha) ; // O novo filho que vai armazenar as últimas t-1 chaves de y
    z->n = y->t - 1 ;
    
    // Copia as últmas t-1 chaves de y para z
    for (int j = 0 ; j < y->t-1 ; j++)
    {
        z->info[j] = y->info[j + y->t] ;
    }
    // Copia os últimos t filhos de y para z, se y não for folha
    if (!y->folha)
    {
        for (int j = 0 ; j < y->t ; j++)
        {
            z->C[j] = y->C[j + y->t] ;
        }
    }
    // Reduz o número de chaves em y
    y->n = y->t - 1 ;
    // Cria espaço para um novo filho em x
    for (int j = x->n ; j >= i + 1; j--)
    {
        x->C[j+1] = x->C[j] ;
    }
    // Conecta z como filho de x
    x->C[i+1] = z ;
    // Move uma chave de y para x
    for (int j = x->n - 1 ; j >= i; j--)
    {
        x->info[j+1] = x->info[j] ;
    }
    x->info[i] = y->info[y->t - 1] ;
    // Incrementa o número de chaves em x
    x->n++ ;
}

// Função para inserir uma nova chave na B-tree
void Insere(struct NoABB_B** Aux, int k, int t)
{
    struct NoABB_B* r = *Aux ;
    // Se a raiz está cheia, cresce a árvore em altura
    if (r->n == 2*t - 1)
    {
        struct NoABB_B* s = NovoNo(t, false); // Nova raiz
        s->C[0] = r ; // Faz a antiga raiz ser filha da nova
        divideFilho(s, 0) ; // Divide a antiga raiz e move uma chave para a nova
        int i = 0 ;
        // Decide qual dos dois filhos vai receber a nova chave
        if (k > s->info[0])
        {
            i++ ;
        }
        insereVazio(s->C[i], k) ; // Insere a chave no filho escolhido
        *Aux = s ; // Muda a raiz da árvore
    }
    else{
        // Se a raiz não está cheia, insere normalmente
        insereVazio(r, k) ;
    }
}
 
// Função para buscar uma chave k na B-tree e imprimir a quantidade de elementos da página deste número e todos os elementos do mesmo vetor
void buscaPagina(struct NoABB_B* Aux, int k) 
{
    int i = 0 ;
    // Encontrar o índice da primeira chave maior ou igual a k
    while (i < Aux->n && k > Aux->info[i])
    {
        i++ ;
    }
    // Se a chave for encontrada no nó x, imprimir a quantidade de elementos da página deste número e todos os elementos de x separados por espaços
    if (i < Aux->n && k == Aux->info[i])
    {
        printf("%d\n", (Aux->n)) ; // Imprimir a quantidade de elementos da página deste número
        for (int j = 0 ; j < Aux->n; j++)
        {
            printf("%d ", Aux->info[j]) ; // Imprimir todos os elementos de x
        }
        printf("\n") ;
    }
    // Se o nó x for folha, a chave não está na árvore, retornar
    else if (Aux->folha)
    {
        printf ("Valor nao encontrado\n") ;
        return ;
    }
    // Senão, buscar a chave no filho apropriado de x
    else {
        buscaPagina(Aux->C[i], k);
    }
}

// Função para imprimir as chaves em uma subárvore enraizada em um nó
void imprimeEmOrdem(struct NoABB_B* Aux)
{
    int i ;
    for (i = 0 ; i < Aux->n ; i++)
    {
        if (!Aux->folha)
        {
            imprimeEmOrdem(Aux->C[i]) ;
        }
        printf("%d ", Aux->info[i]) ;
    }
    if (!Aux->folha)
    {
        imprimeEmOrdem(Aux->C[i]) ;
    }
    printf ("\n") ;
}
 
void imprimeTamRaiz(struct NoABB_B* Aux)
{
    if (Aux == NULL)
        printf("Raiz Nula\n") ;
    else
        printf("%d\n", Aux->n) ;
}
 
void imprimeRaiz(struct NoABB_B* Aux) 
{
    if (Aux == NULL)
    {
        printf("A árvore está vazia.\n") ;
    }else
    {
        printf("%d\n", Aux->n); // Imprime o número de chaves na raiz
        /*for (int i = 0; i < root->n; i++) {
            printf("%d ", root->keys[i]); // Imprime os elementos da raiz
        }
        printf("\n");*/
    }
}

int main ()
{
    int M ;
    scanf ("%d", &M) ;
    M ++ ;
    struct NoABB_B* raiz = NovoNo(M, true) ; // Cria uma B-tree de grau mínimo
    int x ;
    scanf("%d", &x);
    while (x != -1)
    {
        if (x == -1) break ; //cond de parada a mais, pq o programa continuava pegando o -1
        Insere(&raiz, x, M);
        scanf ("%d", &x);
    }
    imprimeRaiz(raiz) ;
    int y ;
    scanf ("%d", &y) ;
    buscaPagina(raiz, y) ;
    
    return 0 ;
} 
