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
