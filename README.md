# MyFraction (Project 2)

CIS 343 Project 2 - MyFraction

In this assignment you will be writing a C++ class for manipulating fractions. 

## Developing Your Solution

You will be writing only a few lines of code in Fraction.h. The only changes needed are:

- Define instance variable(s) in the private section
- Define private helper function(s), such as for calculating GCD or LCM of two integers, and other helper functions as you see fit
- Add your own function signatures/prototypes if you decide to earn the extra points
- The biggest amount of code of your solution will go to one file: Fraction.cpp. Throughout this file you'll notice function name prefixed with `Fraction::` scope to identify where the name belongs to.

## Compiling the Project

This creates a builded/compiled folder of all files needed for running the specific tests.

```
mkdir build
cd build
cmake .. 
```

## Testing the project

This looks for the runtest file to run all of the tests against using the C++ testing library

```
make
./runtest
```

## Created By
Adam Chlebek (2019)