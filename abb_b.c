
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define T 10

struct btree_node {
    int keys[2 * T - 1];
    struct btree_node* children[2 * T];
    int num_keys;
};

struct btree {
    struct btree_node* root;
};

struct btree_node* btree_node_create() {
    struct btree_node* node = malloc(sizeof(struct btree_node));
    node->num_keys = 0;
    for (int i = 0; i < 2 * T; i++) {
        node->children[i] = NULL;
    }
    return node;
}

struct btree* btree_create() {
    struct btree* tree = malloc(sizeof(struct btree));
    tree->root = btree_node_create();
    return tree;
}

bool btree_node_search(struct btree_node* node, int key) {
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }

    if (i < node->num_keys && key == node->keys[i]) {
        return true;
    }

    if (node->children[i] == NULL) {
        return false;
    }

    return btree_node_search(node->children[i], key);
}

bool btree_search(struct btree* tree, int key) {
    return btree_node_search(tree->root, key);
}

void btree_insert(struct btree* tree, int key) {
    btree_node_insert(tree->root, key);
}

void btree_node_insert(struct btree_node* node, int key) {
    int i = node->num_keys - 1;
    if (node->children[0] == NULL) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->num_keys == 2 * T - 1) {
            btree_node_split_child(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        btree_node_insert(node->children[i], key);
    }
}

void btree_node_split_child(struct btree_node* node, int i) {
    struct btree_node* child = node->children[i];
    struct btree_node* new_child = btree_node_create();
    new_child->num_keys = T - 1;

    for (int j = 0; j < T - 1; j++) {
        new_child->keys[j] = child->keys[j + T];
    }

    if (child->children[0] != NULL) {
        for (int j = 0; j < T; j++) {
            new_child->children[j] = child->children[j + T];
            child->children[j + T] = NULL;
        }
    }

    child->num_keys = T - 1;

    for (int j = node->num_keys; j >= i + 1; j--) {
        node->children[j + 1] = node->children[j];
    }

    node->children[i+1] = new_child;

    for (int j = node->num_keys - 1; j >= i; j--) {
        node->keys[j + 1] = node->keys[j];
    }

    node->keys[i] = child->keys[T - 1];
    node->num_keys++;
}

void btree_print(struct btree* tree, struct btree_node* node, int level) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < node->num_keys; i++) {
        btree_print(tree, node->children[i], level + 1);
        for (int j = 0; j < level; j++) {
            printf(" ");
        }
        printf("%d\n", node->keys[i]);
    }
    btree_print(tree, node->children[node->num_keys], level + 1);
}

int main() {
    struct btree* tree = btree_create();
    int x ;
    scanf ("%d", &x) ;
    while (x != -1)
    {
        btree_insert(tree, x) ;
        scanf ("%d", &x) ;
    }
    
    btree_print(tree, tree->root, 0);

    bool found1 = btree_search(tree, 6);
    bool found2 = btree_search(tree, 18);

    printf("Found 6: %d\n", found1);
    printf("Found 18: %d\n", found2);

    return 0;
}

// Criar uma nova B-tree
//struct btree* tree = btree_create();

// Inserir um novo elemento na árvore
//btree_insert(tree, 10);

// Realizar uma busca por um elemento na árvore (Retornará 1 ou 0)
//bool found = btree_search(tree, 10);
