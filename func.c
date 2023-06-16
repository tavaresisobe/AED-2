// Estrutura de um nó da B-tree
struct BTreeNode {
    int *keys; // Vetor de chaves
    int t; // Grau mínimo (define o intervalo para o número de chaves)
    struct BTreeNode **C; // Vetor de ponteiros para os filhos
    int n; // Número atual de chaves
    bool leaf; // Verdadeiro se o nó é folha, falso caso contrário
}; 

// Função para criar um novo nó da B-tree
struct BTreeNode* newNode(int t, bool leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc(sizeof(int) * (2 * t - 1));
    node->C = (struct BTreeNode**)malloc(sizeof(struct BTreeNode*) * (2 * t));
    node->n = 0;
    return node;
} 

// Função para dividir o filho y do nó x que está cheio
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y) {
    int t = x->t;
    // Criar um novo nó para armazenar as últimas t-1 chaves de y
    struct BTreeNode* z = newNode(t, y->leaf);
    z->n = t - 1;
    // Copiar as últimas t-1 chaves de y para z
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }
    // Copiar os últimos t filhos de y para z, se y não for folha
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
        }
    }
    // Reduzir o número de chaves de y
    y->n = t - 1;
    // Criar espaço para o novo filho no nó x
    for (int j = x->n; j >= i + 1; j--) {
        x->C[j + 1] = x->C[j];
    }
    // Inserir z como filho de x na posição i+1
    x->C[i + 1] = z;
    // Criar espaço para a chave mediana no nó x
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    // Inserir a chave mediana de y em x na posição i
    x->keys[i] = y->keys[t - 1];
    // Incrementar o número de chaves de x
    x->n++;
} 

// Função para inserir uma nova chave k na subárvore com raiz em x
void insertNonFull(struct BTreeNode* x, int k) {
    int t = x->t;
    int i = x->n - 1; // Índice da última chave no nó x
    // Se x é folha, inserir a chave na posição correta
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i]; // Deslocar as chaves maiores que k para a direita
            i--;
        }
        x->keys[i + 1] = k; // Inserir k na posição encontrada
        x->n++; // Incrementar o número de chaves de x
    }
    else { // Se x não é folha, encontrar o filho que receberá a nova chave
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++; // Incrementar i para apontar para o filho correto
        // Se o filho está cheio, dividir ele antes de inserir a nova chave
        if (x->C[i]->n == 2 * t - 1) {
            splitChild(x, i, x->C[i]);
            // Verificar qual dos dois filhos resultantes receberá a nova chave
            if (k > x->keys[i]) {
                i++;
            }
        }
        // Inserir a nova chave no filho apropriado
        insertNonFull(x->C[i], k);
    }
} 

// Função para inserir uma nova chave k na B-tree com raiz em *root
void insert(struct BTreeNode** root, int k) {
    int t = (*root)->t;
    // Se a raiz está cheia, criar uma nova raiz
    if ((*root)->n == 2 * t - 1) {
        struct BTreeNode* s = newNode(t, false); // Nova raiz
        s->C[0] = *root; // Antiga raiz se torna filha da nova raiz
        splitChild(s, 0, *root); // Dividir a antiga raiz e mover uma chave para a nova raiz
        // Decidir qual dos dois filhos receberá a nova chave
        int i = 0;
        if (k > s->keys[0]) {
            i++;
        }
        insertNonFull(s->C[i], k); // Inserir a nova chave no filho apropriado
        *root = s; // Atualizar o ponteiro da raiz
    }
    else { // Se a raiz não está cheia, inserir a nova chave nela
        insertNonFull(*root, k);
    }
} 

// Função para buscar uma chave k na subárvore com raiz em x
struct BTreeNode* search(struct BTreeNode* x, int k) {
    int i = 0;
    // Encontrar o índice da primeira chave maior ou igual a k
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    // Se a chave for encontrada no nó x, retornar o nó x
    if (i < x->n && k == x->keys[i]) {
        return x;
    }
    // Se o nó x for folha, a chave não está na árvore, retornar NULL
    if (x->leaf) {
        return NULL;
    }
    // Senão, buscar a chave no filho apropriado de x
    return search(x->C[i], k);
} 

