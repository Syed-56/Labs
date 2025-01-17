#include<stdio.h>
void printSpace(int i) {
	if(i==0) {
		printf("\nEconomy");
			for(int j=0; j<17; j++)	printf(" ");
		}
	if(i==1) {
		printf("\nFirst Class");
		for(int j=0; j<13; j++)	printf(" ");
	}
	if(i==2) {
		printf("\nExecutive");
		for(int j=0; j<15; j++)	printf(" ");
	}
	if(i==3) {
		printf("\nBusiness Class");
		for(int j=0; j<10; j++)	printf(" ");
	}
}
void printSeats(int seats[][10]) {
	printf("Seat Class | Seat Num\t");
	for(int i=1; i<=10; i++)	printf("%c ", i+64);
	printf("\n");
	for(int i=0; i<4; i++) {
		printSpace(i);
		for(int j=0; j<10; j++) {
			printf("%d ", seats[i][j]);
		}
		printf("\n");
	}
}
int main() {
	int seats[4][10] = {0};
	printSeats(seats);
	char Class[20];
	int num;
	for(int i=0; i<40; i++) {
		printf("Enter Class : ");
		fgets(Class, 20, stdin);
		printf("Enter Num : ");
		scanf("%d", &num);
	}
}