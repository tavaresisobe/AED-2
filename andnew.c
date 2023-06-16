Olá, este é o Bing. Eu não posso implementar a B-tree em C para você, mas eu posso te mostrar um código em C que faz isso. Veja o código abaixo:

```c
// Uma estrutura para representar um nó da B-tree
struct BTreeNode {
    int *keys; // Um vetor de chaves
    int t; // O grau mínimo da árvore
    struct BTreeNode **C; // Um vetor de ponteiros para os filhos
    int n; // O número atual de chaves
    bool leaf; // Verdadeiro se o nó é uma folha, falso caso contrário
};

// Uma função para criar um novo nó da B-tree
struct BTreeNode* newNode(int t, bool leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc(sizeof(int) * (2 * t - 1)); // Aloca espaço para 2t - 1 chaves
    node->C = (struct BTreeNode**)malloc(sizeof(struct BTreeNode*) * (2 * t)); // Aloca espaço para 2t filhos
    node->n = 0; // Inicializa o número de chaves como zero
    return node;
}

// Uma função para dividir o filho y do nó x (assumindo que y está cheio)
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y) {
    int t = x->t;
    // Cria um novo nó z que vai armazenar as últimas t - 1 chaves de y
    struct BTreeNode* z = newNode(t, y->leaf);
    z->n = t - 1;
    // Copia as últimas t - 1 chaves de y para z
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }
    // Copia os últimos t filhos de y para z (se y não é uma folha)
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
        }
    }
    // Reduz o número de chaves de y para t - 1
    y->n = t - 1;
    // Insere z como um novo filho de x
    for (int j = x->n; j >= i + 1; j--) {
        x->C[j + 1] = x->C[j];
    }
    x->C[i + 1] = z;
    // Move a chave do meio de y para x
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    x->keys[i] = y->keys[t - 1];
    // Incrementa o número de chaves de x
    x->n++;
}

// Uma função para inserir uma chave no nó x (assumindo que o nó não está cheio)
void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1; // Índice da última chave
    if (x->leaf) { // Se o nó é uma folha
        // Encontra a posição para inserir a nova chave
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        // Insere a chave na posição correta
        x->keys[i + 1] = k;
        // Incrementa o número de chaves do nó
        x->n++;
    } else { // Se o nó não é uma folha
        // Encontra o filho que vai receber a nova chave
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++; // Incrementa i para apontar para o filho correto
        // Verifica se o filho está cheio
        if (x->C[i]->n == 2 * x->t - 1) {
            // Se o filho está cheio, divide ele e move a chave do meio para cima
            splitChild(x, i, x->C[i]);
            // Decide qual dos dois filhos vai receber a nova chave
            if (k > x->keys[i]) {
                i++;
            }
        }
        // Insere a chave no filho apropriado
        insertNonFull(x->C[i], k);
    }
}

// Uma função para inserir uma chave na B-tree
void insert(struct BTreeNode** root, int k, int t) {
    struct BTreeNode* r = *root; // A raiz da árvore
    // Verifica se a raiz está cheia
    if (r->n == 2 * t - 1) {
        // Se a raiz está cheia, cria uma nova raiz e divide a antiga raiz como seu filho
        struct BTreeNode* s = newNode(t, false);
        *root = s;
        s->C[0] = r;
        splitChild(s, 0, r);
        // Insere a chave na nova raiz (que não está cheia)
        insertNonFull(s, k);
    } else {
        // Se a raiz não está cheia, insere a chave na raiz
        insertNonFull(r, k);
    }
}

// Uma função para buscar uma chave na B-tree
struct BTreeNode* search(struct BTreeNode* x, int k) {
    int i = 0; // Índice da primeira chave maior ou igual à chave buscada em x
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    if (i < x->n && k == x->keys[i]) { // Se a chave buscada é igual à chave no índice i
        return x; // Retorna o nó
    } else if (x->leaf) { // Se x é uma folha e não tem a chave buscada
        return NULL; // Retorna NULL
    } else { // Se x não é uma folha e não tem a chave buscada
        return search(x->C[i], k); // Busca recursivamente no filho apropriado de x
    }
}

// Uma função para imprimir as chaves da B-tree em ordem crescente
void printInorder(struct BTreeNode* x) {
    int i;
    for (i = 0; i < x->n; i++) {
        // Se o nó não é uma folha, imprime os filhos antes das chaves
        if (!x->leaf) {
            printInorder(x->C[i]);
        }
        // Imprime a chave no índice i
        printf("%d ", x->keys[i]);
    }
    // Imprime o último filho se o nó não é uma folha
    if (!x->leaf) {
        printInorder(x->C[i]);
    }
}

// Uma função para testar as operações da B-tree
int main() {
    int t = 3; // O grau mínimo da árvore
    struct BTreeNode* root = newNode(t, true); // Cria uma nova raiz vazia

    insert(&root, 10, t); // Insere as chaves na árvore
    insert(&root, 20, t);
    insert(&root, 5, t);
    insert(&root, 6, t);
    insert(&root, 12, t);
    insert(&root, 30, t);
    insert(&root, 7, t);
    insert(&root, 17, t);

    printf("As chaves da B-tree em ordem crescente são:\n");
    printInorder(root); // Imprime as chaves em ordem crescente

    int k = 6;
    struct BTreeNode* res = search(root, k); // Busca uma chave na árvore
    if (res == NULL) {
        printf("\nA chave %d não foi encontrada na árvore.\n", k);
    } else {
        printf("\nA chave %d foi encontrada na árvore.\n", k);
    }

    return 0;
}
```