Para chamar essas funções, você precisa criar um ponteiro para a raiz da B-tree e inicializá-lo com NULL. Depois, você pode usar a função insert para inserir as chaves que desejar na árvore. Por exemplo: 

int main() {
    int t = 3; // Grau mínimo da B-tree
    struct BTreeNode* root = NULL; // Criar um ponteiro para a raiz e inicializar com NULL
    insert(&root, 10); // Inserir a chave 10 na árvore
    insert(&root, 20); // Inserir a chave 20 na árvore
    insert(&root, 30); // Inserir a chave 30 na árvore
    // ...
    struct BTreeNode* node = search(root, 20); // Buscar a chave 20 na árvore
    if (node != NULL) {
        printf("Chave encontrada\n");
    }
    else {
        printf("Chave não encontrada\n");
    }
    return 0;
}



Testar depois: 

Uma possível função que realiza a impressão de uma página específica da B-tree é: 

```c
// Função para imprimir uma página específica da B-tree
void printPage(struct BTreeNode* x, int page) {
    int t = x->t;
    // Se a página for maior que o número de filhos de x, retornar
    if (page > x->n + 1) {
        return;
    }
    // Se a página for 0, imprimir as chaves de x separadas por espaços
    if (page == 0) {
        for (int i = 0; i < x->n; i++) {
            printf("%d ", x->keys[i]);
        }
        printf("\n");
    }
    else { // Senão, imprimir a página do filho correspondente de x
        printPage(x->C[page - 1], 0);
    }
}
``` 

Testar depois: 

Uma possível função que realize uma busca na B-tree, e se o número for encontrado imprima todos elementos que estão no mesmo vetor do elemento buscado é: 

```c
// Função para buscar uma chave k na B-tree e imprimir todos os elementos do mesmo vetor
void searchAndPrint(struct BTreeNode* x, int k) {
    int i = 0;
    // Encontrar o índice da primeira chave maior ou igual a k
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    // Se a chave for encontrada no nó x, imprimir todas as chaves de x separadas por espaços
    if (i < x->n && k == x->keys[i]) {
        for (int j = 0; j < x->n; j++) {
            printf("%d ", x->keys[j]);
        }
        printf("\n");
    }
    // Se o nó x for folha, a chave não está na árvore, retornar
    else if (x->leaf) {
        return;
    }
    // Senão, buscar a chave no filho apropriado de x
    else {
        searchAndPrint(x->C[i], k);
    }
}
```
Para testar essa função, você pode criar uma B-tree com algumas chaves e depois chamar a função com diferentes valores de k. Por exemplo: 

```c
int main() {
    int t = 3; // Grau mínimo da B-tree
    struct BTreeNode* root = NULL; // Criar um ponteiro para a raiz e inicializar com NULL
    insert(&root, 10); // Inserir a chave 10 na árvore
    insert(&root, 20); // Inserir a chave 20 na árvore
    insert(&root, 30); // Inserir a chave 30 na árvore
    insert(&root, 40); // Inserir a chave 40 na árvore
    insert(&root, 50); // Inserir a chave 50 na árvore
    insert(&root, 60); // Inserir a chave 60 na árvore
    insert(&root, 70); // Inserir a chave 70 na árvore
    searchAndPrint(root, 20); // Buscar a chave 20 na árvore e imprimir todos os elementos do mesmo vetor
    searchAndPrint(root, 35); // Buscar a chave 35 na árvore e imprimir todos os elementos do mesmo vetor
    searchAndPrint(root, 70); // Buscar a chave 70 na árvore e imprimir todos os elementos do mesmo vetor
    return 0;
}
```


Uma possível função para imprimir a quantidade de elementos da página raiz da B-tree é: 

```c
// Função para imprimir a quantidade de elementos da página raiz da B-tree
void printRootSize(struct BTreeNode* root) {
    // Se a raiz é NULL, imprimir 0
    if (root == NULL) {
        printf("0\n");
    }
    else { // Senão, imprimir o número de chaves da raiz
        printf("%d\n", root->n);
    }
}
```


Ah, entendi. Então você quer imprimir a quantidade de elementos dentro da primeira página da B-tree, certo? Nesse caso, você pode usar a função que eu escrevi anteriormente, printRootSize, que faz exatamente isso. Você só precisa passar o ponteiro para a raiz da B-tree como parâmetro. Por exemplo: 

