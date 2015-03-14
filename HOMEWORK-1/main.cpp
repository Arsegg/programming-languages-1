#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

// given string is number or not
bool isNumber(const string & s) {
    string::const_iterator it = s.begin();
    if (*it == '+' || *it == '-') {
        it++;
        if (it == s.end()) {
            return false;
        }
    }
    while (it != s.end() && isdigit(*it)) {
        it++;
    }
    return it == s.end();
}

// given string is operator or not
bool isOperator(const string & c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "%";
}

// get priority of given operator
// 0 for plus and minus
// 1 for multiply, divide and divide by modulo
int getPriority(const string & c) {
    if (c == "+" || c == "-") {
        return 0;
    }
    if (c == "*" || c == "/" || c == "%") {
        return 1;
    }
    throw runtime_error("Incorrect operator");
}

// infix to reverse pollish notation converter
vector<string> rpnize(const string & expression) {
    vector<string> ans;
    stringstream stream(expression);
    string s;
    vector<string> stack;
    while (!stream.eof()) {
        stream >> s;
        if (isNumber(s)) {
            ans.push_back(s);
        } else if (isOperator(s)) {
            while (!stack.empty() && isOperator(stack.back()) && getPriority(s) <= getPriority(stack.back())) {
                ans.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(s);
        } else if (s == "(") {
            stack.push_back(s);
        } else if (s == ")") {
            while (!stack.empty() && stack.back() != "(") {
                ans.push_back(stack.back());
                stack.pop_back();
            }
            if (stack.empty()) {
                throw runtime_error("Invalid brackets");
            }
            stack.pop_back();
        } else {
            throw runtime_error("Invalid word");
        }
    }
    while (!stack.empty()) {
        ans.push_back(stack.back());
        stack.pop_back();
    }
    return ans;
}

// reverse pollish notation calculator
int solve(const vector<string> & s) {
    vector<int> stack;
    for (vector<string>::const_iterator it = s.begin(); it != s.end(); it++) {
        if (isNumber(*it)) {
            stack.push_back(atoi(it->c_str()));
        }
        else {
            if (stack.size() < 2) {
                throw runtime_error("Invalid expression");
            }
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
                    if (second == 0) {
                        throw runtime_error("Division by zero");
                    }
                    stack.push_back(first / second);
                    break;
                case '%':
                    if (second == 0) {
                        throw runtime_error("Division by zero");
                    }
                    stack.push_back(first % second);
                    break;
            }
        }
    }
    if (stack.size() != 1) {
        throw runtime_error("Invalid expression");
    }
    return stack.back();
}

int main() {
    string s;
    do {
        cout << "Enter math expression (empty string for exit):\n";
        getline(cin, s);
        try {
            cout << s << " = " << solve(rpnize(s)) << "\n";
        }
        catch (exception & e) {
            cerr << "Caught error: " << e.what() << "\n";
        }
    } while (!s.empty());

    return 0;
}