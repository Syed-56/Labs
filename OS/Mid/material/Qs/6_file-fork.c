#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	int num1=10,num2=3,num3=7;
	FILE *fptr = fopen("data.txt","w");
	if(!fptr) {
		printf("Error");
		exit(1);
	}
	fprintf(fptr,"%d %d %d", num1,num2,num3);
	fclose(fptr);

	pid_t pid1 = fork();
	if(pid1<0) {
		printf("Error");
		exit(1);
	}
	else  if(pid1==0) {
		FILE *f1 = fopen("data.txt","r");
		int n1;
		fscanf(f1,"%d",&n1);
		fclose(f1);
		
		int sum=0;
		for(int i=0;i<=n1;i++) {
			sum += i;
		}
		printf("Child1: Sum of Natural nums = %d\n", sum);
		exit(0);
	}
	wait(NULL);

	pid_t pid2 = fork();
        if(pid2<0) {
                printf("Error");
                exit(1);
        }
        else  if(pid2==0) {
		FILE *f2 = fopen("data.txt","r");
		int n2;
		fscanf(f2,"%d %d", &n2,&n2);
		fclose(f2);
		int cube = n2*n2*n2;
		printf("Child2: Cube of Number: = %d\n", cube);
		exit(0);	
	}
        wait(NULL);

	pid_t pid3 = fork();
        if(pid3<0) {
                printf("Error");
                exit(1);
        }
        else  if(pid3==0) {
                FILE *f3 = fopen("data.txt","r");
                int n3;
                fscanf(f3,"%d %d %d", &n3,&n3,&n3);
		fclose(f3);
                int sq = n3*n3;
                printf("Child3: Square of Number: = %d\n", sq);
		exit(0);
        }
        wait(NULL);

}