```c
int main() {
    int t = 3; // Grau mínimo da B-tree
    struct BTreeNode* root = NULL; // Criar um ponteiro para a raiz e inicializar com NULL
    insert(&root, 10); // Inserir a chave 10 na árvore
    insert(&root, 20); // Inserir a chave 20 na árvore
    insert(&root, 30); // Inserir a chave 30 na árvore
    insert(&root, 40); // Inserir a chave 40 na árvore
    insert(&root, 50); // Inserir a chave 50 na árvore
    insert(&root, 60); // Inserir a chave 60 na árvore
    insert(&root, 70); // Inserir a chave 70 na árvore
    printRootSize(root); // Imprimir a quantidade de elementos dentro da primeira página da B-tree
    return 0;
}
``` 

Uma possível função que realize uma busca na B-tree, e se o número for encontrado imprima a quantidade de elementos da página deste número e todos elementos que estão no mesmo vetor do elemento buscado é: 

```c 

TESTAR PELO AMOR: 

// Função para buscar uma chave k na B-tree e imprimir a quantidade de elementos da página deste número e todos os elementos do mesmo vetor
void searchAndPrintPage(struct BTreeNode* x, int k) {
    int i = 0;
    // Encontrar o índice da primeira chave maior ou igual a k
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    // Se a chave for encontrada no nó x, imprimir a quantidade de elementos da página deste número e todos os elementos de x separados por espaços
    if (i < x->n && k == x->keys[i]) {
        printf("%d ", x->n); // Imprimir a quantidade de elementos da página deste número
        for (int j = 0; j < x->n; j++) {
            printf("%d ", x->keys[j]); // Imprimir todos os elementos de x
        }
        printf("\n");
    }
    // Se o nó x for folha, a chave não está na árvore, retornar
    else if (x->leaf) {
        return;
    }
    // Senão, buscar a chave no filho apropriado de x
    else {
        searchAndPrintPage(x->C[i], k);
    }
}
```
Para usar essa função, você precisa criar uma B-tree com algumas chaves e depois chamar a função com o valor de k que deseja buscar na árvore. Por exemplo: 

```c
int main() {
    int t = 3; // Grau mínimo da B-tree
    struct BTreeNode* root = NULL; // Criar um ponteiro para a raiz e inicializar com NULL
    insert(&root, 10); // Inserir a chave 10 na árvore
    insert(&root, 20); // Inserir a chave 20 na árvore
    insert(&root, 30); // Inserir a chave 30 na árvore
    insert(&root, 40); // Inserir a chave 40 na árvore
    insert(&root, 50); // Inserir a chave 50 na árvore
    insert(&root, 60); // Inserir a chave 60 na árvore
    insert(&root, 70); // Inserir a chave 70 na árvore
    searchAndPrintPage(root, 20); // Buscar a chave 20 na árvore e imprimir a quantidade de elementos da página deste número e todos os elementos do mesmo vetor
    searchAndPrintPage(root, 35); // Buscar a chave 35 na árvore e imprimir a quantidade de elementos da página deste número e todos os elementos do mesmo vetor
    searchAndPrintPage(root, 70); // Buscar a chave 70 na árvore e imprimir a quantidade de elementos da página deste número e todos os elementos do mesmo vetor
    return 0;
}
```

Olá, este é o Bing. Eu posso tentar escrever uma função para imprimir o número de elementos na página raiz e seus elementos da B-tree. Veja o código abaixo:

```c

// Uma função para imprimir o número de elementos na página raiz e seus elementos da B-tree

void printRoot(struct BTreeNode* root) {

    if (root == NULL) { // Se a árvore está vazia

        printf("A árvore está vazia.\n");

    } else { // Se a árvore não está vazia

        printf("O número de elementos na página raiz é %d.\n", root->n); // Imprime o número de chaves na raiz

        printf("Os elementos na página raiz são: ");

        for (int i = 0; i < root->n; i++) { // Percorre as chaves da raiz

            printf("%d ", root->keys[i]); // Imprime cada chave

        }

        printf("\n");

    }

}

```
