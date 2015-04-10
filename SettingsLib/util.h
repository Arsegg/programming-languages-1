#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <cmath>

void assertTrue(const std::string &message, const bool &condition) {
    if (!condition) {
        std::cerr << message << "\n";
    }
}

template<class T>
void assertEquals(const std::string &message, const T &actual, const T &expected) {
    std::ostringstream stream;
    stream << message << ": Expected " << expected << ", found " << actual;
    assertTrue(stream.str(), actual == expected);
}

void assertEquals(const std::string &message, const double &actual, const double &expected) {
    std::ostringstream stream;
    stream << message << ": Expected " << expected << ", found " << actual;
    assertTrue(stream.str(), std::abs(actual - expected) < 1e-9);
}

int stringToInt(const std::string &s) {
    std::istringstream stream(s);
    int ans;
    stream >> ans;

    return ans;
}

bool stringToBool(const std::string &s) {
    if (s == "true") {
        return true;
    }
    if (s == "false") {
        return false;
    }
    throw std::runtime_error("Wrong value: " + s);
}

double stringToDouble(const std::string &s) {
    std::istringstream stream(s);
    double ans;
    stream >> ans;

    return ans;
}

std::string intToString(const int &n) {
    std::ostringstream stream;
    stream << n;

    return stream.str();
}

std::string boolToString(const bool &n) {
    return n ? "true" : "false";
}

std::string doubleToString(const double &n) {
    std::ostringstream stream;
    stream << n;

    return stream.str();
}

template<class T>
void testFunc(const std::string &message, const T &actual, const T &expected) {
    std::cout << "Testing: " << message << "\n";
    assertEquals(message, actual, expected);
}

void test() {
    std::cout << "Testing started.\n";

    testFunc("stringToInt(-2147483648)", stringToInt("-2147483648l"), (int) -2147483648);
    testFunc("stringToInt(2147483647)", stringToInt("2147483647"), (int) 2147483647);
    testFunc("stringToBool(false)", stringToBool("false"), false);
    testFunc("stringToBool(true)", stringToBool("true"), true);
    testFunc("stringToDouble(1.7e-308)", stringToDouble("1.7e-308"), 1.7e-308);
    testFunc("stringToDouble(1.7e+308)", stringToDouble("1.7e+308"), 1.7e+308);
    testFunc("intToString(-2147483648)", intToString(-2147483648), std::string("-2147483648"));
    testFunc("intToString(2147483647)", intToString(2147483647), std::string("2147483647"));
    testFunc("boolToString(false)", boolToString(false), std::string("false"));
    testFunc("boolToString(true)", boolToString(true), std::string("true"));
    testFunc("doubleToString(1.7e-308)", doubleToString(1.7e-308), std::string("1.7e-308"));
    testFunc("doubleToString(1.7e+308)", doubleToString(1.7e+308), std::string("1.7e+308"));

    std::cout << "Testing finished.\n\n";
}

#endif //_UTIL_H_
