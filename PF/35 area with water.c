#include<stdio.h>
int maxArea(int* height, int heightSize) {
    int area, maxArea=0;
    int max=height[0];
    
    for(int i=0; i<heightSize; i++) {
    	for(int j=i+1; j<heightSize; j++) {
    		if(height[j] < height[i])	continue;
    		area = height[i] * j;
    		printf("\nArea : %d x %d = %d", height[i], j, area);
		}
	}
    return area;
}
int main() {
	int heightSize;
	printf("Enter height Size : ");
	scanf("%d", &heightSize);
	int height[heightSize];
	printf("Enter Heights : ");
	for(int i=0; i<heightSize; i++) 	scanf("%d", &height[i]);
	int find = maxArea(height, heightSize);
//	printf("\nMax Area Found : %d", find);
}