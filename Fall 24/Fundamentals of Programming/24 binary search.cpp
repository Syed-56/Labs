#include<stdio.h>
int binarySearch(int n, int arr[], int target) {
	int min=0, max=n-1;
	while(min<=max) {
		int mid = min + (max-min)/2;
		if(arr[mid]==target)	return mid;
		else if(arr[mid]<=target)	min = mid+1;
		else	max = mid-1;
	}
	return -1;
}
int main() {
	int arr[] = {0,2,3,5,6,7,9};
	int n = sizeof(arr)/sizeof(arr[0]);
	int target;
	printf("Enter Target : ");
	scanf("%d", &target);
	int result = binarySearch(n,arr,target);
	if(result==-1)	printf("Not Found");
	else	printf("Element Found at Index %d", result);
}