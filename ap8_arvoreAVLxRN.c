#include<stdio.h>
#include<stdlib.h>

struct arvoreRN{
  int num;
  struct arvore *esq;
  struct arvore *dir;
  int cor ; //0 = negro, 1 = rubro
};

typedef struct arvoreRN TipoArvoreRN;
typedef TipoArvoreRN* ArvoreRN;

struct arvore{
  int num;
  struct arvore *esq;
  struct arvore *dir;
  int h;
};

typedef struct arvore TipoArvore;
typedef TipoArvore* Arvore;

int arvoreVazia(Arvore arvore){
  return arvore==NULL;
}

Arvore inicializaArvore(){
  return NULL;
}

Arvore instanciaArvore(int num){
  Arvore arvore;
  arvore = (Arvore)malloc(sizeof(TipoArvore));
  arvore->num = num;
  arvore->esq = NULL;
  arvore->dir = NULL;
  arvore->h = 1;        //toda arvore criada é folha inicialmente, logo h = 0
  return arvore;
}

Arvore destroiArvore(Arvore arvore){
  if(!arvoreVazia(arvore)){
    destroiArvore(arvore->esq);
    destroiArvore(arvore->dir);
    free(arvore);
  }
  return NULL;
}

Arvore insereNum(Arvore raiz, int num){
 if(raiz==NULL){
   raiz = instanciaArvore(num);
   return raiz;
   }
  if(num < raiz->num){
    raiz->esq = insereNum(raiz->esq,num);
  }else{
    raiz->dir = insereNum(raiz->dir,num);
  }
  return raiz;
}
void imprimePreOrdem(Arvore raiz){
  if(raiz != NULL){
  printf("%d ",raiz->num);
  imprimePreOrdem(raiz->esq);
  imprimePreOrdem(raiz->dir);
  }
}

void imprimeEmOrdem(Arvore raiz){
  if(raiz!=NULL){
    imprimeEmOrdem(raiz->esq);
    printf("%d ",raiz->num);
    imprimeEmOrdem(raiz->dir);
  }
}

void imprimePosOrdem(Arvore raiz){
  if(raiz!=NULL){
    imprimePosOrdem(raiz->esq);
    imprimePosOrdem(raiz->dir);
    printf("%d ",raiz->num);
  }
}

Arvore busca(Arvore arvore, int num){
 if(arvoreVazia(arvore)) 
   return NULL;
  if(arvore->num == num) 
    return arvore;
  if(arvore->num > num)
    return busca(arvore->esq,num);
  return busca(arvore->dir,num);
}

Arvore buscaAux(Arvore arvore, int num, Arvore* pai){  //utilizada na funcao de remocao
  Arvore noAtual = arvore;
  *pai = NULL;
  while(noAtual){
    if(noAtual->num == num) 
      return noAtual;
    *pai = noAtual;
    if(num < noAtual->num)
      noAtual = noAtual->esq;
    else noAtual = noAtual->dir;
  }
    return NULL;  //se nao for retornado noAtual significa que o num nao foi encontrado na arvore e consequentemente a funcao retorna NULL
}

Arvore removeNum(Arvore arvore, int num){
  Arvore node, pai, a, b;
  node = buscaAux(arvore,num,&pai);
    if(node==NULL) return arvore;
    if (!node->esq || node->dir){
      if (!node->esq) b = node->dir;
      else b = node->dir;
    } else {
      a = node;
      b = node->esq;
        while(b->dir){
          a = b;
          b = b->dir;
        }
      if (a!=node){
        a->dir = b->esq;
        b->esq = node->esq;
      }
        b->dir = node->dir;
    }
          if(!pai) {
            free(node);
            return b;
          }
              if(num < pai->num)
                pai->esq = b;
              else 
                pai->dir = b;

                free(node);
                return arvore;
  }

//arvores AVL
int maxValue(int x, int y){
  if (x>y) return x;
  else return y;
}

int altura(Arvore arvore){
  if(arvore == NULL) return 0;
  return arvore->h;
}




Arvore rotDireita(Arvore arvore){
  Arvore aux1 = arvore->esq;  //nesse codigo, aux2 nao é estritamente necessario, porem ajuda no entendimento
  Arvore aux2 = aux1->dir;
    aux1->dir = arvore;
    arvore->esq = aux2;
    
 
    
    arvore->h = maxValue(altura(arvore->esq),altura(arvore->dir)) + 1;
    aux1->h = maxValue(altura(aux1->esq),altura(aux1->dir)) + 1;
 
    
    return aux1;
  
}

Arvore rotEsquerda(Arvore arvore){
  Arvore aux1 = arvore->dir;  //nesse codigo, aux2 nao é estritamente necessario, porem ajuda no entendimento
  Arvore aux2 = aux1->esq;
    aux1->esq = arvore;
    arvore->dir = aux2;
    
    arvore->h = maxValue(altura(arvore->esq),altura(arvore->dir)) + 1;
    aux1->h = maxValue(altura(aux1->esq),altura(aux1->dir)) + 1;
 
    
    return aux1;
  
}

