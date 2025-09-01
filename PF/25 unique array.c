#include<stdio.h>
int main() {
	int arr[] = {1,2,3,4,5,6,7,8,9,0,2,4,5};
	int n = sizeof(arr)/sizeof(arr[0]);
	for(int i=0; i<n; i++)	printf("%d ", arr[i]);
	printf("\nUnique : ");
	for(int i=0; i<n; i++) {
		int found=0;
		for(int j=0; j<n; j++) {
			if(i==j)	continue;
			if(arr[i]==arr[j]) found=1;
		}
		if(!found)	printf("%d ",arr[i]);
	}
}