# include <stdio.h>
# include <stdlib.h>

# define MAX_INT 32767

void merge(int * A, int p, int q, int r){
  int n1 = q - p + 1;
  int n2 = r - q;

  int * L = malloc((n1 + 1) * sizeof(int));
  int * R = malloc((n2 + 1) * sizeof(int));

  int i = 0;
  int j = 0;

  for(int i = 0; i < n1; i = i + 1){
    L[i] = A[p + i];
  }

  for(int j = 0; j < n2;j = j + 1){
    R[j] = A[q + j];
  }

  L[n1] = MAX_INT;
  R[n2] = MAX_INT;

  i = j = 0;

  for(int k = p; k <= r; k = k + 1){
    if(L[i] < R[j]){
      A[k] = L[i];
      i = i + 1;
    }
    else{
      A[k] = R[j];
      j++;
    }
  }
  free(L);
  free(R);
}


void merge_sort(int * A, int p, int r){
  if(p < r){
    int q = (p + r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q + 1, r);
    merge(A, p, q, r);
  }	
}

int main(){
  int a[10] = [3,3,8,5,2,1974,1950,50,-2000,20,30];

  return 0;
}
