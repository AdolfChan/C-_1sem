#pragma once
#ifndef MAN_H_
#define MAN_H_
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class BigInt {
    friend ostream& operator<<(std::ostream&, const BigInt&);
    friend BigInt operator-(BigInt, const BigInt&);
    BigInt operator -=(const BigInt&);
    friend BigInt operator+(BigInt, const BigInt&);
    BigInt operator +=(const BigInt&);
    const BigInt operator ++();
    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator !=(const BigInt&, const BigInt&);
    friend bool operator <=(const BigInt&, const BigInt&);
    friend bool operator >(const BigInt&, const BigInt&);
    friend bool operator >=(const BigInt&, const BigInt&);
    friend BigInt operator*(BigInt&, const BigInt&);
    BigInt operator *=(const BigInt&);
    friend BigInt operator/(BigInt, long long);
    friend BigInt operator%(BigInt, long long);

public:

    BigInt(int);
    BigInt(size_t);
    BigInt(char);
    BigInt(short);
    BigInt(long);
    BigInt(long long);

    std::vector<int> lnum;
    bool isNegative;
    static const int BASE = 1000000000;
    BigInt() { this->isNegative = false; };

    BigInt(std::string str) {
        if (str.length() == 0) {
            this->isNegative = false;
        }
        else {
            if (str[0] == '-') {
                str = str.substr(1);
                this->isNegative = true;
            }
            else {
                this->isNegative = false;
            }

            for (long long i = str.length(); i > 0; i -= 9) {
                if (i < 9)
                    this->lnum.push_back(atoi(str.substr(0, i).c_str()));
                else
                    this->lnum.push_back(atoi(str.substr(i - 9, 9).c_str()));
            }

            this->remove_zeroes();
        }
    }

    BigInt& operator-() const {
        BigInt copy(*this);
        copy.isNegative = !copy.isNegative;
        return copy;
    }

    void remove_zeroes() {
        while (this->lnum.size() > 1 && this->lnum.back() == 0) {
            this->lnum.pop_back();
        }

        if (this->lnum.size() == 1 && this->lnum[0] == 0) this->isNegative = false;
    }

};
#endif