#include<stdio.h>
int findMaxLegnth(int arr[], int n, int target) {
	int sum,legnth,maxL=0;
	for(int i=0; i<n; i++) {
		sum=0;
		for(int j=i; j<n; j++) {
			sum += arr[j];
			if(sum==target) {
				legnth = j-i+1;
				if(legnth > maxL)	maxL = legnth;
			}
		}
	}
	return maxL;
}
int main() {
	int arr[] = {1,3,5,3,2};
	int n = sizeof(arr)/sizeof(arr[0]);
	printf("Enter Target : ");
	int target;
	scanf("%d", &target);
	int x=findMaxLegnth(arr,n,target);
	printf("Max Legnth : %d", x);
}