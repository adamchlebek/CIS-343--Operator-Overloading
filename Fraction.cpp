#include "Fraction.h"
#include <algorithm>
#include <iomanip>
#include <regex>
#include <cmath>

using namespace std;

/* Friend functions */
Fraction operator+(int val, const Fraction &f) { 
    Fraction fTemp{ val };
    return f + fTemp;
}

Fraction operator-(int val, const Fraction &f) { 
    Fraction fTemp{ val };
    return fTemp - f;
}

Fraction operator*(int val, const Fraction &f) { 
    Fraction fTemp{ val };
    return f * fTemp;    
}

Fraction operator/(int val, const Fraction &f){
    Fraction fTemp{ val };
    return fTemp / f;
}

Fraction operator^(int val, const Fraction &f){
    Fraction fTemp{ val };
    return fTemp ^ f;
}

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
    isWhole = (s.find('/') == std::string::npos || s.find(' ') != std::string::npos); //Set isWhole based on a / or a space
    isPositiveValue = (s.find('-') == std::string::npos); //Sets isPositiveValue based on if there is a negative
    
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

    if(wholeVal == 0 && numVal == 0){
        isPositiveValue = true;
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
    num < 0 ? f.wholeVal -= num : f.wholeVal += num;
    return f;
}

Fraction Fraction::operator+(const Fraction &other) const {
    Fraction f {*this};
    int numValOther = ((other.wholeVal * other.denomVal) + other.numVal) * f.denomVal;
    int numValF = ((f.wholeVal * f.denomVal) + f.numVal) * other.denomVal;
    f.denomVal *= other.denomVal;
    f.wholeVal = 0;
    if((f.isPositiveValue && !other.isPositiveValue) || (!f.isPositiveValue && other.isPositiveValue)){
        if(numValF - numValOther < 0){
            f.isPositiveValue = false;
        }
        f.numVal = abs(numValF - numValOther);
    } else {
        f.numVal = numValF + numValOther;
    }
    if(f.numVal > f.denomVal) f.makeProper();
    f = f.toReduced();

    return f;
}

Fraction Fraction::operator-() const { 
    Fraction f{*this};
    f.isPositiveValue = !f.isPositiveValue;
    return f;
}

Fraction Fraction::operator-(int val) const {
    Fraction f {*this};
    Fraction v{val};
    return f - v;
}

Fraction Fraction::operator-(const Fraction &other) const { 
    Fraction f {*this};
    int numValOther = ((other.wholeVal * other.denomVal) + other.numVal) * f.denomVal;
    int numValF = ((f.wholeVal * f.denomVal) + f.numVal) * other.denomVal;
    f.numVal = abs(numValF - numValOther);
    f.denomVal *= other.denomVal;

    if(f.wholeVal - other.wholeVal < 0) f.isPositiveValue = false;
    if(f.wholeVal - other.wholeVal > 0 && f.isPositiveValue) f.isPositiveValue = true;
    
    f.wholeVal = 0;
    if(f.numVal > f.denomVal) f.makeProper();
    f = f.toReduced();
    return f;
}

Fraction Fraction::operator*(int val) const {     
    Fraction f {*this};
    int improper = (f.wholeVal * f.denomVal) + f.numVal;
    f.wholeVal = 0;
    if(val < 0){
        f.isPositiveValue = !f.isPositiveValue;
        f.numVal = improper * -val;
    } else if(val == 0) {
        f.isPositiveValue = true;
        f.numVal = 0;
        f.denomVal = 1;
    } else {
        f.numVal = improper * val;
    }
    if (f.numVal > f.denomVal) f.makeProper();
    f = f.toReduced();
    return f; 
}

Fraction Fraction::operator*(const Fraction &other) const { 
    Fraction f {*this};
    if(f.numVal == other.denomVal && f.denomVal == other.numVal){
        f.wholeVal = 1;
        f.numVal = 0;
        f.denomVal = 1;
        return f;
    }
    f.isPositiveValue = ((!other.isPositiveValue && !f.isPositiveValue) || (other.isPositiveValue && f.isPositiveValue)) || (other.wholeVal == 0 || f.wholeVal == 0);
    f.numVal = ((f.wholeVal * f.denomVal) + f.numVal) * ((other.wholeVal * other.denomVal) + other.numVal);
    f.denomVal = f.denomVal * other.denomVal;
    f.wholeVal = 0;
    f = f.toReduced();
    if(f.numVal > f.denomVal) f.makeProper();
    return f;
}

optional<int> Fraction::operator[](int pos) const { 
    switch(pos){
        case 0:
            if(wholeVal != 0){
                if(isPositiveValue){
                    return wholeVal;
                }else{
                    return wholeVal * -1;
                }
            }else{
                return {};
            }
        case 1:
            if(numVal != 0){
                if(wholeVal == 0 && !isPositiveValue){
                    return numVal * -1;
                }else{
                    return numVal;
                }
            }else{
                return {};
            }
        case 2:
            if(numVal != 0){
                return denomVal;
            }else{
                return {};
            }
        default:
            throw std::invalid_argument("Out of range.");
    }
}

bool Fraction::operator<(const Fraction &other) const {
    int newNum = (denomVal * wholeVal + numVal);
    if(!isPositiveValue) newNum *= -1;
    int otherNewNum = (other.denomVal * other.wholeVal + other.numVal);
    if(!other.isPositiveValue) otherNewNum *= -1;
    return ((newNum / denomVal) < (otherNewNum / other.denomVal));
}

