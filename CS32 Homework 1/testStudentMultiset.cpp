#include "StudentMultiset.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	StudentMultiset A;
	assert(A.add(2));
	assert(A.add(4));
	assert(A.add(6));
	assert(A.add(5));
	assert(A.add(4));
	assert(A.add(4));
	assert(A.add(5));

	assert(A.size() == 7);
	assert(A.add(2));
	assert(A.size() == 8);

	A.print();
}

int main()
{
	test();
	cout << endl;
	cout << "Passed all tests" << endl;
} 