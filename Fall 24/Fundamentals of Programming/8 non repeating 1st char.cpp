#include<stdio.h>
#include<string.h>
int main() {
	char str[50];
	printf("Enter String : ");
	fgets(str,50,stdin);
	str[strcspn(str,"\n")]=0;
	int n=strlen(str);
	for(int i=0; i<n; i++) {
		int found=1;
		for(int j=0; j<n; j++) {
			if(i==j)	continue;
			else {
				if(str[i]==str[j]) {
					found=0;
					break;
				}
			}
		}
		if(found) {
			printf("Non repeating 1st character : %c", str[i]);
			return 0;
		}
	}
	printf("No character found");
}