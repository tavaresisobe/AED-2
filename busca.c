/ Função para buscar uma chave k na B-tree e imprimir a quantidade de elementos da página deste número e todos os elementos do mesmo vetor
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
