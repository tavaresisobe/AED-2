#include <stdio.h>
#include <stdlib.h> // srand, rand
#include <time.h> // time


void start ()
{
    int tam_vet, i ;
    int *vet, *vet2 ;
    scanf ("%d", &tam_vet) ;
    vet = malloc (tam_vet * sizeof(int)) ;
    for (i = 0 ; i < tam_vet ; i++)
    {
        scanf ("%d", &vet[i]) ;
    }
    vet2 = malloc (tam_vet * sizeof(vet)) ;
    for (i = 0 ; i < tam_vet ; i++) //copiando vetor para implementação do quicksort utiliziando a mediana
    {
        vet2[i] = vet[i] ;
    }
    
    
//	srand(time(NULL));
	quick_sort(vet, 0, tam_vet - 1);
	quick_sort(vet2, 0, tam_vet - 1);
	
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet[i]);
	printf ("\n\n") ;
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet2[i]);
}

// função que realiza a troca entre dois elementos
void troca(int vet[], int i, int j)
{
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

// particiona e retorna o índice do pivô
int particiona(int vet[], int inicio, int fim)
{
	int pivo, pivo_indice, i;
	
	pivo = vet[fim]; // o pivô é sempre o último elemento
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		// verifica se o elemento é <= ao pivô
		if(vet[i] <= pivo)
		{
			// realiza a troca
			troca(vet, i, pivo_indice);
			// incrementa o pivo_indice
			pivo_indice++;
		}
	}
	
	// troca o pivô
	troca(vet, pivo_indice, fim);
	
	// retorna o índice do pivô
	return pivo_indice;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(int vet[], int inicio, int fim)
{
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	troca(vet, pivo_indice, fim);
	// chama a particiona
	return particiona(vet, inicio, fim);
}

void quick_sort(int vet[], int inicio, int fim)
{
	if(inicio < fim)
	{
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(vet, inicio, fim);
		
		// chamadas recursivas quick_sort
		quick_sort(vet, inicio, pivo_indice - 1);
		quick_sort(vet, pivo_indice + 1, fim);
	}
}

int main()
{
    start() ;
	// vetor que será ordenado
	int vet[] = {19, 42, 20, 57, 53};
	int tam_vet = sizeof(vet) / sizeof(int);
	int i;
	
	// inicializa random seed
	srand(time(NULL));
	 
	// chamada do quicksort
	quick_sort(vet, 0, tam_vet - 1);

	// mostra o vetor ordenado
	return 0; 
}
/*
#include <stdio.h>
#include <stdlib.h> // srand, rand
#include <time.h> // time


void start ()
{
    int vet[] = {19, 42, 20, 57, 53};
	int tam_vet = sizeof(vet) / sizeof(int);
	int i;
	srand(time(NULL));
	quick_sort(vet, 0, tam_vet - 1);
	
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet[i]);
}

// função que realiza a troca entre dois elementos
void troca(int vet[], int i, int j)
{
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

// particiona e retorna o índice do pivô
int particiona(int vet[], int inicio, int fim)
{
	int pivo, pivo_indice, i;
	
	pivo = vet[fim]; // o pivô é sempre o último elemento
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		// verifica se o elemento é <= ao pivô
		if(vet[i] <= pivo)
		{
			// realiza a troca
			troca(vet, i, pivo_indice);
			// incrementa o pivo_indice
			pivo_indice++;
		}
	}
	
	// troca o pivô
	troca(vet, pivo_indice, fim);
	
	// retorna o índice do pivô
	return pivo_indice;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(int vet[], int inicio, int fim)
{
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	troca(vet, pivo_indice, fim);
	// chama a particiona
	return particiona(vet, inicio, fim);
}

void quick_sort(int vet[], int inicio, int fim)
{
	if(inicio < fim)
	{
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(vet, inicio, fim);
		
		// chamadas recursivas quick_sort
		quick_sort(vet, inicio, pivo_indice - 1);
		quick_sort(vet, pivo_indice + 1, fim);
	}
}

int main()
{
    start() ;
	// vetor que será ordenado
	int vet[] = {19, 42, 20, 57, 53};
	int tam_vet = sizeof(vet) / sizeof(int);
	int i;
	
	// inicializa random seed
	srand(time(NULL));
	 
	// chamada do quicksort
	quick_sort(vet, 0, tam_vet - 1);

	// mostra o vetor ordenado
	return 0; 
}*/
