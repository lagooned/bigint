#include "BigInt.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    BigInt a, b, result;

    string operand1[16] = {"2", "2", "-2", "-2", "984", "984", "-984", "-984",
                           "528197654789", "528197654789",
                           "-528197654789", "-528197654789",
                           "7365432514328679409876534",
                           "7365432514328679409876534",
                           "-7365432514328679409876534",
                           "-7365432514328679409876534" };

    string operand2[16] = {"3", "-3", "3", "-3", "123", "-123", "123", "-123",
                           "617018112091", "-617018112091", "617018112091",
                           "-617018112091", "76541329276", "-76541329276",
                           "76541329276", "-76541329276" };


    for (int i = 0; i < 16; i++)
    {
        a.init(operand1[i]);
        b.init(operand2[i]);

        cout << a.toString() << " + " << b.toString() << endl;
        cout << "--------------------------------------";
        result = a + b;
        cout << result.toString() << endl << endl;

        //    << result.toString() << endl;
    }

    return 0;
}
