#include<stdio.h>
int main() {
	int n=6;
	int arr[6];
	int ind=0,temp;
	printf("Enter Array : ");
	for(int i=0; i<n; i++)	scanf("%d", &arr[i]);
	
	for(int i=0; i<n; i++) {
		if(arr[i]!=0) {
			arr[ind++] = arr[i];
		}
	}
	for(int i=ind; i<n; i++)	arr[i]=0;
	for(int i=0; i<6; i++)	printf("%d ",arr[i]);
}