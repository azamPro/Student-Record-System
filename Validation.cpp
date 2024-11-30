#include "Validation.h"

// Function to validate numeric input
int getValidNumericInput(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a valid number." << endl;
        } else {
            return value;
        }
    }
}

// Function to validate string input
string getValidStringInput(string prompt) {
    string value;
    while (true) {
        cout << prompt;
        cin.ignore(); // Clear leftover newline
        getline(cin, value);

        if (value.empty()) {
            cout << "Input cannot be empty. Please try again." << endl;
        } else {
            return value;
        }
    }
}

// Function to validate phone numbers
string getValidPhoneNumber(string prompt) {
    string phoneNumber;
    regex phonePattern("^05\\d{8}$"); // Saudi phone number format

    while (true) {
        cout << prompt;
        cin >> phoneNumber;

        if (regex_match(phoneNumber, phonePattern)) {
            return phoneNumber;
        } else {
            cout << "Invalid phone number. Please enter a 10-digit Saudi phone number starting with 05." << endl;
        }
    }
}
