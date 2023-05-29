/* Programa: AP8 - Arvore AVL x Arvore RN
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 3.0 - 28/05/2023 - 15:15h
*/
 
// ##################### Bibliotecas Externas ##############################
	
#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

struct tipoABB_RN{ //Arvore Rubro Negra
    int chave ;
	struct tipoABB_RN* pai ; // noh pai
	struct tipoABB_RN* esq ;
	struct tipoABB_RN* dir ;
	int cor ; // 0 - Negra, 1 - Rubro
};

//ponteiro para a raiz
struct tipoABB_RN* root = NULL;

// ###################### Funcoes e Procedimentos do programa - ABB RED BLACK ##############

//retorna maior valor entre de 2 elementos
int max(int a, int b)
{
  if(a > b)
    return a;
  else
    return b;
}

//rotacao para a esquerda:
void rotacionaDir(struct tipoABB_RN* aux)
{
	struct tipoABB_RN* esquerda = aux->esq ;
	aux->esq = esquerda->dir ;
	if (aux->esq)
		aux->esq->pai = aux ;
	esquerda->pai = aux->pai ;
	if (!aux->pai)
	{
		root = esquerda ;
	}else if (aux == aux->pai->esq)
	{
		aux->pai->esq = esquerda ;
	}else
		aux->pai->dir = esquerda ;
	esquerda->dir = aux ;
	aux->pai = esquerda ;
}

//rotacao para a direita
void rotacionaEsq(struct tipoABB_RN* aux)
{
	struct tipoABB_RN* direita = aux->dir ;
	aux->dir = direita->esq ;
	if (aux->dir)
		aux->dir->pai = aux ;
	direita->pai = aux->pai ;
	if (!aux->pai)
	{
		root = direita ;
	}else if (aux == aux->pai->esq){
		aux->pai->esq = direita ;
	}else
		aux->pai->dir = direita ;
	direita->esq = aux ;
	aux->pai = direita ;
}

//busca o No, onde sera inserido o no folha
struct tipoABB_RN* buscaPai(struct tipoABB_RN* raiz, 
                                struct tipoABB_RN* aux)
{
	//caso AbbRN estiver vazia
	if (raiz == NULL)
		return aux ;

	if (aux->chave < raiz->chave)
	{
		raiz->esq = buscaPai(raiz->esq, aux) ;
		raiz->esq->pai = raiz ;
	}
	else if (aux->chave > raiz->chave)
	{
		raiz->dir = buscaPai(raiz->dir, aux) ;
		raiz->dir->pai = raiz ;
	}
	return raiz ;
}

struct tipoABB_RN* criaNo(int chave)
{
    struct tipoABB_RN* aux
			= (struct tipoABB_RN*)malloc(sizeof(struct tipoABB_RN)) ;
	if (aux)
	{
		aux->esq = NULL ;
		aux->dir = NULL ;
		aux->pai = NULL ;
		aux->chave = chave ;
		aux->cor = 1 ;
	}else
	    printf ("Erro ao alocar memoria\n") ;
	return aux ;
}

void insereABBRubroNegra(int chave, int *mudacor, int *rotate)
{
    struct tipoABB_RN* temp = criaNo(chave) ;
    if (temp)
    {
        //insere o novo noh, e retorna seu rrespectivo no pai
		root = buscaPai(root, temp) ;
		fixup(root, temp, mudacor, rotate) ;
		root->cor = 0 ;
    }
}

