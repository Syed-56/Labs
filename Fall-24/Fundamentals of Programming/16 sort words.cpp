#include<stdio.h>
#include<string.h>
int main() {
	char str[50], word[20];
	char temp;
	printf("Enter String : ");
	fgets(str,50,stdin);
	str[strcspn(str,"\n")]=0;
	printf("Enter Word : ");
	scanf("%s", &word);
	int n = strlen(str);

	//ascending order
	for(int i=0; i<n-1; i++) {
		for(int j=0; j<n-1-i; j++) {
			if(str[j] > str[j+1]) {
				temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
		}
	}
	puts(str);
	//descending order
	for(int i=0; i<n-1; i++) {
		for(int j=0; j<n-1-i; j++) {
			if(str[j] < str[j+1]) {
				temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
		}
	}
	puts(str);
}