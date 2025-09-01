#include<stdio.h>
void printGrid(char arr[][12]) {
	for(int i=0; i<12; i++) {
		printf("\n\t\t");
		for(int j=0; j<12; j++) {
			printf("%c  ", arr[i][j]);
		}
		printf("\n");
	}
}
int main() {
	char arr[12][12] = {
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
		{'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
		{'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
		{'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
		{'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
		{'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
		{'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
		{'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
		{'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
		{'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
		{'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '*'}
	};
	char temp = arr[1][1];
	char x = 'x';
	int i=0, j=0;
	arr[1][1] = x;
	char move;
	printf("W = up, S = down, A = left, D = right\n");
	while(1) {
		if(arr[i][j]=='*') {
			printf("You Won");
			break;
		}
		printGrid(arr);
		printf("Enter Move : ");
		scanf(" %c", &move);
		if(move=='W') {
			if((arr[i-1][j])!='.') {
				printf("Cant Move, Enter again : ");
				scanf(" %c", &move);
			}
			temp = arr[i][j];
			i--;
			arr[i][j] = x;
			arr[i-1][j] = temp;
		}
		if(move=='A') {
			if((arr[i][j-1])!='.') {
				printf("Cant Move, Enter again : ");
				scanf(" %c", &move);
			}
			temp = arr[i][j];
			j--;
			arr[i][j] = x;
			arr[i][j-1] = temp;
		}
		if(move=='S') {
			if((arr[i+1][j])!='.') {
				printf("Cant Move, Enter again : ");
				scanf(" %c", &move);
			}
			temp = arr[i][j];
			i++;
			arr[i][j] = x;
			arr[i+1][j] = temp;
		}
		if(move=='D') {
			if((arr[i][j+1])!='.') {
				printf("Cant Move, Enter again : ");
				scanf(" %c", &move);
			}
			temp = arr[i][j];
			j++;
			arr[i][j] = x;
			arr[i][j+1] = temp;
		}
	}
}