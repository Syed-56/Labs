#include<iostream>
#include<string>
using namespace std;
string concatenate(string* words, string word1, string word2) {
	words[0] = word1+word2;
	return words[0];
}
string comparison(string* words, string word1, string word2) {
	if(word1 > word2)	words[1] = word1 + " is greater than " + word2;
	else if(word2 > word1)  words[1] = word2 + " is greater than " + word1;
	else	words[1] = "both are equal";
	return words[1];
}
string legnth(string* words, string word1, string word2) {
	int length1 = 0;
        while (word1[length1] != '\0') {
        length1++;
    }
    int length2 = 0;
        while (word2[length2] != '\0') {
        length2++;
    }
    // I used the to_string() function to covert integer value of legnth into string
    words[2] = "Legnth of " + word1 + " = " + to_string(length1) + "\t Legnth of " + word2 + " = " + to_string(length2);
    return words[2];
}
int main() {
	string word1, word2;
	cout << "Enter String 1 : ";
	getline(cin,word1);
	cout << "Enter String 2 : ";
	getline(cin,word2);
	string* words = new string[3];
	cout << "Concatenation : " << concatenate(words,word1,word2);
	cout << "\nComparison : " << comparison(words,word1,word2);
	cout << "\nLegnth : " << legnth(words,word1,word2);
	delete[] words;
}