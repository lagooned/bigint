BigIntTest: BigIntTest.o
	g++ -o BigIntTest BigIntTest.o BigInt.o

BigIntTest.o: BigIntTest.cpp BigInt.cpp
	g++ -c BigInt.h BigInt.cpp BigIntTest.cpp

clean:
	rm *.o *.gch BigIntTest
