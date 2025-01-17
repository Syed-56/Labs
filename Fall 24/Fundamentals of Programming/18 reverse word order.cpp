#include<stdio.h>
#include<string.h>
char* reverseOrder(int n, char str[], int len, char word[]) {
	int counter=1;
	for(int i=1; str[i] != ' '; i++) {
		word[i] = str[i];
		counter++;
	}
	for(int i=0; i<n-counter; i++) {
		str[i] = str[counter+i];
	}
	int j=0;
	for(int i=n-counter; i<n; i++) {
		str[i] = word[j];
		j++;
	}
	return str;
}
int main() {
	char str[100];
	printf("Enter String : ");
	fgets(str,50,stdin);
	str[strcspn(str,"\n")]=0;
	int n = strlen(str);
	char word[10];
	int len = strlen(word);
	reverseOrder(n,str,len,word);
	printf("\nOrder Reversed : %s", str);
}