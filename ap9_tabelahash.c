/* Programa: AP9 - Tabela Hash
   Autor: Gustavo Henrique Tavares Isobe - RA: 158552
   Versao: 2.0 - 02/06/2023 - 19:34h
*/
 
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ###################### Funcoes para o Tratamento de Colisoes (DUPLO MAPEAMENTO) ##############

int h1(int k, int m)
{
    return k % m ;
}

int h2(int k, int m)
{
    return 1 + (k % (m - 1)) ; ;
}

int f_transformacao(int k, int m, int i)
{
    return ((h1(k, m) + i * h2(k, m)) % m) ;
}

// ###################### Funcoes e Procedimentos do programa ##############

void start()
{
    int m ; //numero primo que reprsenta o tamanho da tabela
    scanf ("%d", &m) ;
    int chave, i = 0 ;
    int *hash ; //implementacao da tabela hash utilizando um vetor simples
    
    hash = malloc(m * sizeof(int)) ; //alocando M memoria no vetor
    inicializarTabela(hash, m) ; //inicializzando tabela com valores nulos
    
    while(scanf("%d", &chave) != -1)
    {
        if (chave == -1)
            break ;
        inserir(hash, m, chave) ;
    }
    scanf ("%d", &chave) ;
    i = busca(hash, m, chave) ;
    if (i == -1) //caso a busca seja mal sucedida
    {
        printf ("Valor nao encontrado\n") ;
    }
    //int x = remover(hash, m, 2) ; //basta descomentar para testar a funcao
    imprimir(hash, m, chave) ;
    return 0 ;
}

void inicializarTabela(int hash[], int m)
{
    int i ;
    for(i = 0 ; i < m ; i++)
        hash[i] = -1 ; // -1 representa indice vago
}

void inserir(int hash[], int m, int chave)
{
    int i = 0 ;
    int aux = f_transformacao(chave, m, i) ;
    while(hash[aux] != -1) //tratando a colisao
    {
        i += 1 ;
        aux = f_transformacao(chave, m, i) ;
    }
    hash[aux] = chave;
}

int remover(int hash[], int m, int chave)
{
    int i = 0 ;
    int aux = f_transformacao(chave, m, i) ;
    while(hash[aux] != -1) //checando se o indice nao e nulo
    {
        if (hash[aux] == chave)
        {
            hash[aux] = -1 ;
            return 1 ; //caso haja remocao, retorna 1
        }else //caso haja colisao, a funcao seja executada novamente
            i += 1 ;
            aux = f_transformacao(chave, m, i) ;
    }
    return 0 ;
}

int busca(int hash[], int m, int chave)
{
    int i = 0 ;
    int aux = f_transformacao(chave, m, i) ;
    while(hash[aux] != -1)
    {
        if(hash[aux] == chave) //retorna o indice do elemento caso a busca seja bem sucedida
            return hash[aux] ;
        else
            i += 1 ;
            aux = f_transformacao(aux, m, i) ;
    }
    return -1 ; //caso elemento nao exister na tabela
}

void imprimir(int hash[], int m, int chave)
{
    int i ;
    for(i = 0 ; i < m ; i++)
    {
        if (hash[i] == -1){
            printf("\\ ") ;
        }else 
        if (hash[i] == chave){
            printf ("D ") ;
        }else printf("%d ", hash[i]) ;
    }
}

// ############################ Principal ###################################

int main()
{
    start() ; //troquei a main por essa funcao para utilizar somente variaveis locais
    return 0 ;
}
