#include<stdio.h>
#include<string.h>
int main() {
	char str[50];
	int temp;
	printf("String : ");
	fgets(str,50,stdin);
	str[strcspn(str,"\n")]=0;
	int n=strlen(str);
	char newStr[n];
	strcpy(newStr,str);
	for(int i=0; i<n/2; i++) {
		temp = str[i];
		str[i] = str[n-1-i];
		str[n-1-i] = temp;
	}
	//check for palindrome
	printf("Reverse : %s\n", str);
	if(strcmp(str,newStr)==0)	printf("Palindrome");
	else	printf("No");
}