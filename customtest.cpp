#define CATCH_CONFIG_MAIN

#include "Fraction.h"

#include "catch.hh"
#include <sstream>

TEST_CASE("Power"){
    SECTION("Power with Positive Value"){
        Fraction f{"3 6/7"};
        Fraction prod;

        prod = f ^ 3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 57);
        CHECK(prod.numerator() == 132);
        CHECK(prod.denominator() == 343);
    }
    
    SECTION("Power with negative Value"){
        Fraction f{"3 6/7"};
        Fraction prod;

        prod = f ^ -3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 343);
        CHECK(prod.denominator() == 19683);
    }

        SECTION("Power with Positive Value less than 1"){
        Fraction f{"6/7"};
        Fraction prod;

        prod = f ^ 3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 216);
        CHECK(prod.denominator() == 343);
    }
    
    SECTION("Power with negative Value less than 1"){
        Fraction f{"6/7"};
        Fraction prod;

        prod = f ^ -3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 1);
        CHECK(prod.numerator() == 127);
        CHECK(prod.denominator() == 216);
    }

    SECTION("Negative Power with Positive Value"){
        Fraction f{"-3 6/7"};
        Fraction prod;

        prod = f ^ 3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 57);
        CHECK(prod.numerator() == 132);
        CHECK(prod.denominator() == 343);
    }
    
    SECTION("Negative Power with negative Value"){
        Fraction f{"-3 6/7"};
        Fraction prod;

        prod = f ^ -3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 343);
        CHECK(prod.denominator() == 19683);
    }

    SECTION("Negative Power with Positive Value less than 1"){
        Fraction f{"-6/7"};
        Fraction prod;

        prod = f ^ 3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 216);
        CHECK(prod.denominator() == 343);
    }
    
    SECTION("Negative Power with negative Value less than 1"){
        Fraction f{"-6/7"};
        Fraction prod;

        prod = f ^ -3;
        CHECK(prod.isPositive());
        CHECK(prod.whole() == 1);
        CHECK(prod.numerator() == 127);
        CHECK(prod.denominator() == 216);
    }
}

TEST_CASE("Division") {
    SECTION("Division with scalar on right") {
        Fraction one{"3 6/17"};

        Fraction prod;
        prod = one / 6;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 19);
        CHECK(prod.denominator() == 34);
    }

    SECTION("Division with scalar on left") {
        Fraction one{"3 6/17"};

        Fraction prod;
        prod = one / 6;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 19);
        CHECK(prod.denominator() == 34);
    }

    SECTION("Division with -1") {
        Fraction one{"3 6/17"};

        Fraction prod;
        prod = one / -1;

        CHECK_FALSE(prod.isPositive());
        CHECK(prod.whole() == 3);
        CHECK(prod.numerator() == 6);
        CHECK(prod.denominator() == 17);
    }

    SECTION("Divide two positive fractions") {
        Fraction one{"5 11/19"};
        Fraction two{"4 3/7"};

        Fraction prod;
        prod = one / two;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 1);
        CHECK(prod.numerator() == 153);
        CHECK(prod.denominator() == 589);
    }

    SECTION("Divide two negative fractions") {
        Fraction one{"-5 11/19"};
        Fraction two{"-4 3/7"};

        Fraction prod;
        prod = one / two;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 1);
        CHECK(prod.numerator() == 153);
        CHECK(prod.denominator() == 589);
    }

    SECTION("Divide two fractions of different sign") {
        Fraction one{"5 11/19"};
        Fraction two{"-4 3/7"};

        Fraction prod;
        prod = one / two;

        CHECK_FALSE(prod.isPositive());
        CHECK(prod.whole() == 1);
        CHECK(prod.numerator() == 153);
        CHECK(prod.denominator() == 589);
    }
}

TEST_CASE("Operator>") {
    SECTION("Different sign") {
        Fraction a{"-10 5/7"};
        Fraction b{"3 17/20"};
        CHECK(a > b);
        CHECK_FALSE(b > a);
    }

    SECTION("Both positive") {
        Fraction a{"10 5/7"};
        Fraction b{"3 17/20"};
        CHECK_FALSE(a > b);
        CHECK(b > a);
    }

    SECTION("Both negative: mixed and fraction") {
        Fraction a{"-5/6"};
        Fraction b{"-1 17/20"};
        CHECK_FALSE(a > b);
        CHECK(b > a);
    }

    SECTION("Both positive: mixed and fraction only") {
        Fraction a{"15/3"};
        Fraction b{"1 20/20"};
        CHECK_FALSE(a > b);
        CHECK(b > a);
    }
}