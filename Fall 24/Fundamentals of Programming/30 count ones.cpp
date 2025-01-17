#include <stdio.h>
#include <stdlib.h>
static int ones=0;
int countOnes(int m, int n, int **arr, int i, int j) {
	if(i==m)	return ones;
	if(arr[i][j]==1)	ones++;
	if(j==n) 	return countOnes(m,n,arr,i+1,0);
	return countOnes(m,n,arr,i,j+1);
}
int main() {
    int m, n;
    printf("Enter the dimensions (m n): ");
    scanf("%d %d", &m, &n);
    int **arr = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        arr[i] = (int *)malloc(n * sizeof(int));
    }
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    printf("The matrix is:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    int i=0,j=0;
    printf("No. of Ones : %d", countOnes(m,n,arr,i,j));
    for (int i = 0; i < m; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}