#include "Fraction.h"
#include <algorithm>
#include <iomanip>
#include <regex>

using namespace std;

/* Friend functions */
Fraction operator+(int val, const Fraction &f) { return {}; }

Fraction operator-(int val, const Fraction &f) { return {}; }

Fraction operator*(int val, const Fraction &f) { return {}; }

Fraction::Fraction() {
    isWhole = false; //Sets default to false
    isPositiveValue = false; //Sets default to false
    isFraction = false; //Sets default to false 
    wholeVal = 0; //Sets default to 0
    numVal = 0; //Sets default to 0
    denomVal = 1; //Sets default to 1 because denominator can't be 0
}

Fraction::Fraction(int v) {
    isPositiveValue = v > 0; //Checks if value is greater than 0
    wholeVal = abs(v); //Gets the positive value of v
    isWhole = true; //Sets whole value to true
    isFraction = false; //Sets fraction to false
    numVal = 0; //Sets numerator value to 0
    denomVal = 1; //Sets numberator value to 1 because denominator can't be 0
}

Fraction::Fraction(const Fraction &other) {
    isWhole = other.isWhole;
    isPositiveValue = other.isPositiveValue;
    isFraction = other.isFraction;
    wholeVal = other.wholeVal;
    numVal = other.numVal;
    denomVal = other.denomVal;
}

Fraction::Fraction(Fraction &&other) {
    isWhole = other.isWhole;
    isPositiveValue = other.isPositiveValue;
    isFraction = other.isFraction;
    wholeVal = other.wholeVal;
    numVal = other.numVal;
    denomVal = other.denomVal;
}

Fraction::Fraction(std::string s) {
    isPositiveValue = (s.find('-') != std::string::npos); //Sets positive value if there is a negative
    isWhole = true; //Sets whole val to true

    if(s.find('/') == std::string::npos){ //Finds a / in the string
        wholeVal = abs(stoi(s));
    }else if(s.find(' ') != std::string::npos){ //Checks if there is a space in in
        isFraction = true;
        wholeVal = abs(stoi(s.substr(0, s.find(' '))));
        numVal = abs(stoi(s.substr(s.find(' '), s.find('/') - s.find(' '))));
        denomVal = abs(stoi(s.substr(s.find('/') + 1, s.length() - (s.find('/') + 1))));
    }else{
        isFraction = true;
        numVal = abs(stoi(s.substr(0, s.find('/'))));
        denomVal = abs(stoi(s.substr(s.find('/') + 1, s.length() - (s.find('/') + 1))));
    }

    //Adds check to make sure denominator is not 0
    if(denomVal == 0){
        throw std::invalid_argument("Error: Value 0 can not be in the denominator!");
    }
}

int Fraction::whole() const { 
    return wholeVal;
}

int Fraction::numerator() const { 
    return numVal;
}

int Fraction::denominator() const { 
    return isFraction ? denomVal : 1;
}

bool Fraction::isPositive() const {
    return isPositiveValue;
 }

Fraction& Fraction::operator=(const Fraction &other) { 
    isWhole = other.isWhole;
    isPositiveValue = other.isPositiveValue;
    isFraction = other.isFraction;
    wholeVal = other.wholeVal;
    numVal = other.numVal;
    denomVal = other.denomVal;
    return *this; 
}

Fraction& Fraction::operator=(Fraction &&other) { return *this; }

Fraction Fraction::operator+(int num) const { return {}; }

Fraction Fraction::operator+(const Fraction &other) const { return {}; }

Fraction Fraction::operator-() const { return {}; }

Fraction Fraction::operator-(int val) const { return {}; }

Fraction Fraction::operator-(const Fraction &other) const { return {}; }

Fraction Fraction::operator*(int val) const { return {}; }

Fraction Fraction::operator*(const Fraction &other) const { return {}; }

optional<int> Fraction::operator[](int pos) const { return {}; }

bool Fraction::operator<(const Fraction &other) const { return {}; }

bool Fraction::operator==(const Fraction &other) const { return {}; }

void Fraction::makeProper() {}

Fraction Fraction::toProper() const { return {}; }

void Fraction::reduce() {}

Fraction Fraction::toReduced() const { return {}; }

ostream &Fraction::writeTo(ostream &os) const { return os; }

istream &Fraction::readFrom(istream &sr) /*throw(std::invalid_argument) */ {
    return sr;
}

bool Fraction::isReduced() const { return {}; }

bool Fraction::isProper() const { return {}; }

ostream &operator<<(ostream &os, const Fraction &f) { return os; }

istream &operator>>(istream &s, Fraction &f) { return s; }

#if I_DO_EXTRA_CREDIT
optional<string> Fraction::isRepeating() const { return {}; }

string Fraction::operator()(int len) const { return {}; }
#endif