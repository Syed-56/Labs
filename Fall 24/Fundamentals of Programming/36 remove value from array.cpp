#include<stdio.h>
int main() {
	int n,val,count=0,j=0;
	printf("Enter n : ");
	scanf("%d", &n);
	int arr[n];
	printf("Input Array : ");
	for(int i=0; i<n; i++)	scanf("%d", &arr[i]);
	printf("Enter Value to remove : ");
	scanf("%d", &val);
	for(int i=0; i<n; i++) {
		if(arr[i]==val) {
			count++;
		}
	}
	int newArr[n-count];
	for(int i=0; i<n; i++) {
		if(arr[i]==val)	continue;
		newArr[j] = arr[i];
		j++;
	}
	printf("Cleaned Array : ");
	for(int i=0; i<(n-count); i++)	printf("%d ", newArr[i]);
}