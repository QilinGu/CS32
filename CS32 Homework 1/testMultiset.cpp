#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Multiset ulms;
	Multiset A;
	assert(ulms.empty());
	assert(ulms.insert(20));
	assert(ulms.insert(10));
	assert(ulms.insert(20));
	assert(ulms.insert(30));
	assert(ulms.insert(20));
	assert(ulms.insert(10));
	assert(ulms.size() == 6 && ulms.uniqueSize() == 3);
	assert(ulms.count(10) == 2);
	assert(ulms.count(20) == 3);
	assert(ulms.count(30) == 1);
	assert(ulms.count(40) == 0);
	assert(ulms.erase(10) == 1);
	assert(ulms.count(10) == 1);
	assert(ulms.eraseAll(20) == 3);
	assert(ulms.count(20) == 0);
	assert(!ulms.contains(20));
	assert(ulms.insert(10));
	assert(ulms.count(10) == 2);

	assert(!ulms.empty());
	assert(A.empty());
	assert(A.insert(20));
	assert(A.insert(20));
	assert(A.insert(20));
	assert(A.insert(20));
	assert(A.insert(30));
	assert(A.insert(30));
	assert(A.insert(40));
	assert(A.size() == 7);
	assert(A.uniqueSize() == 3);
	assert(A.contains(30));
	assert(!A.contains(10));
	assert(A.count(30) == 2);
	unsigned long x;
	assert(A.get(0, x) == 4);
	assert(x == 20);
	assert(A.get(1, x) == 2);
	assert(x == 30);
	assert(A.get(2, x) == 1);
	assert(x == 40);

	A.swap(ulms);
	assert(A.count(10) == 2);
	assert(A.count(20) == 0);
	assert(A.count(30) == 1);
	assert(A.count(40) == 0);

	assert(ulms.size() == 7);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
} 