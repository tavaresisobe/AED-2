#include <stdio.h>
#include <malloc.h>
#include <limits.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

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
}

int partition2(int* array,int p, int r){
  int pivoh; //pivo nesse caso eh o ultimo elemento do array;
  int mid;
  int i = p-1;
    mid = ((r+p+1)/2);

     if(array[p] < array[mid] && array[p] > array[r]) swap(&array[p],&array[r]);
     if(array[p] < array[r] && array[p] > array[mid]) swap(&array[p],&array[r]);
     if(array[mid] < array[p] && array[mid] > array[r]) swap(&array[mid],&array[r]);
     if(array[mid] < array[r] && array[mid] > array[p]) swap(&array[mid],&array[r]);
     if(array[r] < array[p] && array[r] > array[mid]) pivoh = array[r];
     if(array[r] < array[mid] && array[r] > array[p]) pivoh = array[r];
     
    pivoh = array[r];
  
    for(int j = p; j<=r-1; j++){
      if(array[j] <= pivoh){
        i++;
        swap(&array[j],&array[i]);
      }
    }
  swap(&array[i+1], &array[r]);
      
  return i+1;
}

void quickSort2(int* A,int p,int r,int contador,int* min,int* max){
  if(p<r){
  int q = partition2(A,p,r);
  quickSort2(A,p,q-1,contador+1,min,max);
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
   array2 = (int *)malloc(sizeof(int)*n);   //19 42 20 57 53
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