#include<stdio.h>
int findMaxProfit(int m, int n, int difficulty[], int profit[], int worker[]) {
	 int money = 0;
    for(int i = 0; i < m; i++) {
        int max = 0; // Initialize max profit for each worker
        for(int j = 0; j < n; j++) {
            if(difficulty[j] <= worker[i] && profit[j] > max) {
                max = profit[j];
            }
        }
        money += max; // Add the highest profit the worker can achieve
    }
    return money;
}

int main() {
	int m,n;
	printf("Enter Number of Jobs : ");
	scanf("%d", &n);
	printf("Enter Number of Workers : ");
	scanf("%d", &m);
	int difficulty[n], profit[n], worker[m];
	printf("Enter Difficulty Levels\n");
	for(int i=0; i<m; i++) 	scanf("%d", &difficulty[i]);
	printf("Enter Profits Levels\n");
	for(int i=0; i<m; i++) 	scanf("%d", &profit[i]);
	printf("Enter Workers Levels\n");
	for(int i=0; i<n; i++) 	scanf("%d", &worker[i]);
	printf("Maximum Achievable Profit : %d", findMaxProfit(m,n,difficulty,profit,worker));
}