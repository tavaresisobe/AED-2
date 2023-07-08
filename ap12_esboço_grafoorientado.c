typedef struct no{
    int chave ;
    int dest ; // destino do nó
    int peso ; // peso da aresta
    struct no *prox ;
}No;

typedef struct grafo{
    int V ;
    No *l_adj[MAX] ; // lista de adjacência
}tipoGrafo;

No *novoNo(int weight, int dest, int chave) 
{
    No *novo = (No*) malloc(sizeof(No));
    if (novo)
    {
        novo->peso = weight;
        novo->dest = dest;
        novo->chave = chave;
    }else 
        printf ("Erro ao alocar memoria\n") ;
    return novo ;
}

void adicionaArestavoid(tipoGrafo *grafo, int src, int dest, int weight, int chave)
{
    // Cria um novo nó com o conteúdo, o destino e o peso dados
    No *novo = novoNo(weight, dest, chave)
 
    // Insere o novo nó na lista de adjacência do vértice de origem
    novo->prox = g->l_adj[src];
    g->l_adj[src] = novo;
}

Escreva um programa em C, que a entrada para cada teste se inicia informando o nó onde será iniciada a busca do caminho mínimo. O nó inicial tem valor V (0 ≤ V ≤ 100). O próximo valor a ser informado é o da restrição, representado por R (-1024 < R < 1024). Depois deve-se informar o número total de nós N (0 ≤ N ≤ 100) e o número de arestas M (1 ≤ M ≤ 1024). Nas próximas M linhas devem ser fornecidas as arestas que serão criadas juntamente com o peso delas, como, por exemplo, 2 7 -3 (possui uma aresta 2 -> 7 com peso -3). Nota-se que os pesos P das arestas estão no intervalo -1024 < P < 1024. Os nós são representados por valores numéricos que variam entre 0 e 100. Considerar a ordem crescente quando for inserido um novo nó na lista de adjacência. Por exemplo, considere que o nó/vértice 9 aponta (tem aresta de ligação) para 5, 6 e 8. Caso insira uma nova aresta 9 -> 3, o no/vértice 3 deve ser inserido antes do nó/vértice 5 na lista de adjacência. Caso insira a aresta 9- > 4, então o no/vértice 4 deve ser inserido antes do nó/vértice 5 e depois do no/vértice 3 na lista de adjacência.  A saída do programa é exibida em uma linha que mostra o caminho mínimo com restrição do grafo com base em uma aresta inicial V. Utilize o algoritmo de Bellman-Ford.
exemplo de input:
7
3
8 12
1 0 -3
2 0 3
3 0 -2
4 1 2
6 3 -1
5 2 1
7 4 -4
7 6 3
7 5 6
1 2 4
4 2 -3
2 5 1
output:
-5 -2 -7 2 -4 -6 3 0

    #include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct {
    int numNodes;
    int numEdges;
    Edge* edges;
} Graph;

Graph createGraph(int numNodes, int numEdges) {
    Graph graph;
    graph.numNodes = numNodes;
    graph.numEdges = numEdges;
    graph.edges = malloc(numEdges * sizeof(Edge));
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    // Adiciona uma aresta ao grafo
    Edge edge;
    edge.src = src;
    edge.dest = dest;
    edge.weight = weight;
    graph->edges[src] = edge;
}

void bellmanFord(Graph graph, int src, int restriction) {
    int* dist = malloc(graph.numNodes * sizeof(int));
    
    // Inicializa as distâncias como infinito
    for (int i = 0; i < graph.numNodes; i++) {
        dist[i] = INT_MAX;
    }
    
    // A distância do nó inicial para ele mesmo é sempre 0
    dist[src] = 0;
    
    // Relaxa as arestas repetidamente para encontrar o caminho mínimo
    for (int count = 0; count < graph.numNodes - 1; count++) {
        for (int i = 0; i < graph.numEdges; i++) {
            int u = graph.edges[i].src;
            int v = graph.edges[i].dest;
            int weight = graph.edges[i].weight;
            
            if (dist[u] != INT_MAX && dist[u] + weight <= dist[v] && weight >= restriction) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Verifica se há ciclos de peso negativo
    for (int i = 0; i < graph.numEdges; i++) {
        int u = graph.edges[i].src;
        int v = graph.edges[i].dest;
        int weight = graph.edges[i].weight;
        
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Há ciclo de peso negativo no grafo!\n");
            free(dist);
            return;
        }
    }
    
    // Imprime as distâncias mínimas encontradas
    for (int i = 0; i < graph.numNodes; i++) {
        printf("Distância mínima de %d a %d: %d\n", src, i, dist[i]);
    }
    
    free(dist);
}

int main() {
    int V, R, N, M;
    printf("Digite o nó inicial: ");
    scanf("%d", &V);
    printf("Digite a restrição: ");
    scanf("%d", &R);
    printf("Digite o número total de nós: ");
    scanf("%d", &N);
    printf("Digite o número de arestas: ");
    scanf("%d", &M);
    
    Graph graph = createGraph(N, M);
    
    for (int i = 0; i < M; i++) {
        int src, dest, weight;
        printf("Digite os nós e o peso da aresta %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        
        addEdge(&graph, src, dest, weight);
    }
    
    bellmanFord(graph, V, R);
    
    return 0;
    }
