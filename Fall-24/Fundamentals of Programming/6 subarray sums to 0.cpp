#include<stdio.h>
int main() {
	int n=5;
	int arr[n];
	printf("Enter Array : ");
	for(int i=0; i<n; i++)	scanf("%d", &arr[i]);
	for(int i=0; i<n; i++) {
		int sum=0;
		for(int j=0; j<n; j++) {
			sum += arr[j];
			if(sum==0) {
				printf("True");
				return 0;
			}
		}
	}
	printf("False");
}