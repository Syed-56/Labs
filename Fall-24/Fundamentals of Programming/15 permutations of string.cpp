#include<stdio.h>
#include<string.h>
int fact(int n) {
	int Fact=1;
	for(int i=1; i<=n; i++) {
		Fact *= i;
	}
	return Fact;
}
int main() {
	char str[10];
	printf("Enter String : ");
	scanf("%s", &str);
	int n=strlen(str);
	int l = fact(n);
	printf("Possible Permutations : %d", l);
}