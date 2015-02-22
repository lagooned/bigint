#include "BigInt.h"
#include <string>
#include <sstream>

using namespace std;

/*
 * (private)
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

/*
 * (private)
 * add character a to the start of the list
 */
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

/*
 * (private)
 * add character a to the end of the list
 */
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

/*
 * (private)
 * free memory and reset member vars
 */
void BigInt::clear() {
    if (head != NULL) {
        DigitNode * current = head;
        DigitNode * last = NULL;

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

/**
 * default constructor
 */
BigInt::BigInt() {
    head = NULL;
    tail = NULL;
    negative = false;
    length = 0;
}

/**
 * copy constructor
 */
BigInt::BigInt(const BigInt& b) {
    copy_from(b);
}

/**
 * equals operator
 */
BigInt& BigInt::operator=(const BigInt& b) {
    copy_from(b);
    return *this;
}

/*
 * (private)
 * used to implement same functionality in both
 * copy constructor and equals operator
 */
void BigInt::copy_from(const BigInt& b) {
    // set negative
    negative = b.negative;

    // init length
    length = 0;

    // if b has digits
    if (b.head != NULL) {

        // set placeholder
        DigitNode * current = b.head;

        // push first one
        push_back(current->digit);

        // while there is a next digit
        while (current->hasNext()) {

            // iterate placeholder
            current = current->next;

            // push said digit
            push_back(current->digit);
        }
    }

    // there are no digits
    else {
        head = NULL;
        tail = NULL;
    }
}

/**
 * clear out old number and add new digits
 */
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

/*
 * (private)
 * destructive complement - used by addition algorithm
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

/**
 * @returns string reprisenting BigInt
 */
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

/**
 * destructer
 */
BigInt::~BigInt() {
    clear();
}
