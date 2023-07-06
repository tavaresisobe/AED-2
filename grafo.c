#include <stdio.h>
#include <stdlib.h>
//http://www.univasf.edu.br/~marcelo.linder/arquivos_aed2/aulas/aula25.pdf

// Define uma estrutura para representar um nó da lista de adjacência
typedef struct node {
    int data; // O valor do nó/vértice
    struct node* next; // O ponteiro para o próximo nó da lista
} Node;

// Define uma estrutura para representar um grafo
typedef struct graph {
    int V; // O número total de nós/vértices
    Node** adj; // O vetor de ponteiros para as listas de adjacência
} Graph;

// Cria um novo nó da lista de adjacência com um dado valor e retorna o seu ponteiro
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node)); // Aloca memória para o nó
    newNode->data = data; // Atribui o valor ao nó
    newNode->next = NULL; // Inicializa o ponteiro para o próximo nó como NULL
    return newNode; // Retorna o ponteiro para o nó criado
}

// Cria um novo grafo com um dado número de nós/vértices e retorna o seu ponteiro
Graph* createGraph(int V) {
    Graph* newGraph = (Graph*) malloc(sizeof(Graph)); // Aloca memória para o grafo
    newGraph->V = V; // Atribui o número de nós/vértices ao grafo
    newGraph->adj = (Node**) malloc(V * sizeof(Node*)); // Aloca memória para o vetor de ponteiros para as listas de adjacência
    for (int i = 0; i < V; i++) { // Para cada nó/vértice do grafo
        newGraph->adj[i] = NULL; // Inicializa a lista de adjacência como vazia
    }
    return newGraph; // Retorna o ponteiro para o grafo criado
}

// Adiciona uma aresta orientada de um nó/vértice u para um nó/vértice v em um grafo g, mantendo a ordem crescente da lista de adjacência
void addEdge(Graph* g, int u, int v) {
    Node* newNode = createNode(v); // Cria um novo nó com o valor de v
    if (g->adj[u] == NULL || g->adj[u]->data > v) { // Se a lista de adjacência de u está vazia ou se o primeiro nó tem um valor maior que v
        newNode->next = g->adj[u]; // Insere o novo nó no início da lista
        g->adj[u] = newNode;
    } else { // Senão, procura a posição correta para inserir o novo nó na lista, mantendo a ordem crescente
        Node* curr = g->adj[u]; // Cria um ponteiro auxiliar para percorrer a lista
        while (curr->next != NULL && curr->next->data < v) { // Enquanto não chegar ao final da lista e enquanto o próximo nó tiver um valor menor que v
            curr = curr->next; // Avança o ponteiro auxiliar
        }
        newNode->next = curr->next; // Insere o novo nó após o ponteiro auxiliar
        curr->next = newNode;
    }
}

// Define uma estrutura para representar uma fila
typedef struct queue {
    int front; // O índice do início da fila
    int rear; // O índice do final da fila
    int size; // O tamanho atual da fila
    int capacity; // A capacidade máxima da fila
    int* array; // O vetor que armazena os elementos da fila
} Queue;

// Cria uma nova fila com uma dada capacidade e retorna o seu ponteiro
Queue* createQueue(int capacity) {
    Queue* newQueue = (Queue*) malloc(sizeof(Queue)); // Aloca memória para a fila
    newQueue->front = 0; // Inicializa o início da fila como 0
    newQueue->rear = capacity - 1; // Inicializa o final da fila como a última posição do vetor
    newQueue->size = 0; // Inicializa o tamanho da fila como 0
    newQueue->capacity = capacity; // Atribui a capacidade da fila
    newQueue->array = (int*) malloc(capacity * sizeof(int)); // Aloca memória para o vetor que armazena os elementos da fila
    return newQueue; // Retorna o ponteiro para a fila criada
}

// Verifica se uma fila está vazia
int isEmpty(Queue* q) {
    return (q->size == 0); // Retorna verdadeiro se o tamanho da fila é 0, falso caso contrário
}

// Verifica se uma fila está cheia
int isFull(Queue* q) {
    return (q->size == q->capacity); // Retorna verdadeiro se o tamanho da fila é igual à capacidade da fila, falso caso contrário
}

// Insere um elemento no final de uma fila, se ela não estiver cheia
void enqueue(Queue* q, int item) {
    if (isFull(q)) { // Se a fila está cheia, não pode inserir
        return;
    }
    q->rear = (q->rear + 1) % q->capacity; // Atualiza o final da fila, usando aritmética modular para circular pelo vetor
    q->array[q->rear] = item; // Insere o elemento no final da fila
    q->size++; // Incrementa o tamanho da fila
}

// Remove e retorna o elemento do início de uma fila, se ela não estiver vazia
int dequeue(Queue* q) {
    if (isEmpty(q)) { // Se a fila está vazia, não pode remover
        return -1;
    }
    int item = q->array[q->front]; // Armazena o elemento do início da fila em uma variável
    q->front = (q->front + 1) % q->capacity; // Atualiza o início da fila, usando aritmética modular para circular pelo vetor
    q->size--; // Decrementa o tamanho da fila
    return item; // Retorna o elemento removido
}

