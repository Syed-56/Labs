#include <iostream>
using namespace std;

class StackOverflowException : public std::exception {
	const char* what() const noexcept override {
		return "StackOverflowException - Stack is full!";
	}
};
class StackUnderflowException : public std::exception {
	const char* what() const noexcept override {
		return "StackUnderflowException - Stack is full!";
	}
};

template <typename stack>
class Stack {
	stack* arr;
	int capacity, storage;
	
	public:
	Stack(int cap) : capacity(cap) {
		arr = new stack[capacity];
	}
	
	void push(int n) {
		if(storage >= capacity) {
			throw StackOverflowException();
		}
		else {
			cout << n << " added to stack" << endl;
			arr[++storage] = n;
		}
	}
	void pop() {
		if(storage <= 0) {
			throw StackUnderflowException();
		}
		else {
			cout << arr[storage] << " removed from stack" << endl;
			arr[storage--];
		}
	}
	
	~Stack() {
		delete[] arr;
	}
};

int main() {
	Stack<int> array(3);
	
	try {
		array.push(1);
		array.push(2);
		array.push(3);
		array.push(4);
	} catch(exception &e) {
		cout << e.what() << endl;
	}
	
	try {
		array.pop();
		array.pop();
		array.pop();
		array.pop();
	} catch(exception &e) {
		cout << e.what() << endl;
	}
}