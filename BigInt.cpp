#include "BigInt.h"
#include <string>
#include <sstream>

using namespace std;

/**
 * returns least significant digit and removes it
 * @throws -1 if number is empty
 */
char BigInt::pop_front() {
    char digit;

    if (head == NULL || length <= 0) {
        throw -1;
    } else {
        // hold onto head
        DigitNode * temp = head;

        // get data
        digit = head->digit;

        // setup new head and tail
        if (head->hasNext()) {
            head->next->previous = NULL;
            head = head->next;
        } else {
            head = NULL;
            tail = NULL;
        }

        // now references are correct, delete the old head
        delete temp;

        // decrement length
        length--;
    }
    return digit;
}

void BigInt::push_front(char a) {
    // new head has no previous
    // next is the old head
    head = new DigitNode(a, NULL, head);


    if (length <= 0) {
        // if there is one node
        // head and tail are the same
        tail = head;
    } else {
        // if there is more than one node
        // setup the new node's next
        // to be where the head is
        head->next->previous = head;
    }

    length++;
}

void BigInt::push_back(char a) {
    // new tail prev points is old tail
    // next is null
    tail = new DigitNode(a, tail, NULL);


    if (length <= 0) {
        // if there is one node
        // tail and head are the same
        head = tail;
    } else {
        // if there is more than one
        // setup previous reference to
        // newly created node
        tail->previous->next = tail;
    }

    length++;
}

void BigInt::clear() {
    if (head != NULL) {
        DigitNode* current = head;
        DigitNode* last = NULL;

        // clean up
        while (current->hasNext()) {
            last = current;
            current = current->next;
            delete last;
        }
    }

    // reset all values
    head = NULL;
    tail = NULL;
    negative = false;
    length = 0;
}

BigInt::BigInt() {
    head = NULL;
    tail = NULL;
    negative = false;
    length = 0;
}

BigInt::BigInt(const BigInt& b) {
    // TODO: copy constructor
    // needed for operator+
}

void BigInt::init(string digits) {

    // TODO: clear out old number before adding a new one
    clear();

    // find negative
    int start = digits.find('-');

    // if pos of new start is greater
    // than negative 1
    if (start > -1) {
        // there is a negative sign
        // in a valid spot in the number
        negative = true;
    }

    // from the start of the number to the end of the string
    for (int i = start + 1; i <= digits.length(); i++) {
        push_back(digits[i]);
    }

}

BigInt operator+(BigInt a, BigInt b) {
    // TODO: IMPLEMENT THIS

    // check for negatives
    // complement the negative

    // add padding zeros until both lengths are max(a.length, b.length) + 2
    // create placeholder BigInt for answer

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

/**
 * Destructive complement - used by addition
 * algorithm
 */
void BigInt::complement(BigInt& a) {
    // set placeholder node to tail
    DigitNode * current = a.tail;

    // push a 0 to take care of possible rollover
    a.push_front('0');

    // add one first and carry
    int carry = 1;

    // for the length of the number
    for(int i = 0; i < a.length; i++) {
        // do math and convert to ascii char equivalents
        int digit = current->digit - '0';
        char newDigit = ((9-digit+carry) % 10) + '0';
        carry = newDigit/10;
        current->digit = newDigit;

        // iterate placeholder backwards
        current = current->previous;
    }

    // remove buffer zeros if needed
    while (a.head->digit == '0') {
        pop_front();
    }
}

string BigInt::toString() {
    stringstream ss;

    // if not empty
    if (head!=NULL) {
        DigitNode * current = head;

        if (negative) {
            ss << "-";
        }

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

BigInt::~BigInt() {
    clear();
}
