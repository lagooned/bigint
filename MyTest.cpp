#include "BigInt.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    BigInt a, b, x, y;

    // accepts zero case w/o seg fault
    a.init("0");
    b.init("0");
    x = a + b;
    cout << x.toString() << endl;

    // output zeros
    a.init("-1");
    b.init("1");
    x = a + b;
    cout << x.toString() << endl;
    a.init("99");
    b.init("-99");
    x = a + b;
    cout << x.toString() << endl;

    // accepts weird inputs bc of char usage
    a.init("jkdlskdfj");
    b.init("djfldskdf");
    x = a + b;
    cout << x.toString() << endl;

    // multiple assignment statements
    a.init("100");
    b.init("100");
    y = x = a + b;
    cout << y.toString() << endl;
    cout << x.toString() << endl;

    return 0;
}
