#include <iostream>
using namespace std;
class HugeInt {
	int *data;
	int size;
	public:
	void input();
	void output();
	
	HugeInt();
	HugeInt(int* d, int s);
	HugeInt(const HugeInt& obj);
	
	bool isLessThan(HugeInt& obj);
	HugeInt add(HugeInt obj);
	~HugeInt() {
		delete[] data;
	}
};

HugeInt::HugeInt() {}
HugeInt::HugeInt(int* d, int s) : size(s) {
	data = new int[size];
    for (int i = 0; i < size; i++)  data[i] = d[i];
}
HugeInt::HugeInt(const HugeInt& obj) {
	data = new int[size]; 
	for(int i=0; i<size; i++) 	data[i] = obj.data[i]; 
	size = obj.size;
}
void HugeInt::input() {
	cout << "Enter Size: ";
	cin >> size;
	data = new int[size];
	cout << "Enter Data: ";
	for(int i=0; i<size; i++)	cin >> data[i];
}
void HugeInt::output() {
	cout << "Number: ";
	for(int i=0; i<size ;i++)	cout << data[i];
}
bool HugeInt::isLessThan(HugeInt& obj) {
	if (size != obj.size)
        return size < obj.size;
    for (int i=0; i<size; i++) {
        if (data[i] != obj.data[i])
            return data[i] < obj.data[i];
    }
    return false;
}
HugeInt HugeInt::add(HugeInt obj) {
	int maxSize = (size > obj.size) ? size : obj.size;
    int *result = new int[maxSize + 1]();
    
    int carry = 0, i = size - 1, j = obj.size - 1, k = maxSize;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += data[i--];
        if (j >= 0) sum += obj.data[j--];
        result[k--] = sum % 10;
        carry = sum / 10;
    }
    
    return HugeInt(result + k + 1, maxSize - k);
}

int main() {
	HugeInt obj1;
	obj1.input();
	int data[] = {1,2,3,4,5,6,7,8,9,0};
	int size = sizeof(data)/sizeof(data[0]);
	HugeInt obj2(data,size);
	HugeInt obj3 = obj1.add(obj2);
	obj1.output();
	cout << " + ";
	obj2.output();
	cout << " = ";
	obj3.output();
	cout << endl;
	if(obj2.isLessThan(obj3))	cout << "I am Lesser\n";
	else	cout << "I am Bigger\n";
}