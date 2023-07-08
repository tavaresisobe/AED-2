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
