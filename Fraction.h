#pragma once
#include <iostream>
#include <optional>
#include <string>

using std::istream;
using std::optional;
using std::ostream;
using std::string;

class Fraction {
    friend ostream &operator<<(ostream &, const Fraction &);
    friend istream &operator>>(istream &, Fraction &);
    friend Fraction operator+(int, const Fraction &);
    friend Fraction operator-(int, const Fraction &);
    friend Fraction operator*(int, const Fraction &);
    friend Fraction operator/(int, const Fraction &);
    friend Fraction operator^(int, const Fraction &);

  public:
    /* Constructors */
    Fraction();
    Fraction(int);
    Fraction(string);
    Fraction(const Fraction &);
    Fraction(Fraction &&);

    // Access functions
    int whole() const;
    int numerator() const;
    int denominator() const;
    bool isPositive() const;

    // Conversion functions
    void reduce();     // Convert fraction to reduced form
    void makeProper(); // Convert fraction to proper form
    Fraction toProper() const;
    Fraction toReduced() const;
    bool isReduced() const;
    bool isProper() const;

    //Custom Functions
    int gcd(int a, int b) const;

    // Operator functions
    Fraction &operator=(const Fraction &);      // Copy assignment
    Fraction &operator=(Fraction &&);           // Move assignment
    Fraction operator+(int) const;              // Add Fraction + int
    Fraction operator+(const Fraction &) const; // Add Fraction + Fraction
    Fraction operator-() const;                 // unary minus
    Fraction operator-(int) const;              // binary minus: Frac - int
    Fraction operator-(const Fraction &) const; // binary minus: Frac - Frac
    Fraction operator*(int)const;               // Multiply: Frac * int
    Fraction operator*(const Fraction &)const;  // Multiply: Frac * Frac
    Fraction operator/(int)const;               // Divide: Frac / int
    Fraction operator/(const Fraction &)const;  // Divide: Frac / Frac
    Fraction operator^(int)const;               // Power: Frac ^ int
    Fraction operator^(const Fraction &)const;  // Power: Frac ^ Frac
    bool operator<(const Fraction &) const;     // Compare Frac < Frac
    bool operator>(const Fraction &) const;     // Compare Frac > Frac
    bool operator==(const Fraction &) const;    // Compare Frac == Frac
    optional<int> operator[](int) const;        // Component access Frac[i]

#if I_DO_EXTRA_CREDIT
    // Implement these two OR add your own operator(s)
    optional<string> isRepeating() const;
    string operator()(int) const;
#endif

  private:
    ostream &writeTo(ostream &) const;
    istream &readFrom(istream &);
    bool isWhole = false;
    bool isPositiveValue = false;
    bool isFraction = false;
    int wholeVal = 0;
    int numVal = 0;
    int denomVal = 1;
};

/* Friend functions (non-member functions) */
ostream &operator<<(ostream &, const Fraction &);
istream &operator>>(istream &, Fraction &);
Fraction operator+(int, const Fraction &); // Add: int + Fraction