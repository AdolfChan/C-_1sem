
#include <iostream>
#include "BigIntHeader.h"
using namespace std;

int main() {
	string str = "4213421421421441341312321312312312";
	BigInt a(str);
	string str2 = "41344214123123123123123";
	BigInt b(str2);

	cout << a + 2 << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << b / 4 << endl;
	cout << a % 12 << endl;
	return 0;
}
