#include <iostream>
#include <vector>
#include <iomanip>
#include "BigIntHeader.h"
using namespace std;


// Преобразование 
BigInt::BigInt(int i) {
    if (i > 0)
        this->isNegative = false;
    else
        this->isNegative = true;

    this->lnum.push_back(abs(i) % BigInt::BASE);
    i /= BigInt::BASE;
    if (i != 0) this->lnum.push_back(abs(i));
}

BigInt::BigInt(long i) {
    if (i > 0)
        this->isNegative = false;
    else
        this->isNegative = true;

    this->lnum.push_back(abs(i) % BigInt::BASE);
    i /= BigInt::BASE;
    if (i != 0) this->lnum.push_back(abs(i));

}
BigInt::BigInt(long long i) {
    if (i > 0)
        this->isNegative = false;
    else 
        this->isNegative = true;
    do {
        this->lnum.push_back(abs(i) % BigInt::BASE);
        i /= BigInt::BASE;
    } while (i != 0);

}

BigInt::BigInt(size_t i) {
    this->isNegative = false;

    this->lnum.push_back(i % BigInt::BASE);
    i /= BigInt::BASE;
    if (i != 0) this->lnum.push_back(i);
}

BigInt::BigInt(char i) {
    if (i > 0)
        this->isNegative = false;
    else
        this->isNegative = true;
    this->lnum.push_back(std::abs(i));
}

BigInt::BigInt(short i) {
    if (i > 0)
        this->isNegative = false;
    else
        this->isNegative = true;
    this->lnum.push_back(std::abs(i));
}


ostream& operator<<(ostream& os, const BigInt& bi) {
    if (bi.lnum.empty())
        os << 0;
    else {
        if (bi.isNegative) os << '-';
        os << bi.lnum.back();
        for (int i = (int)bi.lnum.size() - 2; i >= 0; --i)
            os << setw(9) << setfill('0') << bi.lnum[i];
    }
    return os;
}

BigInt operator+(BigInt left, const BigInt& right) {
    if (left.isNegative) {
        if (right.isNegative)
            return -(-left + (-right));
        else
            return right - (-left);
    }
    else if (right.isNegative)
        return left - (-right);

    int carry = 0;
    for (size_t i = 0;
        i < std::max(left.lnum.size(), right.lnum.size()) || carry != 0; ++i) {
        if (i == left.lnum.size()) left.lnum.push_back(0);

        left.lnum[i] += carry + (i < right.lnum.size() ? right.lnum[i] : 0);
        carry = left.lnum[i] >= BigInt::BASE;

        if (carry != 0) left.lnum[i] -= BigInt::BASE;
    }
    left.remove_zeroes();
    return left;
}

BigInt BigInt::operator +=(const BigInt& value) {
    return *this = (*this + value);
}
const BigInt BigInt::operator++() {
    return (*this += 1);
}

bool operator<(const BigInt& left, const BigInt& right) {
    if (left.isNegative) {
        if (right.isNegative)
            return ((-right) < (-left));
        else
            return true;
    }
    else if (right.isNegative)
        return false;
    else {
        if (left.lnum.size() != right.lnum.size()) {
            return left.lnum.size() < right.lnum.size();
        }
        else {
            for (long long i = left.lnum.size() - 1; i >= 0; --i) {
                if (left.lnum[i] != right.lnum[i]) return left.lnum[i] < right.lnum[i];
            }

            return false;
        }
    }
}
bool operator ==(const BigInt& left, const BigInt& right) {

    if (left.isNegative != right.isNegative) return false;

    if (left.lnum.empty()) {
        if (right.lnum.empty() || (right.lnum.size() == 1 && right.lnum[0] == 0)) return true;
        else return false;
    }

    if (right.lnum.empty()) {
        if (left.lnum.size() == 1 && left.lnum[0] == 0) return true;
        else return false;
    }

    if (left.lnum.size() != right.lnum.size()) return false;
    for (long long i = 0; i < left.lnum.size(); ++i)
        if (left.lnum[i] != right.lnum[i]) return false;

    return true;
}
bool operator >(const BigInt& left, const BigInt& right) {
    return !(left <= right);
}
bool operator !=(const BigInt& left, const BigInt& right) {
    return !(left == right);
}

bool operator <=(const BigInt& left, const BigInt& right) {
    return !(right < left);
}

bool operator >=(const BigInt& left, const BigInt& right) {
    return !(left < right);
}

BigInt operator-(BigInt left, const BigInt& right) {
    if (right.isNegative)
        return left + (-right);
    else if (left.isNegative)
        return -(-left + right);
    else if (left < right)
        return -(right - left);

    int carry = 0;
    for (size_t i = 0; i < right.lnum.size() || carry != 0; ++i) {
        left.lnum[i] -= carry + (i < right.lnum.size() ? right.lnum[i] : 0);
        carry = left.lnum[i] < 0;
        if (carry != 0) left.lnum[i] += BigInt::BASE;
    }

    left.remove_zeroes();
    return left;
}

BigInt BigInt::operator -=(const BigInt& value) {
    return *this = (*this - value);
}

BigInt operator*(BigInt& left, const BigInt& right) {
    BigInt result;
    result.lnum.resize(left.lnum.size() + right.lnum.size());

    for (size_t i = 0; i < left.lnum.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.lnum.size() || carry != 0; ++j) {
            long long cur =
                result.lnum[i + j] +
                left.lnum[i] * 1LL * (j < right.lnum.size() ? right.lnum[j] : 0) +
                carry;
            result.lnum[i + j] = (int)(cur % BigInt::BASE);
            carry = (int)(cur / BigInt::BASE);
        }
    }
    result.isNegative = left.isNegative != right.isNegative;
    result.remove_zeroes();
    return result;
}

BigInt BigInt::operator *=(const BigInt& value) {
    return *this = (*this * value);
}

BigInt operator/(BigInt left, long long right) {
    int carry = 0;
    for (int i = (int)left.lnum.size() - 1; i >= 0; --i) {
        long long cur = left.lnum[i] + carry * 1ll * BigInt::BASE;
        left.lnum[i] = int(cur / right);
        carry = int(cur % right);
    }
    left.remove_zeroes();

    return left;
}

BigInt operator%(BigInt left, long long right) {
    int carry = 0;
    for (int i = (int)left.lnum.size() - 1; i >= 0; --i) {
        long long cur = left.lnum[i] + carry * 1ll * BigInt::BASE;
        left.lnum[i] = int(cur / right);
        carry = int(cur % right);
    }
    left.remove_zeroes();

    return carry;
}
