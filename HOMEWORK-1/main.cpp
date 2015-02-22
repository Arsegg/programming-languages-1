#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
#include <stdexcept>

using namespace std;

runtime_error divisionByZeroError("Division by zero");
runtime_error invalidCharacterError("Invalid character");

bool isNumber(string &s) {
    string::iterator it = s.begin();
    if (*it == '+' || *it == '-') {
        it++;
        if (it == s.end())
            return false;
    }
    for (; it != s.end() && isdigit(*it); it++);
    return it == s.end();
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

bool isOperator(string &s) {
    return s.size() == 1 && isOperator(s[0]);
}

int getPriority(char c) {
    if (c == '+' || c == '-')
        return 0;
    if (c == '*' || c == '/' || c == '%')
        return 1;
    throw invalidCharacterError;
}

// infix to reverse pollish notation converter
vector<string> rpn(string &expression) {
    vector<string> ans; // resulting array in reverse pollish notation
    stringstream stream(expression); // splitting input by space
    string s; // buffer for input
    vector<char> stack; // stack of operators
    while (!stream.eof()) {
        stream >> s;
        if (isNumber(s)) {
            ans.push_back(s);
        }
        else if (isOperator(s)) {
            while (!stack.empty() && stack.back() && isOperator(stack.back()) && getPriority(s[0]) <= getPriority(stack.back())) {
                ans.push_back(string(1, stack.back()));
                stack.pop_back();
            }
            stack.push_back(s[0]);
        }
        else if (s == "(")
            stack.push_back(s[0]);
        else if (s == ")") {
            while (!stack.empty() && stack.back() != '(') {
                ans.push_back(string(1, stack.back()));
                stack.pop_back();
            }
            if (stack.empty())
                throw invalidCharacterError;
            stack.pop_back();
        }
        else
            throw invalidCharacterError;
    }
    while (!stack.empty()) {
        ans.push_back(string(1, stack.back()));
        stack.pop_back();
    }
    return ans;
}

// reverse pollish notation calculator
int solve(vector<string> s) {
    vector<int> stack; // stack of numbers
    for (vector<string>::iterator it = s.begin(); it != s.end(); it++) {
        if (isNumber(*it))
            stack.push_back(atoi(it->c_str()));
        else {
            // pop 2 arguments from stack and calculate
            if (stack.size() < 2)
                throw invalidCharacterError;
            int second = stack.back();
            stack.pop_back();
            int first = stack.back();
            stack.pop_back();
            switch (it->at(0)) {
                case '+':
                    stack.push_back(first + second);
                    break;
                case '-':
                    stack.push_back(first - second);
                    break;
                case '*':
                    stack.push_back(first * second);
                    break;
                case '/':
                    if (!second)
                        throw divisionByZeroError;
                    stack.push_back(first / second);
                    break;
                case '%':
                    if (!second)
                        throw divisionByZeroError;
                    stack.push_back(first % second);
                    break;
            }
        }
    }
    if (stack.size() != 1)
        throw invalidCharacterError;
    return stack.back();
}

int main() {
    string s("2 + 2 * 2 - 1 - 1337 % 6 + 666 / -666 * 13 * 24 + ( ( 1 + 3 + 3 ) / 7 ) * ( 12345 % 1337 )"); // = 0
    getline(cin, s);
    try {
        cout << solve(rpn(s)) << "\n";
    }
    catch (exception &e) {
        cerr << "Error: " << e.what() << "\n";
    }
    cout << "Press any key...";
    getch();

    return 0;
}