Arvore rotEsquerdaDireita(Arvore arvore){
  arvore->esq = rotEsquerda(arvore->esq);
  return rotDireita(arvore);
}

Arvore rotDireitaEsquerda(Arvore arvore){
  arvore->dir = rotDireita(arvore->dir);
  return rotEsquerda(arvore);
}

int fatorBalanceamento(Arvore node) {
    if (node == NULL)
        return 0;
    return altura(node->esq) - altura(node->dir);
}


Arvore insereAVL(Arvore arvore, int num) {
    if (arvore == NULL)
        return instanciaArvore(num);
    if (num < arvore->num)
        arvore->esq = insereAVL(arvore->esq, num);
    else if (num > arvore->num)
        arvore->dir = insereAVL(arvore->dir, num);
    else
        return arvore; 

    arvore->h = maxValue(altura(arvore->esq), altura(arvore->dir))+1;

    // verifica o balanceamento da arvore
    int balanceFactor = fatorBalanceamento(arvore);

    if (balanceFactor > 1 && fatorBalanceamento(arvore->esq) >=0)  //num < arvore->esq->num
        return rotDireita(arvore);

    if (balanceFactor < -1 && fatorBalanceamento(arvore->dir) <=0)   //num > arvore->dir->num
        return rotEsquerda(arvore);

    if (balanceFactor > 1 && fatorBalanceamento(arvore->esq)<0) {   //num > arvore->esq->num
        return rotEsquerdaDireita(arvore);
             
    }
    if (balanceFactor < -1 && fatorBalanceamento(arvore->dir)>0) {   //num < arvore->dir->num
        return rotDireitaEsquerda(arvore);
}


return arvore;
}

Arvore removeAVL(Arvore arvore, int num)
{
    
    if (arvore == NULL)
        return arvore;
    if ( num < arvore->num )
        arvore->esq = removeAVL(arvore->esq, num);
    else if( num > arvore->num )
        arvore->dir = removeAVL(arvore->dir, num);
    else
    {
        if( (arvore->esq == NULL) || (arvore->dir == NULL) )
        {
            Arvore temp = arvore->esq ? arvore->esq :arvore->dir;
            if (temp == NULL)
            {
                temp = arvore;
                arvore = NULL;
            }
            else 
             *arvore = *temp; 
            free(temp);
        }
        else
        {
          Arvore atualMin = arvore->dir;
          while(atualMin->esq != NULL) atualMin = atualMin->esq;  //obtem o valor minimo da arvore
            
        
          
            arvore->num = atualMin->num;
 
          
            arvore->dir = removeAVL(arvore->dir, atualMin->num);
        }
    }
 
    if (arvore == NULL)
      return arvore;
 
    
    arvore->h = maxValue(altura(arvore->esq),
                           altura(arvore->dir))+1;
 
    
    int fator = fatorBalanceamento(arvore);
 
  
    if (fator > 1 && fatorBalanceamento(arvore->esq) >= 0) //LL
        return rotDireita(arvore);
 
    if (fator > 1 && fatorBalanceamento(arvore->esq) < 0)  //LR
    {
        arvore->esq =  rotEsquerda(arvore->esq);
        return rotDireita(arvore);
    }
    
    if (fator < -1 && fatorBalanceamento(arvore->dir) <= 0)  //RR
        return rotEsquerda(arvore);
 
    
    if (fator < -1 && fatorBalanceamento(arvore->dir) > 0)  //RL
    {
        arvore->dir = rotDireita(arvore->dir);
        return rotEsquerda(arvore);
    }
 
    return arvore;
}

int alturaArvore(Arvore arvore)
{
    if (arvore == NULL)
        return 0;
    else {
        int alturaEsq = alturaArvore(arvore->esq);
        int alturaDir = alturaArvore(arvore->dir);
 
        
        if (alturaEsq > alturaDir)
            return (alturaEsq +1);
        else
            return (alturaDir +1);
    }
}

//16 14 20 12 11 19 18 15 17 13 -1 14 19 15 20 -1  

int main(void) {
  int number;
  Arvore arvore = inicializaArvore(),aux;
  ArvoreRN arvoreRN = inicializaArvore(), auxRN;

  while(1){
    scanf("%d",&number);
    if(number>=0){
      arvore = insereAVL(arvore,number);
      
    }
    else break;
  }

  printf("%d,",alturaArvore(arvore)-1);
  printf("%d,",alturaArvore(arvore->esq));
  printf("%d\n",alturaArvore(arvore->dir));

  while(1){
      scanf("%d",&number);
      if(number>=0){
        aux = busca(arvore,number);
        if(aux == NULL){
          arvore = insereAVL(arvore,number);
          
        }else {
          arvore = removeAVL(arvore,number);
          
        }
      }
      else break;
  }

  scanf("%d", &number);
  aux = busca(arvore,number);
  
  if(aux != NULL){
    printf("%d,",alturaArvore(aux)-1);
    printf("%d,",altura(aux->esq));
    printf("%d\n",altura(aux->dir));
  }
    else printf("Valor nao encontrado");

  //imprimePreOrdem(arvore);
  return 0;
}
