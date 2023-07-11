/* Programa: AP 11 - Grafo - BFS x DFS
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 07/07/2023 - 20:10 h
   Nota: 10/10
*/

//https://github.com/tavaresisobe/AED-I/blob/main/lab05.c
//https://github.com/tavaresisobe/AED-I/blob/main/lab06.c
//https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// ########################## TAD X.h ######################################

typedef struct no{
    int chave ;
    struct no *prox ;
}No;

typedef struct grafo{
    int V ;
    No *l_adj[MAX] ; // lista de adjacência
}tipoGrafo;

// ###################### Funcoes e Procedimentos do programa ##############

No *novoNo(int c) 
{
    No *no = (No *)malloc(sizeof(No)) ;
    if (no)
    {
        no->chave = c ;
        no->prox = NULL ;
    }else 
        printf ("Erro ao alocar memoria\n") ;
    return no ;
}

void criaGrafo(tipoGrafo *grafo, int V)
{
    grafo->V = V ;
    for (int i = 0; i < V; i++) 
    {
        grafo->l_adj[i] = NULL ; //inicializa lista
    }
}

void adicionaAresta(tipoGrafo *grafo, int u, int v)
{
    No *no = novoNo(v) ;
    No *temp = grafo->l_adj[u] ;
    No *aux = NULL ; //guarda predecessor do no

    while (temp != NULL && temp->chave < v) //busca posicao do novo vertice
    {
        aux = temp ;
        temp = temp->prox ;
    }

    if (aux == NULL) { //se a lista estiver vazia
        no->prox = grafo->l_adj[u] ;
        grafo->l_adj[u] = no ;
    }else{
        no->prox = aux->prox ;
        aux->prox = no ;
    }
}

// busca em largura
void BFS(tipoGrafo *grafo, int s, int *visitado)
{
    //fila:
    int fila[MAX] ;
    int primeiro = 0 ;
    int ultimo = 0 ;
    
    fila[ultimo++] = s ;
    visitado[s] = 1 ; //colore no

    while (primeiro != ultimo) 
    {
        int u = fila[primeiro++] ;
        printf("%d ", u) ; //imprime o no visitado
        No *temp = grafo->l_adj[u] ; // obtém sucesspres
        while (temp != NULL)
        {
            int v = temp->chave ;
            if (visitado[v] == 0) //se no estiver descolorido
            {
                fila[ultimo++] = v ;
                visitado[v] = 1 ; // marca o nó como visitado
            }
            temp = temp->prox ;
        }
    }
}

// busca em profundidade
void DFS(tipoGrafo *grafo, int s, int *visitado) 
{
    printf("%d ", s) ; //imprimindo o no visitado
    visitado[s] = 1 ; //colore no visitado
    No *temp = grafo->l_adj[s] ; //guarda sucessores do no atual
    while (temp != NULL)
    {
        int v = temp->chave ;
        if (visitado[v] == 0)
        {
            DFS(grafo, v, visitado) ;
        }
        temp = temp->prox ;
    }
}

void chamaBusca(tipoGrafo *grafo, int s, int x) 
{
    int visitado[MAX] ;
    for (int i = 0; i < grafo->V; i++) 
    {
        visitado[i] = 0 ; //inicializa vetor com zeros
    }
    if (x == 0) BFS(grafo, s, visitado) ;
    else DFS(grafo, s, visitado) ;
}

/*void imprimeLista(No *aux)
{
    No *temp = aux ;
    while (temp != NULL) 
    {
        printf("%d ", temp->chave) ;
        temp = temp->prox ;
    }
}

void imprimeGrafo(Grafo *grafo)
{
    for (int i = 0; i < grafo->V; i++)
    {
        printf("%d: ", i) ;
        imprimeLista(grafo->l_adj[i]) ;
        printf("\n") ;
    }
}*/

// ############################ Principal ###################################

int main() 
{
    tipoGrafo grafo ;
    int busca ;
    int V, M ; 
    scanf("%d", &busca) ; // no da busca
    scanf("%d", &V) ; // num total de nós
    scanf("%d", &M) ; // num de arestas   

    if (busca <= 100 && V <= 100 && M <= 200) //condiçaozinha do enunciado
    {
        criaGrafo(&grafo, V) ; // inicializa grafo com V nós
        for (int i = 0; i < M; i++) 
        {
            int u, v ;
            scanf("%d %d", &u, &v) ;
            adicionaAresta(&grafo, u, v) ; // adiciona aresta direcionada de u para v
        }
        chamaBusca(&grafo, busca, 0) ;
        printf("\n") ;

        chamaBusca(&grafo, busca, 1) ;
        printf("\n") ;
    }else
        printf("Os valores de entrada nao condizem com o enunciado\n") ;
    return 0 ;
}
