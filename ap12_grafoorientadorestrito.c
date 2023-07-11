/* Programa: AP 12 - Caminho Mínimo em Grafo com Restrição
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 09/07/2023 - 17:14h
*/
 
// ##################### Bibliotecas Externas ##############################
 
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
 
// ########################## TAD X.h ######################################
 
typedef struct no{
    int destino;
    int peso;
    struct no *prox;
}No;
 
typedef struct grafo{
    int V;
    No *l_adj[MAX]; // lista de adjacência
}tipoGrafo;
 
// ###################### Funcoes e Procedimentos do programa ##############
 
void inicializarGrafo(tipoGrafo *grafo) //inicializando o grafo
{
    grafo->V = 0 ;
    for (int i = 0; i < MAX; i++)
    {
        grafo->l_adj[i] = NULL ;
    }
}
 
void adicionaAresta(tipoGrafo *grafo, int origem, int destino, int peso) //adiciona nova aresta no grafo
{
    No *novoNo = (No*)malloc(sizeof(No)) ;
    if (novoNo)
    {
        novoNo->destino = destino ;
        novoNo->peso = peso ;
        novoNo->prox = grafo->l_adj[origem] ;
        grafo->l_adj[origem] = novoNo ;
    }else 
        printf("Erro ao alocar memoria\n") ;
}
 
void inicializarFonte(int inicio, int n, int *dist, int *pred) //funcao para inicializar fonte da origem do caminho
{
    for (int i = 0; i < n; i++) 
    {
        dist[i] = MAX ; //infinito
        pred[i] = -1 ;
    }
    dist[inicio] = 0 ; //de inicio a distância do noh eh zero
}
 
void relaxar(int origem, int destino, int peso, int *dist, int *pred) //relaxa o antigo caminho
{
    if (dist[origem] != MAX && dist[destino] > dist[origem] + peso)
    {
        dist[destino] = dist[origem] + peso ;
        pred[destino] = origem ;
    }
}
 
//BellMan-Ford:
void bellmanFordRestrito(tipoGrafo *grafo, int inicio, int restricao, int n)
{
    int *dist = (int*)malloc(n * sizeof(int)) ; // distância
    int *pred = (int*)malloc(n * sizeof(int)) ; // predecessores
    inicializarFonte(inicio, n, dist, pred) ;
    for (int k = 0; k < n - 1; k++)
    {
        for (int u = 0; u < n; u++)
        {
            No *atual = grafo->l_adj[u] ;
            while (atual != NULL)
            {
                int v = atual->destino ;
                int w = atual->peso ;
                if (w <= restricao)
                {
                    relaxar(u, v, w, dist, pred) ;
                }
                atual = atual->prox ;
            }
        }
    }
    imprimirDistancia(dist, n) ;
 
    free(dist) ;
    free(pred) ;
}
 
void imprimirDistancia(int dist[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", dist[i]) ;
    }
}
 
// ############################ Principal ###################################
 
int main()
{
    tipoGrafo grafo ; 
    inicializarGrafo(&grafo) ;
    
    int inicio, R, N, M ;
    scanf("%d", &inicio) ;
    scanf("%d", &R) ;
    scanf("%d %d", &N, &M) ;
    for (int i = 0; i < M; i++)
    {
        int u, v, peso ;
        scanf("%d %d %d", &u, &v, &peso) ;
        adicionaAresta(&grafo, u, v, peso) ;
    }
    bellmanFordRestrito(&grafo, inicio, R, N) ;
 
    return 0;
}
