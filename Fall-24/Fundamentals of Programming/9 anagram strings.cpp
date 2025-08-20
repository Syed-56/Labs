#include<stdio.h>
#include<string.h>
int main() {
	char str1[50];
	printf("Enter String : ");
	fgets(str1,50,stdin);
	str1[strcspn(str1,"\n")]=0;
	int n1=strlen(str1);
	char str2[50];
	printf("Enter String : ");
	fgets(str2,50,stdin);
	str2[strcspn(str2,"\n")]=0;
	int n2=strlen(str2);
	for(int i=0; i<n1; i++) {
		int anagram=0;
		for(int j=0; j<n2; j++) {
			if(str1[i]==str2[j])	anagram=1;
		}
		if(!anagram) {
			printf("Not Anagram");
			return 0;
		}
	}
	printf("Anagram");
}