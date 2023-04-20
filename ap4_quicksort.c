#include <stdio.h>
#include <stdlib.h>

//https://replit.com/@Ramanujaann/AED-2-QuickSort?s=app
//https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/quick.html

void troca(int *a, int *b)
{
    int t = *a ;
    *a = *b ;
    *b = t ;
}

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
    printf ("Vet 1:") ;
    quick_sort1(vet, 0, tam_vet - 1, 0);
    printf("\nVet 2:\n") ;
    quick_sort2(vet2, 0, tam_vet - 1, 0);
	
	for(i = 0; i < tam_vet; i++) //print para auxiliar
	    printf("%d ", vet[i]);
	printf ("\n\n") ;
	for(i = 0; i < tam_vet; i++)
	    printf("%d ", vet2[i]);
}

int divide(int vet[], int p, int r)
{
    int pivo = vet[r];
    int i = (p - 1);
    printf ("\npivo = %d\n", pivo) ;
    for (int k = p; k <= r ; k++)
    {
        printf ("%d ", vet[k]) ;
    }
    for (int j = p ; j < r ; j++)
    {
        if (vet[j] < pivo)
        {
            troca(&vet[++i], &vet[j]);
        }
    }
    troca(&vet[i + 1], &vet[r]);
    printf ("\n") ;
    for (int k = p; k <= r ; k++)
    {
        printf ("%d ", vet[k]) ;
    }
    printf ("\n");
    return (i + 1);
}

int mediana(int vet[], int p, int r)
{
    int pivo ;
    int mid = (p + (r+1))/ 2 ;
    
    if (vet[mid] < vet[p]) 
        troca(&vet[mid], &vet[p]) ;
    
    if (vet[r] < vet[p])
        troca(&vet[r], &vet[p]) ;
    
    if (vet[r] < vet[mid])
        troca(&vet[r], &vet[mid]) ;
    
    troca(&vet[mid], &vet[r-1]) ;
    pivo = vet[r-1] ;
    
    return divide(vet, p, r);
}

void quick_sort1(int vet[], int p, int r, int count)
{
    if (p < r) 
    {
        int pi = divide(vet, p, r);
        //ordenando :
        quick_sort1(vet, p, pi - 1, count+1) ; //elementos a esquerda do pivo
        quick_sort1(vet, pi + 1, r, count+1) ; //elementos a direita do pivo
    }
   // else{ 
   //     printf("%d\n", count) ;
   // }
}

void quick_sort2(int vet[], int p, int r, int count)
{
    if (p < r) 
    {
        int pi = mediana(vet, p, r);
        //ordenando :
        quick_sort1(vet, p, pi - 1, count+1) ; //elementos a esquerda do pivo
        quick_sort1(vet, pi + 1, r, count+1) ; //elementos a direita do pivo
    }
}
int main()
{
    start() ;
    return 0; 
}
/*
int partition(int* A,int p, int r){
  int pivoh = A[r]; //pivo nesse caso eh o ultimo elemento do array;
  int i = p-1;
  int temp;
    for(int j = p; j<=r-1; j++){
      if(A[j] <= pivoh){
        i++;
        swap(&A[j],&A[i]);
      }
    }
  swap(&A[i+1], &A[r]);
      
  return i+1;
}

void quickSort(int* A,int p,int r, int contador, int* min, int* max){
  if(p<r){
  int q = partition(A,p,r);
  quickSort(A,p,q-1,contador+1, min, max);
  quickSort(A,q+1,r,contador+1, min, max);
  }  
  else{
    if(contador < *min) *min = contador;
    if(contador > *max) *max = contador;
  }
}*/

/*
☰

68

69

70

71

72

73

74

75

76

77

78

79

80

81

82

83

84

85

86

87

88

89

90

91

92

93

94

95

96

97

98

99

100

#include <stdio.h>

quickSort2(A,q+1,r,contador+1,min,max);

} 

else{

if(contador < *min) *min = contador;

if(contador > *max) *max = contador;

}

}




int main(void) {

int *array,*array2;

int n, min = INT_MAX, max = INT_MIN, min2 = INT_MAX, max2 = INT_MIN;

scanf("%d",&n);

array = (int *)malloc(sizeof(int)*n);

for(int i=0; i<n; i++){

scanf("%d",array+i);

}

array2 = (int *)malloc(sizeof(int)*n); //19 42 20 57 53

for(int i=0; i<n; i++){ 

array2[i] = array[i];

}

quickSort(array,0,n-1,0,&min,&max);

quickSort2(array2,0,n-1,0,&min2,&max2);

//for(int i=0; i<n ; i++) printf("%d ",array2[i]);

printf("%d",max - min);

printf("\n%d",max2 - min2);

return 0;

}


*/