bool Fraction::operator>(const Fraction &other) const {
    int newNum = (denomVal * wholeVal + numVal);
    if(!isPositiveValue) newNum *= -1;
    int otherNewNum = (other.denomVal * other.wholeVal + other.numVal);
    if(!other.isPositiveValue) otherNewNum *= -1;
    return ((newNum / denomVal) < (otherNewNum / other.denomVal));
}

bool Fraction::operator==(const Fraction &other) const { 
    Fraction t{other};
    t = t.toReduced();
    Fraction f{*this};
    f = f.toReduced();
    return f.numVal == t.numVal && f.denomVal == t.denomVal && f.wholeVal == t.wholeVal && f.isPositiveValue == t.isPositiveValue;
}

void Fraction::makeProper() {
    if(numVal >= denomVal){
        int rem = numVal % denomVal;
        wholeVal += numVal/denomVal;
        numVal = rem;
        if(rem == 0) denomVal = 1;
    }
}

Fraction Fraction::toProper() const {
    Fraction f{*this};

    if(f.numVal >= f.denomVal){
        int rem = f.numVal % f.denomVal;
        f.wholeVal += f.numVal/f.denomVal;
        f.numVal = rem;
        if(rem == 0) f.denomVal = 1;
    }

    return f;
}

void Fraction::reduce() {
    int greatest = gcd(numVal, denomVal);
    numVal = numVal/greatest;
    denomVal = denomVal/greatest;
}

Fraction Fraction::toReduced() const { 
    Fraction f{*this};
    int greatest = gcd(f.numVal, f.denomVal);
    if(f.wholeVal < 0) f.wholeVal *= -1;
    f.numVal = f.numVal/greatest;
    f.denomVal = f.denomVal/greatest;
    return f;
}

ostream &Fraction::writeTo(ostream &os) const { 
	os << "[";

    if(whole() == 0 && numerator() == 0 && denominator() == 1){
        os << "0]";
        return os;
    }  

	if (!isPositive()) os << "-";

	if (whole() != 0) os << whole();

	if (numerator() != 0)
	{
		if (whole() != 0) os << " ";
		os << numerator() << "/" << denominator();
	}

	os << "]";

	return os;
}

istream &Fraction::readFrom(istream &sr) /*throw(std::invalid_argument) */ { 
    char c;
    sr >> std::skipws >> c;
    std::string str = "";
    str = str + c;
    sr.peek();
    
    while(sr.good()){
        sr >> std::noskipws >> c;
        str = str + c;
        if(c == ']') break;
        if(isalpha(c) || c == '#' || c == '%') throw std::invalid_argument("Invalid Character");
        sr.peek();
    }

    if(str[1] == ']') throw std::invalid_argument("No numbers");

    if(str[0] != '[') throw std::invalid_argument("Starting character not [");

    if(str[str.size() - 1] != ']') throw std::invalid_argument("Ending character not ]");

    if(str[str.size() - 2] != '0' && str[str.size() - 3] == '/') throw std::invalid_argument("Denominator can not be 0");

    if(str.find('-') != std::string::npos) if(!isdigit(str[str.find('-') + 1])) throw std::invalid_argument("Negative with no following number");
        
    *this = Fraction(str);

    return sr;
}

bool Fraction::isReduced() const {
    return gcd(numVal, denomVal) == 1;
}

bool Fraction::isProper() const { 
    return numVal < denomVal && numVal != 0;
 }

int Fraction::gcd(int a, int b) const { 
    if (a == 0) return b; 
    if (b == 0) return a; 
   
    if (a == b) return a; 
   
    if (a > b) return gcd(a-b, b); 

    return gcd(a, b-a); 
}

ostream &operator<<(ostream &os, const Fraction &f) { 
    f.writeTo(os);
    return os; 
}

istream &operator>>(istream &s, Fraction &f) { 
    f.readFrom(s);
    return s; 
}


Fraction Fraction::operator/(int val) const {     
    Fraction f {*this};
    f.numVal = (f.denomVal * f.wholeVal) + f.numVal;
    f.denomVal *= abs(val);
    if(val < 0) f.isPositiveValue = !f.isPositiveValue;

    f.wholeVal = 0;

    if (f.numVal > f.denomVal) f.makeProper();
    f = f.toReduced();
    return f; 
}

Fraction Fraction::operator/(const Fraction &other) const { 
    Fraction f {*this};
    int newNumF = (f.denomVal * f.wholeVal) + f.numVal;
    int newNumOther = (other.denomVal * other.wholeVal) + other.numVal;
    f.isPositiveValue = ((!other.isPositiveValue && !f.isPositiveValue) || (other.isPositiveValue && f.isPositiveValue)) || (other.wholeVal == 0 || f.wholeVal == 0);

    f.numVal = newNumF * other.denomVal;
    f.wholeVal = 0;
    f.denomVal *= newNumOther;
    if(f.numVal > f.denomVal) f.makeProper();
    f = f.toReduced();

    return f;
}

Fraction Fraction::operator^(int val) const {     
    Fraction f {*this};
    int newNum = (f.denomVal * f.wholeVal) + f.numVal;
    f.isPositiveValue = newNum >= 0;

    f.wholeVal = 0;
    f.numVal = pow(newNum, abs(val));
    f.denomVal = pow(f.denomVal, abs(val));


    if(val < 0){
        int temp = f.denomVal;
        f.denomVal = f.numVal;
        f.numVal = temp;
    }

    if(f.numVal > f.denomVal) f.makeProper();
    f = f.toReduced();
    return f; 
}

Fraction Fraction::operator^(const Fraction &other) const { 
    throw std::invalid_argument("Invalid power value");
}

#if I_DO_EXTRA_CREDIT
optional<string> Fraction::isRepeating() const { return {}; }

string Fraction::operator()(int len) const { return {}; }
#endif