all: MyTest BigIntTest

MyTest: MyTest.o
	g++ -o MyTest MyTest.o BigInt.o

MyTest.o: MyTest.cpp BigInt.cpp
	g++ -c BigInt.h BigInt.cpp MyTest.cpp

BigIntTest: BigIntTest.o
	g++ -o BigIntTest BigIntTest.o BigInt.o

BigIntTest.o: BigIntTest.cpp BigInt.cpp
	g++ -c BigInt.h BigInt.cpp BigIntTest.cpp

test:
	./MyTest && ./BigIntTest

clean:
	rm *.o *.gch *.stackdump BigIntTest MyTest
