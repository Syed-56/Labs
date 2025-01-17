#include<stdio.h>
#include<stdlib.h>
typedef struct {
	char **copyCountries;
	char title[20];
	char artist[30];
	char genre[20];
	int tracks;
} song;
void inputSong(int n, song *cd, int region[]) {
	for(int i=0; i<n; i++) {
		getchar();
		printf("\nEnter Title : ");
		scanf("%s", &cd[i].title);
		printf("Enter Artist : ");
		scanf("%s", &cd[i].artist);
		printf("Enter Genre : ");
		scanf("%s", &cd[i].genre);
		printf("Enter No. of Tracks : ");
		scanf("%d", &cd[i].tracks);
		printf("In How many Regions : ");
		scanf("%d", &region[i]);
		cd[i].copyCountries = (char **)malloc(region[i] * sizeof(char *));
        if (!cd[i].copyCountries) exit(1);
		for (int j = 0; j < region[i]; j++) {
            cd[i].copyCountries[j] = (char *)malloc(30 * sizeof(char)); // Allocate memory for each region name
            if (!cd[i].copyCountries[j]) 	exit(1);
            printf("Enter Region %d: ", j+1);
            scanf("%s", cd[i].copyCountries[j]); // Limit input
        }
	}
}
void outputSong(int n, song *cd, int region[]) {
	for(int i=0; i<n; i++) {
		printf("\nSong %d", i+1);
		printf("\nTitle : %s", cd[i].title);
		printf("\nArtist : %s", cd[i].artist);
		printf("\nGenre : %s", cd[i].genre);
		printf("\nTracks : %d", cd[i].tracks);
		printf("\nRegions:-\n");
		for(int j=0; j<region[i]; j++) {
			printf("%s  ", cd[i].copyCountries[j]);
		}
		printf("\n");
	}
}
int main() {
	int n;
	printf("How Many Songs : ");
	scanf("%d", &n);
	song *cd;
	cd = (song* )malloc(n * sizeof(song));
	if(!cd) 	return 1;
	int region[n];
	inputSong(n,cd,region);
	outputSong(n,cd,region);
	for (int i = 0; i < n; i++) {
        free(cd[i].copyCountries);
    }
    free(cd);
}