//funcao para concertar desbalanceamento causado pela insercao
void fixup(struct tipoABB_RN* raiz, struct tipoABB_RN* aux, 
            int *mudacor, int *rotate)
{
	struct tipoABB_RN* pai = NULL ;
	struct tipoABB_RN* avo = NULL ;

	while ((aux != raiz) && (aux->cor != 0)
		&& (aux->pai->cor == 1))
	{
		pai = aux->pai ;
		avo = aux->pai->pai ;
		
		//rotacoes para esquerda:
		if (pai == avo->esq)
		{
			struct tipoABB_RN* tio_esq_aux = avo->dir ;
			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if (tio_esq_aux != NULL && tio_esq_aux->cor == 1)
			{
			    if (avo->cor != 1)
			    {
			        avo->cor = 1 ;
			        *mudacor += 1 ;
			    }
			    if (pai->cor != 0)
			    {
				    pai->cor = 0 ;
				    *mudacor += 1 ;
				}
				if (tio_esq_aux->cor != 0)
				{
				    tio_esq_aux->cor = 0 ;
				    *mudacor += 1 ;
				}
				aux = avo ;
			}

			else{
				/* Case : 2
					pt is right child of its parent
					Left-rotation required */
				if (aux == pai->dir)
				{
					rotacionaEsq(pai) ;
					*rotate += 1 ;
					aux = pai ;
					pai = aux->pai ;
				}

				/* Case : 3
					pt is left child of its parent
					Right-rotation required */
			    rotacionaDir(avo) ;
			    *rotate += 1 ;
				int t = pai->cor ;
				if (pai->cor != avo->cor)
				{
				    pai->cor = avo->cor ;
				    *mudacor += 1 ;
				}
				if (avo->cor != t)
				{
				    avo->cor = t ;
				    *mudacor += 1 ;
				}
				aux = pai ;
			}
		}

		//rotacoes para direita:
		else {
			struct tipoABB_RN* tio_dir_aux = avo->esq ;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((tio_dir_aux != NULL) && (tio_dir_aux->cor == 1))
			{
			    if (avo->cor != 1)
			    {
			        avo->cor =  1 ;
			        *mudacor += 1 ;
				}
				if (pai->cor != 0)
				{
				    pai->cor = 0 ;
				    *mudacor += 1 ;
				}
				if(tio_dir_aux->cor != 0)
				{
				    tio_dir_aux->cor = 0 ;
				    *mudacor += 1 ;
				}
				aux = avo ;
			}
			else{
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (aux == pai->esq)
				{
					rotacionaDir(pai) ;
					*rotate += 1 ;
					aux = pai ;
					pai = aux->pai ;
				}

				/* Case : 3
					pt is right child of its parent
					Left-rotation required */
				rotacionaEsq(avo) ;
				*rotate += 1 ;
				int t = pai->cor ;
				if (pai->cor != avo->cor)
				{
				    pai->cor = avo->cor ;
				    *mudacor += 1 ;
				}
				if (avo->cor != t)
				{
				    avo->cor = t ;
				    *mudacor += 1 ;
				}
				aux = pai ;
			}
		}
	}
}

int alturaNoPreto(struct tipoABB_RN* aux, int *count)
{
    if (aux != NULL && aux->cor == 0)
        *count += 1 ;
    if (aux->dir != NULL && aux->dir->cor == 0)
        alturaNoPreto(aux->dir, count) ;
    if (aux->esq != NULL && aux->esq->cor == 0)
        alturaNoPreto(aux->esq, count) ;
    return *count ;
}

//funcao para calcular altura da AbbRN
int alturaRN(struct tipoABB_RN* aux)
{
        if(aux == NULL)
            return 0 ;
        else
            return 1 + max(alturaRN(aux->esq), alturaRN(aux->dir)) ;
}

void preordem(struct tipoABB_RN* aux)
{
    if (aux!= NULL)
        printf("%d-%d  ", aux->chave, aux->cor) ;
    if (aux->dir != NULL)
        preordem(aux->dir) ;
    if (aux->esq != NULL)
        preordem(aux->esq) ;
}

int main()
{
	int i = 0, j, n ;
    int vet[20] ;
	scanf ("%d", &n) ;
    while (n != -1)
    {
        vet[i] = n ;
        scanf ("%d", &n) ;
        i++ ;
    }
    int mudacor = 0, rotate = 0, c_esq = 0, c_dir = 0 ;
	for (j = 0 ; j < i ; j++)
	{
	    insereABBRubroNegra(vet[j], &mudacor, &rotate) ;
	}
	//preordem(root) ;
	printf ("%d,%d,%d\n", alturaRN(root)-1, alturaRN(root->esq),
	                alturaRN(root->dir)) ;
    printf ("%d\n", max(alturaNoPreto(root->dir, &c_dir), alturaNoPreto(root->esq, &c_esq))) ;
	printf ("%d,%d\n", mudacor, rotate) ;
	return 0 ;
}
