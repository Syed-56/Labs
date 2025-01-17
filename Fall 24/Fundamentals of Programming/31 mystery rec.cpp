#include<stdio.h>
int mysteryRec(int a, int b) {
	if(b==1)	return a;
	else {
		return a + mysteryRec(a,b-1);
	}
}
int main() {
	int a=5,b=4;
	int x = mysteryRec(a,b);
	printf("%d", x);
}