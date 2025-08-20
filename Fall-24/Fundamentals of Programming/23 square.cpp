#include<stdio.h>
int main() {
	int n;
	printf("Enter n : ");
	scanf("%d", &n);
	int max=(n*2)-1;
	for(int i=0; i<=max; i++) {
		printf("\n"); 
		for(int j=0; j<=max; j++) {
			if(i==0 || j==0 || i==max || j==max)	printf("%d ", n);
			else	printf("  ");
		}
	}
}