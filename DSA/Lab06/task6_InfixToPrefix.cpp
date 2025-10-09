#include <iostream>
#include <cmath>
#define MAX 100
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

string infixToPrefix(string infix) {
    for(int i=0; i<(infix.size()/2); i++)   swap(infix[i], infix[infix.size()-i-1]);
    for(int i=0; i<(infix.size()); i++) {
        if(infix[i]=='(')  infix[i] = ')';
        else if(infix[i]==')')    infix[i] = '(';
    }

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
    string prefix = postfix;
    for(int i=0; i<(prefix.size()/2); i++)   swap(prefix[i], prefix[prefix.size()-i-1]);
    return prefix;
}

int evaluatePrefix(string prefix) {
    Stack s;
    for(int i=prefix.length()-1; i>=0; i--) {
        char c = prefix[i];
        if(isdigit(c))  s.push(c-'0');
        else {
            int op1 = s.getTop(); s.pop();
            int op2 = s.getTop(); s.pop();
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
    string prefix = infixToPrefix(infix);
    cout << prefix << endl;

    string infix2 = "1+(2*3-4)";
    cout << infix2 << " = " << evaluatePrefix(infixToPrefix(infix2));
}