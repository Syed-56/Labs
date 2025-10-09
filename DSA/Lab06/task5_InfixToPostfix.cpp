#include <iostream>
#define MAX 5
#include <cmath>
using namespace std;

class Stack {
    int arr[MAX];
    int top=-1;

    public:
    void push(char val) {
        if(top >= MAX-1) {
            cout << "Stack Overflow\n";
            return;
        }
        top++;
        arr[top] = val;
    }
    void pop() {
        if(top==-1) {
            cout << "Stack Underflow\n";
            return;
        }
        arr[top]=0;
        top--;
    }
    int getTop() {
        return arr[top];
    }
    bool empty() {
        return (top==-1);
    }
};


int precedence(char op) {
    if(op=='^')  return 3;
    else if(op=='*' || op=='/')  return 2;
    else if(op=='+' || op=='-')  return 1;
    else return -1;
}

string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";

    for(int i=0; i<infix.length(); i++) {
        char c = infix[i];
        if((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            postfix += c;
        }
        else if(c == '(')  s.push('(');
        else if(c==')') {
            while(!s.empty() && s.getTop() != '(') {
                postfix += s.getTop();
                s.pop();
            }
            if(s.getTop()=='(')    s.pop();
        }
        else {
            while(!s.empty() && precedence(c) <= precedence(s.getTop())) {
                postfix += s.getTop();
                s.pop();
            }
            s.push(c);
        }
    }
    while(!s.empty()) {
        postfix += s.getTop();
        s.pop();
    }
    return postfix;
}

int evaluatePostfix(string postfix) {
    Stack s;
    for(int i=0; i<postfix.size(); i++) {
        char c = postfix[i];
        if(isdigit(c))  s.push(c-'0');
        else {
            int op2 = s.getTop(); s.pop();
            int op1 = s.getTop(); s.pop();
            int result = 0;

            switch (c) {
                case '+': result = op1+op2; break;
                case '-': result = op1-op2; break;
                case '*': result = op1*op2; break;
                case '/': result = op1/op2; break;
                case '^': result = pow(op1,op2); break;
                default: break;
            }
            s.push(result);
        }
    }
    return s.getTop();
}

int main() {
    string infix = "A+(B*C-D)/E";
    string postfix = infixToPostfix(infix);
    cout << postfix << endl;

    string infix2 = "1+(2*3-4)";
    cout << infix2 << " = " << evaluatePostfix(infixToPostfix(infix2));
}