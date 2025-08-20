#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main() {
	int d1,d2,sum[100]={0};
	srand(time(0));
	int freq[13] = {0};
	for(int i=0; i<100; i++) {
		d1 = rand() % 6 + 1;
		d2 = (rand() % 6) + 1;
		sum[i] = d1+d2;
		freq[sum[i]]++;
	}
	printf("Sum  Freq\n");
	int max = freq[2];
	int j;
	for(int i=2; i<12; i++) {
		printf(" %d :  %d\n", i, freq[i]);
		if(freq[i] > max) {
			max = freq[i];
			j=i;
		}
	}
	printf("Max Freq is %d of %d", max, j);
}