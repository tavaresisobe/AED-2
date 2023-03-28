/* Programa: AP1 - Recursão
   Autor: Gustavo Henrique Tavares Isobe
   Versao: 1.0 - 28/03/2023 - 02:23h
*/
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ###################### Funcoes e Procedimentos do programa ##############

void start()
{
    int i, n, num ;
    scanf ("%d", &n) ;
    int *vet, *count = 0 ;
    vet = malloc (n * sizeof(int)) ;
    for (i = 0 ; i < n ; i++)
    {
        scanf ("%d", &vet[i]) ;
    }
    scanf ("%d", &num) ;
    int x = buscabin(vet, &count, 0, n-1, num) ;
    if (x == 0)
        printf ("%d nao foi encontrado\n", num) ;
    else
        printf ("%d\n", count) ;
    free(vet) ;
}

int buscabin(int *vet, int *c, int minimo, int maximo, int num)
{
    if (maximo >= minimo)
    {
        int aux = minimo + (maximo - minimo)/2 ;
        if (vet[aux] == num) 
            return aux ;
        if (vet[aux] > num)
        {
            *c += 1 ;
            return buscabin(vet, c, minimo, aux-1, num) ;
        }else
            *c += 1 ;
            return buscabin(vet, c, aux+1, maximo, num) ;
    }
    return 0 ;
}

// ############################ Principal ###################################

int main(void)
{
    start() ;
    return 0 ;
}
