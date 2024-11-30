#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <string>
#include <regex>
#include <limits>

using namespace std;

// Function declarations
int getValidNumericInput(string prompt);
string getValidStringInput(string prompt);
string getValidPhoneNumber(string prompt);

#endif // VALIDATION_H
