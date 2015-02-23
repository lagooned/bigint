#include "BigInt.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

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
 * pop extra buffer zeros
 */
void BigInt::pop_zeros() {
    while (head->digit == '0') {
        pop_front();
    }
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
    clear();
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

    // clear out old number before adding a new one
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
    for (int i = start + 1; i <= digits.length() - 1; i++) {
        push_back(digits[i]);
    }
}

/**
 * Adding algorithm
 * (makes copies before adding)
 * @throws -1 if invalid operands
 */
BigInt BigInt::operator+(BigInt b) {
    BigInt a = *this;

    if (a.head == NULL || b.head == NULL) {
        throw -1;
    } else {
        // create placeholder BigInt for answer
        BigInt answer;

        // add padding zeros until both lengths are max(a.length, b.length) + 2
        int newLength = max(a.length, b.length) + 2;

        while (a.length < newLength) { a.push_front('0'); }
        while (b.length < newLength) { b.push_front('0'); }

        cout << endl << "After buffer zeros: " << a.toString() << " + " << b.toString() << endl;

        // check for negatives and complement
        if (a.negative) { complement(a); }
        if (b.negative) { complement(b); }

        cout << "After Complement: " << a.toString() << " + " << b.toString() << endl;

        // set carry to 0
        int carry = 0;

        // set two pointers to tails for iteration
        DigitNode * a_current = a.tail;
        DigitNode * b_current = b.tail;


        // // FOR length of answer newLength
        while (a_current != NULL) {
             // convert chars to int via ascii offset (subtract '0')
             int a = a_current->digit - '0';
             int b = b_current->digit - '0';

             // compute digit
             int answerDigit = (a + b + carry) % 10;

             // set carry
             carry = (a + b + carry)/10;

             cout << "a: " << a << " b: " << b << " digit: " << answerDigit << " carry: " << carry << endl;

             // convert answer back to ascii (add '0') and answer.push_front(answerDigit);
             answer.push_front(answerDigit + '0');

             // iterate both pointers backwards
             a_current = a_current->previous;
             b_current = b_current->previous;
        }

        //if first digit in the answer is 9
        if (answer.head->digit == '9') {
            // set answer's negative to true
            answer.negative = true;
            // take complement
            complement(answer);
        }

        return answer;
    }
}

/*
 * (private)
 * destructive complement - used by addition algorithm
 */
void BigInt::complement(BigInt& a) {

    // set placeholder node to tail
    DigitNode * current = a.tail;

    // push a 0 to take care of possible rollover
    // a.push_front('0');

    // add one first and carry
    int carry = 1;

    // for the length of the number
    while(current != NULL) {
        // do math and convert to ascii char equivalents
        int digit = current->digit - '0';

        int calcPlusOne = 9-digit+carry;

        int newDigit = (calcPlusOne % 10);

        carry = (calcPlusOne)/10;

        current->digit = newDigit + '0';

        // iterate placeholder backwards
        current = current->previous;
    }
}

/**
 * @returns string reprisenting BigInt
 */
string BigInt::toString() {
    stringstream ss;

    // if not empty
    if (head != NULL) {
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
 * destructer
 */
BigInt::~BigInt() {
    clear();
}
