/*
 * This program was developed for Coding theory subject in NSU.
 * It can make a division your numerator-polynomial by your denominator-polynomial in the number-field of 'module' elements.
 */

#include <iostream>

using namespace std;

void printPoly(string polyStr) {
    int r = (int) polyStr.length() - 1;
    for (int i = 0; i <= r; i++) {
        if (i == 0) printf("%c", polyStr[i]);
        else {
            if (i == 1) {
                printf("%cx", polyStr[i]);
            } else {
                printf("%cx^%d", polyStr[i], i);
            }
        }
        if (i != r) printf("+");
    }
    printf("\n");
}

int c2i(char c) {
    return c - 48;
}

char i2c(int i) {
    return (char) (i + 48);
}

int main() {
    int module; //module of the number-field
    cout << "Please, input your module: ";
    cin >> module;

    if (module < 2) {
        cout << "FAILED! Your module is less then two!\n";
        return 0;
    }

    string numerator;
    cout << "Please, input your numerator-polynomial: ";
    cin >> numerator;
    printPoly(numerator);

    string denominator = "01";
    cout << "Please, input your denominator-polynomial: ";
    cin >> denominator;
    printPoly(denominator);

    int polySize = (int) denominator.size();
    int currSize = (int) numerator.size();
    int diffSizes = currSize - polySize;

    string h;
    for (int i = 0; i <= diffSizes; i++)h += "0";

    while (diffSizes >= 0) {
        int mul = 1;
        int divLast = c2i(numerator[currSize - 1]);
        int polyLast = c2i(denominator[currSize - 1 - diffSizes]);
        while (divLast > polyLast * mul) mul++;

        if (divLast != polyLast * mul) {
            cout << "FAILED finding of multiplier for poly!\n";
            return 0;
        }

        h[diffSizes] = i2c(mul);
        if (numerator[currSize - 1]) {
            for (int i = currSize - 1; i >= currSize - polySize; i--) {
                int rem = (module + c2i(numerator[i]) - (c2i(denominator[i - diffSizes]) * mul) % module) % module;
                numerator[i] = i2c(rem);
            }
        }

        int pos = currSize - 1;
        while (pos >= 0 && numerator[pos] == '0') {
            numerator.erase(pos, 1);
            pos--;
        }
        currSize = (int) numerator.size();
        diffSizes = currSize - polySize;
    }

    cout << "Result vector : " << h << endl;
    cout << "Result of division : ";
    printPoly(h);

    if (!numerator.empty()) {
        cout << "Remainder vector : " << numerator << endl;
        cout << "Remainder of div : ";
        printPoly(numerator);
    } else {
        cout << "Division without remainder!" << endl;
    }
    return 0;
}
