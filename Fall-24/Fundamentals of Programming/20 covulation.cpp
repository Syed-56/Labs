#include<stdio.h>
int calcAns(int arr[][5], int filter[][3], int i, int j) {
	int ans=0;
	for(int m=0; m<3; m++) {
		for(int n=0; n<3; n++) {
			ans += arr[m+i][n+j] * filter[m][n];
		}
	}
	return ans;
}
int main() {
	int arr[5][5] = {
		{1,2,3,4,5},
		{5,6,7,8,9},
		{1,3,5,7,9},
		{2,4,6,8,0},
		{1,0,1,0,1}
	};
	int filter[3][3] = {
		{1,0,1},
		{0,1,0},
		{1,0,1}
	};
	int result[3][3];
	
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			result[i][j] = calcAns(arr,filter,i,j);
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}
}