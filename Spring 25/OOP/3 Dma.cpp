#include <iostream>
using namespace std;
int main() {
	int n=5;
	int* ptr=&n;
	int**p = &ptr;
	cout<<"Val of n = "<<n<<"\nAdd of n = "<<ptr<<"\nVal of n = "<<*ptr<<"\nAdd of n = "<<&n;
	cout<<"\nVal of ptr = "<<*p<<"\nAdd of ptr = "<<p<<"\nVal of n = "<<**p<<"\nAdd of p = "<<&p;
	
	int* num  =  new int;
	*num  =  5;  //DMA in C, storing address of 5 without creating a variable
	int* mun = new int(10);	//this is called explicit declaration and the above one is called inplicit decleration. both are valid
	cout<<"\nAddress of 5 = "<<num<<"\nAddress of 10 = "<<mun;
	cout<<"\nValue at "<<num<<" = "<<*num<<"\nvalue at "<<mun<<" = "<<*mun;
	delete num, mun;
}