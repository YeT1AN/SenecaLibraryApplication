/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 8 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include "Utils.h"

using namespace std;
namespace sdds {
    unsigned int getIntMM(unsigned int min, unsigned int max) {
        unsigned int input = 0;
        bool done = false;
        while (!done) {
            cin >> input;
            if (!cin || input < min || input > max) {
                std::cout << "Invalid Selection, try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
                done = false;
            }
            else {
                done = true;
            }
        }
        return input;
    }
    int numLen(int n) {
        int i = 0;
        if (n > 0) {
            while (n != 0) {
                n = n / 10;
                i++;
            }
        }
        if (n < 0) i = -1;
        return i;
    }
}
