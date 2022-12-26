#include <iostream>
#include "BigIntHeader.h"
using namespace std;



int main() {
    BigInt a("1003123123122321312312312312312");
    BigInt b("100321312312412421313123122");
    cout << a + 2 << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << b / 4 << endl;
    cout << a % 12 << endl;
    return 0;
    
}
