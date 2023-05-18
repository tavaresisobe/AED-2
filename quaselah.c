#include<stdio.h>
#include<stdlib.h>
//6 4 3 2 1 -1 4 5 -1 1
//16 14 20 12 11 19 18 15 17 13 -1 14 19 15 20 -1 18

// structure of the tree node
struct node
{
    int data;
    struct node* left;
    struct node* right;
    int ht;
};

// global initialization of root node
struct node* root = NULL;
 
// function prototyping
struct node* create(int);
struct node* insert(struct node*, int);
struct node* delete(struct node*, int);
struct node* search(struct node*, int);
struct node* rotate_left(struct node*);
struct node* rotate_right(struct node*);
int balance_factor(struct node*);
int height(struct node*);
void imprimir(struct node*);
 
int main()
{
  int chave, data, i;
  struct node* result = NULL;
 
  do{
    scanf("%d", &chave) ;
    if (chave == -1)
      break ;
    root = insert(root, chave) ;
  }while (1) ;

  do{
    scanf("%d", &chave) ;
    if (chave == -1)
      break ;
    result = search(root, chave);
    if (result == NULL)
    {
      root = insert(root, chave);
    }else
      root = delete(root, chave);
  }while(1) ;
  scanf ("%d", &i) ;
  result = search(root, i) ;
  printf ("%d,%d,%d\n", height(root), height(root->left), height(root->right)) ;
  //printf("%d,", height(root)) ;
  if (result)
  {
    printf ("%d,%d,%d\n", height(result), height(result->left), height(result->right)) ;
    printf ("Valor encontrado\n") ;
  }else
    printf ("Valor nao encontrado\n") ;
  
  imprimir(root) ;
 
  return 0;
}
 
// creates a new tree node
struct node* create(int data)
{
  struct node* novo = (struct node*) malloc (sizeof(struct node));
  // if a memory error has occurred
  if (novo)
  {
    novo->data = data;
    novo->left = NULL;
    novo->right = NULL;
  }else
    printf("\nERRO ao alocar nó em novoNo!\n");
  return novo;
}
 
// rotates to the left
struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);
 
    // return the new node after rotation
    return right_child;
}
 
// rotates to the right
struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);
 
    // return the new node after rotation
    return left_child;
}
 
// calculates the balance factor of a node
int balance_factor(struct node* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}
 
// calculate the height of the node
int height(struct node* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
 
    if (lh > rh)
      return (lh);
    return (rh);
}

    //Função para calcular a altura de uma árvore binária
/*
int height(struct node* raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = height(raiz->left);
        int dir = height(raiz->right);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}
*/
 
// inserts a new node in the AVL tree
struct node* insert(struct node* root, int data)
{
    if (root == NULL)
    {
        struct node* new_node = create(data);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (data > root->data)
    {
        // insert the new node to the right
        root->right = insert(root->right, data);
 
        // tree is unbalanced, then rotate it
        if (balance_factor(root) == -2)
        {
            if (data > root->right->data)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert(root->left, data);
 
        // tree is unbalanced, then rotate it
        if (balance_factor(root) == 2)
        {
            if (data < root->left->data)
            {
                root = rotate_right(root);
            }
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height(root);
    return root;
}
 
// deletes a node from the AVL tree
struct node * delete(struct node *root, int x)
{
    struct node * temp = NULL;
 
    if (root == NULL)
    {
        return NULL;
    } 
 
    if (x > root->data)
    {
        root->right = delete(root->right, x);
        if (balance_factor(root) == 2)
        {
            if (balance_factor(root->left) >= 0)
            {
                root = rotate_right(root);
            }
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    else if (x < root->data)
    {
        root->left = delete(root->left, x);
        if (balance_factor(root) == -2)
        {
            if (balance_factor(root->right) <= 0)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        if (root->right != NULL)
        { 
            temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
 
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
            if (balance_factor(root) == 2)
            {
                if (balance_factor(root->left) >= 0)
                {
                    root = rotate_right(root);
                }
                else
                {
                    root->left = rotate_left(root->left);
                    root = rotate_right(root);
                }
            }
        }
        else
        {
            return (root->left);
        }
    }
    root->ht = height(root);
    return (root);
}
 
// search a node in the AVL tree
struct node* search(struct node* root, int key)
{
  if (root == NULL)
    {
        return NULL;
    }
 
    if(root->data == key)
    {
        return root;
    }
 
    if(key > root->data)
    {
        search(root->right, key);
    }
    else
    {
        search(root->left, key);
    } 
}
 
// inorder traversal of the tree
void inorder(struct node* root)
{
  if (root == NULL)
  {
      return;
  }
 
  inorder(root->left);
  printf("%d ", root->data);
  inorder(root->right);
}
 
// preorder traversal of the tree
void preorder(struct node* root)
{
  if (root == NULL)
  {
    return;
  }
  printf("%d ", root->data);
  preorder(root->left);
  preorder(root->right);
}

// postorder traversal of the tree
void imprimir(struct node* aux)
{
  if (aux!= NULL)
        printf("%d ", aux->data);
    if (aux->right!= NULL)
        imprimir(aux->right);
    if (aux->left!= NULL)
        imprimir(aux->left);
}
