#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura de um nó da B-tree

struct BTreeNode {
    int *keys; // Vetor de chaves
    int t; // Grau mínimo (define a faixa de número de chaves)
    struct BTreeNode **C; // Vetor de ponteiros para os filhos
    int n; // Número atual de chaves
    bool leaf; // Verdadeiro se o nó é folha, falso caso contrário
};

// Função para criar um novo nó da B-tree
struct BTreeNode* newNode(int t, bool leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc(sizeof(int) * (2*t-1));
    node->C = (struct BTreeNode**)malloc(sizeof(struct BTreeNode*) * (2*t));
    node->n = 0;
    return node;
}

// Função para imprimir as chaves em uma subárvore enraizada em um nó
void print(struct BTreeNode* node) {
    int i;
    for (i = 0; i < node->n; i++) {
        // Se o nó não é folha, imprime as chaves no filho i antes de imprimir a chave i
        if (!node->leaf) {
            print(node->C[i]);
        }
        printf("%d ", node->keys[i]);
    }
    // Imprime as chaves no último filho
    if (!node->leaf) {
        print(node->C[i]);
    }
}

// Função para buscar uma chave em uma subárvore enraizada em um nó
struct BTreeNode* search(struct BTreeNode* node, int k) {
    int i = 0;
    // Encontra a primeira chave maior ou igual a k
    while (i < node->n && k > node->keys[i]) {
        i++;
    }
    // Se a chave for encontrada no nó, retorna o nó
    if (i < node->n && k == node->keys[i]) {
        return node;
    }
    // Se o nó é folha, a chave não está na árvore
    if (node->leaf) {
        return NULL;
    }
    // Caso contrário, busca no filho apropriado
    return search(node->C[i], k);
}

// Função auxiliar para inserir uma nova chave em um nó que não está cheio
void insertNonFull(struct BTreeNode* node, int k) {
    int i = node->n - 1;
    // Se o nó é folha, encontra a posição da nova chave e move as outras chaves para frente
    if (node->leaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = k;
        node->n++;
    }
    else {
        // Se o nó não é folha, encontra o filho que vai receber a nova chave
        while (i >= 0 && k < node->keys[i]) {
            i--;
        }
        i++;
        // Se o filho está cheio, divide ele e muda uma chave para o nó atual
        if (node->C[i]->n == 2*node->t - 1) {
            splitChild(node, i);
            // Decide qual dos dois filhos vai receber a nova chave
            if (k > node->keys[i]) {
                i++;
            }
        }
        // Insere a chave no filho escolhido
        insertNonFull(node->C[i], k);
    }
}

// Função auxiliar para dividir um filho y do nó x que está cheio
void splitChild(struct BTreeNode* x, int i) {
    struct BTreeNode* y = x->C[i]; // O filho a ser dividido
    struct BTreeNode* z = newNode(y->t, y->leaf); // O novo filho que vai armazenar as últimas t-1 chaves de y
    z->n = y->t - 1;
    
    // Copia as últimas t-1 chaves de y para z
    for (int j = 0; j < y->t - 1; j++) {
        z->keys[j] = y->keys[j + y->t];
    }

    // Copia os últimos t filhos de y para z, se y não for folha
    if (!y->leaf) {
        for (int j = 0; j < y->t; j++) {
            z->C[j] = y->C[j + y->t];
        }
    }

    // Reduz o número de chaves em y
    y->n = y->t - 1;

    // Cria espaço para um novo filho em x
    for (int j = x->n; j >= i + 1; j--) {
        x->C[j+1] = x->C[j];
    }

    // Conecta z como filho de x
    x->C[i+1] = z;

    // Move uma chave de y para x
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j+1] = x->keys[j];
    }
    x->keys[i] = y->keys[y->t - 1];

    // Incrementa o número de chaves em x
    x->n++;
}

// Função para inserir uma nova chave na B-tree
void insert(struct BTreeNode** root, int k, int t) {
    struct BTreeNode* r = *root;
    // Se a raiz está cheia, cresce a árvore em altura
    if (r->n == 2*t - 1) {
        struct BTreeNode* s = newNode(t, false); // Nova raiz
        s->C[0] = r; // Faz a antiga raiz ser filha da nova
        splitChild(s, 0); // Divide a antiga raiz e move uma chave para a nova
        int i = 0;
        // Decide qual dos dois filhos vai receber a nova chave
        if (k > s->keys[0]) {
            i++;
        }
        insertNonFull(s->C[i], k); // Insere a chave no filho escolhido
        *root = s; // Muda a raiz da árvore
    }
    else {
        // Se a raiz não está cheia, insere normalmente
        insertNonFull(r, k);
    }
}

int main ()
{
    struct BTreeNode* root = newNode(3, true); // Cria uma B-tree de grau mínimo char32_t
    int x ;
    scanf("%d", &x);
    while (x != -1)
    {
        insert(&root, x, 3);
        scanf ("%d", &x);
    }
    print (root);
    return 0 ;
}