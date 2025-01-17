#include<stdio.h>
int main() {
	int n=5;
	int arr[n] = {1,2,3,4,5};
	int temp;
	for(int i=0; i<n/2; i++) {
		temp = arr[n-1-i];
		arr[n-1-i] = arr[i];
		arr[i] = temp;
	}
	for(int i=0; i<n; i++)	printf("%d  ", arr[i]);
}