// Exibe a sequência da Busca em Largura (BFS) de um grafo g a partir de um nó/vértice inicial s
void BFS(Graph* g, int s) {
    int* visited = (int*) malloc(g->V * sizeof(int)); // Cria um vetor para marcar os nós/vértices visitados
    for (int i = 0; i < g->V; i++) { // Para cada nó/vértice do grafo
        visited[i] = 0; // Inicializa como não visitado
    }
    Queue* q = createQueue(g->V); // Cria uma fila com capacidade igual ao número de nós/vértices do grafo
    visited[s] = 1; // Marca o nó/vértice inicial como visitado
    enqueue(q, s); // Insere o nó/vértice inicial na fila
    while (!isEmpty(q)) { // Enquanto a fila não estiver vazia
        int u = dequeue(q); // Remove e armazena o nó/vértice do início da fila em uma variável
        printf("%d ", u); // Exibe o nó/vértice visitado
        Node* curr = g->adj[u]; // Cria um ponteiro auxiliar para percorrer a lista de adjacência do nó/vértice visitado
        while (curr != NULL) { // Enquanto não chegar ao final da lista
            int v = curr->data; // Armazena o valor do nó/vértice adjacente em uma variável
            if (!visited[v]) { // Se o nó/vértice adjacente não foi visitado ainda
                visited[v] = 1; // Marca como visitado
                enqueue(q, v); // Insere na fila
            }
            curr = curr->next; // Avança o ponteiro auxiliar para o próximo nó da lista
        }
    }
    free(visited); // Libera a memória alocada para o vetor de visitados
    free(q); // Libera a memória alocada para a fila
}

// Exibe a sequência da Busca em Profundidade(DFS) de um grafo g a partir de um nó/vértice inicial s, usando um vetor auxiliar de visitados e um ponteiro para indicar se é a primeira chamada da função recursiva ou não 
// Exibe a sequência da Busca em Profundidade (DFS) de um grafo g a partir de um nó/vértice inicial s, usando um vetor auxiliar de visitados e um ponteiro para indicar se é a primeira chamada da função recursiva ou não 
void DFSUtil(Graph* g, int s, int* visited, int* first) {
    if (*first) { // Se é a primeira chamada da função
        *first = 0; // Marca como não é mais a primeira chamada
        for (int i = 0; i < g->V; i++) { // Para cada nó/vértice do grafo
            visited[i] = 0; // Inicializa como não visitado
        }
    }
    visited[s] = 1; // Marca o nó/vértice inicial como visitado
    printf("%d ", s); // Exibe o nó/vértice visitado
    Node* curr = g->adj[s]; // Cria um ponteiro auxiliar para percorrer a lista de adjacência do nó/vértice visitado
    while (curr != NULL) { // Enquanto não chegar ao final da lista
        int v = curr->data; // Armazena o valor do nó/vértice adjacente em uma variável
        if (!visited[v]) { // Se o nó/vértice adjacente não foi visitado ainda
            DFSUtil(g, v, visited, first); // Chama a função recursivamente para o nó/vértice adjacente
        }
        curr = curr->next; // Avança o ponteiro auxiliar para o próximo nó da lista
    }
}

// Exibe a sequência da Busca em Profundidade (DFS) de um grafo g a partir de um nó/vértice inicial s
void DFS(Graph* g, int s) {
    int* visited = (int*) malloc(g->V * sizeof(int)); // Cria um vetor para marcar os nós/vértices visitados
    int first = 1; // Cria uma variável para indicar se é a primeira chamada da função DFSUtil ou não
    DFSUtil(g, s, visited, &first); // Chama a função DFSUtil com os parâmetros corretos
    free(visited); // Libera a memória alocada para o vetor de visitados
}

// Define as estruturas, variáveis globais, constantes e funções auxiliares aqui

int main() {
    int V; // O nó/vértice inicial
    int N; // O número total de nós/vértices
    int M; // O número de arestas
    int u, v; // Os nós/vértices de origem e destino de cada aresta

    // Lê o nó/vértice inicial
    scanf("%d", &V);

    // Lê o número total de nós/vértices
    scanf("%d", &N);

    // Cria um grafo com N nós/vértices
    Graph* g = createGraph(N);

    // Lê o número de arestas
    scanf("%d", &M);

    // Lê e adiciona as arestas no grafo
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &u, &v); // Lê os nós/vértices de origem e destino da aresta
        addEdge(g, u, v); // Adiciona a aresta no grafo
    }

    // Exibe a sequência da Busca em Largura a partir do nó/vértice inicial
    printf("BFS: ");
    BFS(g, V);
    printf("\n");

    // Exibe a sequência da Busca em Profundidade a partir do nó/vértice inicial
    printf("DFS: ");
    DFS(g, V);
    printf("\n");

    // Retorna 0 para indicar sucesso
    return 0;
}
