#include<stdio.h>
#include<string.h>
static int i=0;
char* reverse(int n, char str[]) {
	if(i>=n/2)	return str;
	char temp = str[i];
	str[i] = str[n-i-1];
	str[n-i-1] = temp;
	i++;
	return reverse(n,str);
}
int main() {
	char str[100];
	printf("Enter String : ");
	fgets(str,50,stdin);
	str[strcspn(str,"\n")]=0;
	int n = strlen(str);
	reverse(n,str);
	printf("\nReversed : %s", str);
}