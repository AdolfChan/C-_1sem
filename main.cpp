
#include <iostream>
#include "BigIntHeader.h"
using namespace std;

int main() {
	string str = "4213421421421441341312321312312312";
	BigInt a(str);
	string str2 = "100312323213122";
	const BigInt b(str2);
	cout << a + 2 << endl;
	cout << ++a << endl;
	cout << -a-- << endl;
	cout << b - a << endl;
	cout << a * b << endl;
	cout << b / 312 << endl;
	cout << b % 9 << endl;
	return 0;
}
