#include "BigInt.h"
#include <string>
#include <sstream>

using namespace std;

void BigInt::complement(BigInt& a) {
    // set placeholder node to tail
    DigitNode *current = tail;

    // add one first and carry
    int carry = 1;

    // for the length of the number
    for(int i = 0; i < length; i++) {
        // do math and convert to ascii char equivalents
        int digit = current->digit - '0';
        char newDigit = ((9-digit+carry) % 10) + '0';
        carry = newDigit/10;
        current->digit = newDigit;

        // iterate placeholder backwards
        current = current->previous;
    }
}

void BigInt::push_front(char a) { }

void BigInt::push_back(char a) { }

BigInt::BigInt() {
    head = NULL;
    tail = NULL;
    negative = false;
    length = 0;
}

BigInt::BigInt(const BigInt& b) {
    // copy constructor
}

void BigInt::init(string digits) {
    int c = digits.find('-');

    // compute offset from front, to capture only digits
    if (c != string::npos) {
        negative = true;
    } else {
        c = 0;
    }

    // cut off ending spaces if needed
    // replace with digits.length if needed
    while (c < digits.find_last_not_of(' ')) {
        push_front(digits[c]);
        length++;
        c++;
    }

}

BigInt operator+(BigInt a, BigInt b) {
    // check for negatives
    // complement the negative
    // add padding zeros until both lengths are max(a.length, b.length) + 2
    // create placeholder variable for answer

    // set carry to 0
    // set two pointers to tails for iteration

    // FOR length of answer max(a.length, b.length) + 1
        // convert chars to int via ascii offset (subtract '0')
        // answerDigit = (a+b)%10 + carry;
        // set carry to (a+b)/10;
        // convert answer back to ascii (add '0') and answer.push_front(answerDigit);
        // iterate both pointers backwards
    // end FOR

    // remove padding zeros from answer

    // if a or b is negative and first digit in the answer is 9
        // set answer's negative to true
        // take complement
    // return answer
}

string BigInt::toString() {
    stringstream ss;

    // if not empty
    if (head!=NULL) {
        DigitNode *current = head;

        // add first element
        ss << current->digit;

        // add more if next isn't null
        while (current->hasNext()) {
            current = current->next;
            ss << current->digit;
        }
    }
    return ss.str();
}

BigInt::~BigInt() {}
