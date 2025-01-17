#include<stdio.h>
void sortArray(int size, int arr[]) {
	int temp;
	for(int i=0; i<size-1; i++) {
		for(int j=i+1; j<size; j++) {
			if(arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
double merge(int nums1Size, int nums2Size, int* nums1, int* nums2) {
	int newArr[nums1Size+nums2Size];
	for(int i=0; i<nums1Size; i++) {
		newArr[i] = nums1[i];
	}
	for(int i=0; i<nums2Size; i++) {
		newArr[i+nums1Size] = nums2[i];
	}
	int size=nums1Size+nums2Size;
	sortArray(size,newArr);
	printf("\nMerged Sorted Array : ");
	for(int i=0; i<size; i++)	printf("%d ", newArr[i]);
	double median;
	if(size%2==0) {
		median = newArr[size/2] + newArr[(size/2)-1];
		median /= 2.0;
		return median;
	}
	else {
		size--;
		median = newArr[size/2];
		return median;
	}
}

int main() {
	int m,n;
	printf("Enter m & n : ");
	scanf("%d %d", &m, &n);
	int nums1[m], nums2[n];
	printf("Enter Nums1 : ");
	for(int i=0; i<m; i++)	scanf("%d", &nums1[i]);
	printf("Enter Nums2 : ");
	for(int i=0; i<n; i++)	scanf("%d", &nums2[i]);

	printf("\nSorted Array 1 : ");
	for(int i=0; i<m; i++)	printf("%d ", nums1[i]);
	printf("\nSorted Array 2 : ");
	for(int i=0; i<n; i++)	printf("%d ", nums2[i]);
	
	double x = merge(m,n,nums1,nums2);
	printf("\nMedian : %.2f", x);
}