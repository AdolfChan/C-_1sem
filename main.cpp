#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class bigInt {
    friend const bigInt operator-(bigInt, const bigInt&);
    friend const bigInt operator+(bigInt, const bigInt&);
    friend bool operator<(const bigInt&, const bigInt&);
    friend const bigInt operator*(bigInt, long long);
    friend const bigInt operator/(bigInt, long long);

public:
    static const int BASE = 1000000000;

    vector<int> lnum;

    bool isNegative;

    bigInt() { this->isNegative = false; };

    bigInt(string str) {
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

    const bigInt operator-() const {
        bigInt copy(*this);
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

ostream& operator<<(ostream& os, const bigInt& bi) {
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

const bigInt operator+(bigInt left, const bigInt& right) {
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
        carry = left.lnum[i] >= bigInt::BASE;

        if (carry != 0) left.lnum[i] -= bigInt::BASE;
    }
    left.remove_zeroes();
    return left;
}

bool operator<(const bigInt& left, const bigInt& right) {
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

const bigInt operator-(bigInt left, const bigInt& right) {
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
        if (carry != 0) left.lnum[i] += bigInt::BASE;
    }

    left.remove_zeroes();
    return left;
}

const bigInt operator*(bigInt left, const bigInt& right) {
    bigInt result;
    result.lnum.resize(left.lnum.size() + right.lnum.size());

    for (size_t i = 0; i < left.lnum.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.lnum.size() || carry != 0; ++j) {
            long long cur =
                result.lnum[i + j] +
                left.lnum[i] * 1LL * (j < right.lnum.size() ? right.lnum[j] : 0) +
                carry;
            result.lnum[i + j] = (int)(cur % bigInt::BASE);
            carry = (int)(cur / bigInt::BASE);
        }
    }
    result.isNegative = left.isNegative != right.isNegative;
    result.remove_zeroes();
    return result;
}

const bigInt operator/(bigInt left, long long right) {
    int carry = 0;
    for (int i = (int)left.lnum.size() - 1; i >= 0; --i) {
        long long cur = left.lnum[i] + carry * 1ll * bigInt::BASE;
        left.lnum[i] = int(cur / right);
        carry = int(cur % right);
    }
    left.remove_zeroes();
    return left;
}

const long long operator%(bigInt left, long long right) {
    int carry = 0;
    for (int i = (int)left.lnum.size() - 1; i >= 0; --i) {
        long long cur = left.lnum[i] + carry * 1ll * bigInt::BASE;
        left.lnum[i] = int(cur / right);
        carry = int(cur % right);
    }
    left.remove_zeroes();
    return carry;
}

int main() {
    bigInt a("1003123123122");
    bigInt b("1003123123123214124124124124");
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << b / 4 << endl;
    cout << a % 2 << endl;
    return 0;
}
