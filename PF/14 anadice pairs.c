#include<stdio.h>
int main() {
	int a,b;
	int sumA=0, sumB=0;
	printf("Enter a & b : ");
	scanf("%d %d", &a, &b);
	for(int i=2; i<=a/2; i++) {
		if(a%i==0)	sumA += i;
	}
	for(int i=2; i<=b/2; i++) {
		if(b%i==0)	sumB += i;
	}
	printf("Sum of factors of a = %d\nSum of factors of b = %d\n", sumA, sumB);
	if(sumA==b && sumB==a)	printf("Anadice Pairs");
	else	printf("Not Anadice Pairs");
}