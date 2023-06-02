#include <stdio.h>
#include <stdlib.h>

void inicializarTabela(int t[], int m)
{
    int i ;
    for(i = 0 ; i < m ; i++)
        t[i] = 0 ;
}

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

void inserir(int t[], int m, int valor)
{
    int i = 0 ;
    int id = f_transformacao(valor, m, i) ;
    while(t[id] != 0) //tratando a colisao
    {
        i += 1 ;
        id = f_transformacao(valor, m, i);
    }
    t[id] = valor;
}

int busca(int t[], int m, int chave)
{
    int i = 0 ;
    int id = f_transformacao(chave, m, i) ;
    while(t[id] != 0)
    {
        if(t[id] == chave)
            return t[id] ;
        else
            i += 1 ;
            id = f_transformacao(id, m, i) ;
    }
    return -1 ;
}

void imprimir(int t[], int m, int valor)
{
    int i ;
    for(i = 0 ; i < m ; i++)
    {
        if (t[i] == 0){
            printf("\\ ") ;
        }else 
        if (t[i] == valor){
            printf ("D ") ;
        }else printf("%d ", t[i]) ;
    }
}

int main()
{
    int m ;
    scanf ("%d", &m) ;
    int valor, i = 0 ;
    int tabela[m] ;
    inicializarTabela(tabela, m) ;
    while(scanf("%d", &valor) != -1)
    {
        if (valor == -1)
            break ;
        inserir(tabela, m, valor) ;
    }
    scanf ("%d", &valor) ;
    i = busca(tabela, m, valor) ;
    if (i == -1)
    {
        printf ("Valor nao encontrado\n") ;
    }
    imprimir(tabela, m, valor) ;
    return 0 ;
}