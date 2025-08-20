#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	char name[50];
	int age;
	int marks;
} student;
void display(int n, student s[]) {
	for(int i=0; i<n; i++) {
		printf("\nName : %s\t", s[i].name);
		printf("Age : %d\t", s[i].age);
		printf("Marks : %d\n", s[i].marks);
	}
}
void update(int n, student s[]) {
	int i;
	char att[20];
	printf("Which Student's record you want to update : ");
	scanf("%d", &i);
	if(i>n ||i<1) {
		printf("Invalid Student Index\n");
		return;
	}
	printf("Which Attribute to update : ");
	scanf("%s", &att);
	getchar();
	if(strcmp(att,"Name")==0) {
		printf("Enter New Name for Student %d : ", i);
		fgets(s[i-1].name,50,stdin);
		s[i-1].name[strcspn(s[i-1].name,"\n")]=0;
	}
	else if(strcmp(att,"Age")==0) {
		printf("Enter New Age for Student %d : ", i);
		scanf("%d", &s[i-1].age);
	}
	else if(strcmp(att,"Marks")==0) {
		printf("Enter New Marks for Student %d : ", i);
		scanf("%d", &s[i-1].marks);
	}
	else	printf("Invalid Attriubte\n");
}
void add(int *n, student s[]) {
	int N;
	printf("How Many Students You want to Add : ");
	scanf("%d", &N);
	s = (student* )realloc(s, (*n+N) * sizeof(student));
	if(!s)	exit(1);
	for(int i=*n; i<*n+N; i++) {
		getchar();
		printf("Student %d Details\n", i+1);
		printf("Enter Name : ");
		fgets(s[i].name,50,stdin);
		s[i].name[strcspn(s[i].name,"\n")]=0;
		printf("Enter Age : ");
		scanf("%d", &s[i].age);
		printf("Enter Marks : ");
		scanf("%d", &s[i].marks);
	}
	*n += N;
}
void del(int *n, student s[]) {
	int ind=-1;
	char Name[50];
	printf("Which Student You Want to Delete : ");
	getchar();
	fgets(Name,50,stdin);
	Name[strcspn(Name,"\n")]=0;
	for(int i=0; i < *n; i++) {
		if(strcmp(Name,s[i].name)==0) {
			ind=i;
			strcpy(s[i].name," ");
			s[i].age=0;
			s[i].marks=0;
			break;
		}
	}
	if(ind == -1) {
		printf("Student Not Found");
		return;
	}
	for(int i=ind; i< (*n)-1; i++) {
		strcpy(s[i].name,s[i+1].name);
		s[i].age = s[i+1].age;
		s[i].marks = s[i+1].marks;
	}
	*n--;
	s = (student* )realloc(s, (*n) * sizeof(student));
	if(!s)	exit(1);
}
int findTop(int n, student s[]) {
	int max = s[0].marks;
	for(int i=0; i<n; i++) {
		if(s[i].marks > max)	max = s[i].marks;
	}
	return max;
}
void sort(int n, student s[]) {
	char att[20];
	student temp;
	printf("By Attribute to Sort : ");
	scanf("%s", &att);
	getchar();
	for(int i=0; i<n-1; i++) {
		for(int j=0; j<n-i-1; j++) {
			if(strcmp(att,"Name")==0) {
				if(strcmp(s[j].name,s[j+1].name) > 0) {
					temp = s[j];
					s[j] = s[j+1];
					s[j+1] = temp;
				}
			}
			else if(strcmp(att,"Age")==0) {
				if(s[j].age > s[j+1].age) {
					temp = s[j];
					s[j] = s[j+1];
					s[j+1] = temp;
				}
			}
			else if(strcmp(att,"Marks")==0) {
				if(s[j].marks > s[j+1].marks) {
					temp = s[j];
					s[j] = s[j+1];
					s[j+1] = temp;
				}
			}
			else	printf("Invalid Attribute");
		}
	}
	printf("Students sorted by %s\n", att);
}
int main() {
	int n;
	printf("How Many Students You want to have in your system : ");
	scanf("%d", &n);
	student *s = (student* )malloc(n * sizeof(student));
	if(!s)	exit(1);
	for(int i=0; i<n; i++) {
		getchar();
		printf("Student %d Details\n", i+1);
		printf("Enter Name : ");
		fgets(s[i].name,50,stdin);
		s[i].name[strcspn(s[i].name,"\n")]=0;
		printf("Enter Age : ");
		scanf("%d", &s[i].age);
		printf("Enter Marks : ");
		scanf("%d", &s[i].marks);
	}
	int opt;
	while(1) {
		printf("\n1) Display Student Record\n2) Update Student Record\n3) Add Student\n4) Delete Student\n5) Find Top performer\n6) Sort\n7) Exit");
		printf("\nWhat You Want : ");
		scanf("%d", &opt);
		getchar();
		if		(opt==1)	display(n,s);
		else if (opt==2)	update(n,s);
		else if (opt==3)	add(&n,s);
		else if (opt==4)	del(&n,s);
		else if	(opt==5) {
			printf("\nHighest Marks are %d", findTop(n,s));
		}
		else if(opt==5)	{
			sort(n,s);
			display(n,s);
		}
		else	break;
	}
	free(s);
}