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
    isWhole = other.isWhole; //Set isWhole to object
    isPositiveValue = other.isPositiveValue; //Set isPositiveValue to object
    isFraction = other.isFraction; //Set isFraction to object
    wholeVal = other.wholeVal; //Set wholeVal to object
    numVal = other.numVal; //Set numVal to object
    denomVal = other.denomVal; //Set denomVal to object
}

Fraction::Fraction(Fraction &&other) {
    isWhole = other.isWhole; //Set isWhole to object
    isPositiveValue = other.isPositiveValue; //Set isPositiveValue to object
    isFraction = other.isFraction; //Set isFraction to object
    wholeVal = other.wholeVal; //Set wholeVal to object
    numVal = other.numVal; //Set numVal to object
    denomVal = other.denomVal; //Set denomVal to object
}

Fraction::Fraction(std::string s) {
    isPositiveValue = (s.find('-') == std::string::npos); //Sets isPositiveValue based on if there is a negative
    isWhole = (s.find('/') == std::string::npos || s.find(' ') != std::string::npos); //Set isWhole based on a / or a space

    if(s.find('/') == std::string::npos){
        wholeVal = abs(stoi(s)); //WholeVal is abs of stoi of s
    }else if(s.find(' ') != std::string::npos){
        isFraction = true; //isFraction is true if there is a space
        wholeVal = abs(stoi(s.substr(0, s.find(' ')))); //WholeVal is getting the first character before the space
        numVal = abs(stoi(s.substr(s.find(' '), s.find('/') - s.find(' ')))); //Numerator is found after the whole Num and before the /
        denomVal = abs(stoi(s.substr(s.find('/') + 1, s.length() - (s.find('/') + 1)))); //Denominator is found after the numerator and after the /
    }else{
        isFraction = true; //isFraction is true if there is not a space or a /
        numVal = abs(stoi(s.substr(0, s.find('/')))); //Numerator is found before the /
        denomVal = abs(stoi(s.substr(s.find('/') + 1, s.length() - (s.find('/') + 1)))); //Denominator is found after the /
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
    return denomVal;    
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

Fraction& Fraction::operator=(Fraction &&other) { 
    isWhole = std::move(other.isWhole);
    isPositiveValue = std::move(other.isPositiveValue);
    isFraction = std::move(other.isFraction);
    wholeVal = std::move(other.wholeVal);
    numVal = std::move(other.numVal);
    denomVal = std::move(other.denomVal);
    return *this;
}

Fraction Fraction::operator+(int num) const { 
    Fraction f{*this};
    if (num < 0){
        f.wholeVal -= num;
    }else{
        f.wholeVal += num;
    }
    return f;
}

Fraction Fraction::operator+(const Fraction &other) const { 
    // Fraction f;
    // if (num < 0){
    //     f.wholeVal = this->wholeVal - other.wholeVal;
    // }else{
    //     f.wholeVal = this->wholeVal + other.wholeVal;
    // }
    // return f;
    return {};
}

Fraction Fraction::operator-() const { 
    Fraction f{*this};
    f.isPositiveValue = !f.isPositiveValue;
    return f;
}

Fraction Fraction::operator-(int val) const {
    Fraction f{*this};
    f.wholeVal = f.whole() - val;
    return f;
}

Fraction Fraction::operator-(const Fraction &other) const { return {}; }

Fraction Fraction::operator*(int val) const {     
    Fraction f{*this};
    f.wholeVal = f.whole() * val;
    return f; 
}

Fraction Fraction::operator*(const Fraction &other) const { return {}; }

optional<int> Fraction::operator[](int pos) const { return {}; }

bool Fraction::operator<(const Fraction &other) const { return {}; }

bool Fraction::operator==(const Fraction &other) const { 
    Fraction f{*this};
    Fraction t{other};
    f = f.toReduced();
    t = t.toReduced();
    return f.numVal == t.numVal && f.denomVal == t.denomVal && f.wholeVal == t.wholeVal;
}

void Fraction::makeProper() {
    if(this->numVal >= this->denomVal){
        int rem = this->numVal % this->denomVal;
        this->wholeVal += this->numVal/this->denomVal;
        this->numVal = rem;
        if(rem == 0){
            this->denomVal = 1;
        }
    }
}

Fraction Fraction::toProper() const {
    Fraction f{*this};

    if(f.numVal >= f.denomVal){
        int rem = f.numVal % f.denomVal;
        f.wholeVal += f.numVal/f.denomVal;
        f.numVal = rem;
        if(rem == 0){
            f.denomVal = 1;
        }
    }

    return f;
}

void Fraction::reduce() {
    int greatest = gcd(this->numVal, this->denomVal);
    this->numVal = this->numVal/greatest;
    this->denomVal = this->denomVal/greatest;
}

Fraction Fraction::toReduced() const { 
    Fraction f{*this};
    int greatest = gcd(f.numVal, f.denomVal);
    f.numVal = f.numVal/greatest;
    f.denomVal = f.denomVal/greatest;
    return f;
}

ostream &Fraction::writeTo(ostream &os) const { return os; }

istream &Fraction::readFrom(istream &sr) /*throw(std::invalid_argument) */ {
    std::string s = "";
    char i;
    while(!sr.eof()){
        i = sr.get();
        s += char(i);
        if(i == ']'){
            break;
        }
    }
    
    if(s[0] != '['){
        throw std::invalid_argument("Invalid_Argument");
    }

    //string fractString = inputString.substr(indexOfB1+1, indexOfB2 - indexOfB1-1)

    Fraction{s};

    return sr;
}

bool Fraction::isReduced() const {
    return gcd(this->numVal, this->denomVal) == 1;
}

bool Fraction::isProper() const { 
    return this->numVal < this->denomVal && this->numVal != 0;
 }

int Fraction::gcd(int a, int b) const {
    // Everything divides 0  
    if (a == 0) 
       return b; 
    if (b == 0) 
       return a; 
   
    // base case 
    if (a == b) 
        return a; 
   
    // a is greater 
    if (a > b) 
        return gcd(a-b, b); 
    return gcd(a, b-a); 
}

ostream &operator<<(ostream &os, const Fraction &f) { return os; }

istream &operator>>(istream &s, Fraction &f) { 
    f.readFrom(s);
    return s; 
}

#if I_DO_EXTRA_CREDIT
optional<string> Fraction::isRepeating() const { return {}; }

string Fraction::operator()(int len) const { return {}; }
#endif