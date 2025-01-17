#include<stdio.h>
int main() {
	int n;
	printf("Enter n : ");
	scanf("%d", &n);
	int arr[n][n];
	int store[n][n];
	for(int i=0; i<n; i++) {
		printf("Enter Row %d : ", i+1);
		for(int j=0; j<n; j++) {
			scanf("%d", &arr[i][j]);
			store[i][j] = arr[i][j];
		}
	}
	int temp;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(i==j)	continue;
			arr[i][j] = store[j][i];
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}