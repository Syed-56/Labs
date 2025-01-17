#include<stdio.h>
#include<stdlib.h>
int main() {
	int n=5;
	int* arr=(int* )malloc(n * sizeof(int));
	printf("Ener Array : ");
	for(int i=0; i<n; i++)	scanf("%d", &arr[i]);
	int elem, ind;
	//adding element
	printf("Enter Element to add : ");
	scanf("%d", &elem);
	printf("Enter Inputting Index : ");
	scanf("%d", &ind);
	arr=(int* )realloc(arr,(n+1)*sizeof(int));
	for(int i=n; i>ind; i--) {
		arr[i] = arr[i-1]; 
	}
	arr[ind] = elem;
	n++;
	for(int i=0; i<n; i++)	printf("%d  ", arr[i]);
	//removing element by index
	printf("\nEnter removing Index : ");
	scanf("%d", &ind);
	arr=(int* )realloc(arr,(n-1)*sizeof(int));
	for(int i=ind; i<n-1; i++) {
		arr[i] = arr[i+1]; 
	}
	n--;
	for(int i=0; i<n; i++)	printf("%d  ", arr[i]);
	//remove by value
	printf("\nEnter Element to remove : ");
	scanf("%d", &elem);
	for(int i=0; i<n; i++) {
		if(arr[i]==elem)	ind=i;
	}
	arr=(int* )realloc(arr,(n-1)*sizeof(int));
	for(int i=ind; i<n-1; i++) {
		arr[i] = arr[i+1]; 
	}
	n--;
	for(int i=0; i<n; i++)	printf("%d  ", arr[i]);
}