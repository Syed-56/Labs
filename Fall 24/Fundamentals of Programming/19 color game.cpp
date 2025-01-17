#include<stdio.h>
#include<string.h>
int main() {
	char color[50];
	printf("Colors : ");
	scanf("%s", &color);
	int n=strlen(color);
	char name1[] = "Sultan";
	char name2[] = "Taha";
	int move,winner=0,win,i;
	for(i=0; winner==0; i++) {
		for(int j=1; j<n-1; j++) {
			if(color[j-1]==color[j] && color[j]==color[j+1]) {
				if(i%2==0 && color[j] == 'y')	winner=0;
				else if(i%2!=0 && color[j] == 'b')	winner=0;
				break;
			}
			else	winner=1;
		}
		if(winner==1)	break;
		if(i%2==0)	printf("%s Move : ", name1);
		else	printf("%s Move : ", name2);
		scanf("%d", &move);
		while(i%2==0 && color[move] != 'y') {
			printf("Wrong Move\nDo Correct : ");
			scanf("%d", &move);
		}
	
		color[move] = ' ';
		for(int i=move; i<n-1; i++) {
			color[i] = color[i+1];
		}
		n--;
		color[n] = '\0';
		puts(color);
	}
	if(i%2==0)	printf("Winner = %s", name2);
	else	printf("Winner = %s", name1);
}