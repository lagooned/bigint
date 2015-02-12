#include <string>

#ifndef _BIGINT_H_
#define _BIGINT_H_

using namespace std;

class BigInt {
    private:
        class DigitNode {
            public:
                unsigned char digit;
                DigitNode *previous, *next;

                DigitNode(unsigned char digit, DigitNode *previous,
                          DigitNode *next)
                {
                    this->digit = digit;
                    this->previous = previous;
                    this->next = next;
                }

                bool hasNext() { return !(next == NULL); }
                bool hasPrev() { return !(previous == NULL); }
        };

        DigitNode *head, *tail;
        int length;
        bool negative;

        void complement(BigInt&);
        void push_front(char);
        void push_back(char);
        unsigned char peek_front(int offset = 0);
        unsigned char peek_back(int offset = 0);

    public:
        BigInt();
        BigInt(const BigInt&);
        void init(string);
        friend BigInt operator+(BigInt, BigInt);
        string toString();
        ~BigInt();
};

#endif
