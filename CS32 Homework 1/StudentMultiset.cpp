#include "StudentMultiset.h"
#include <iostream>
using namespace std;

StudentMultiset::StudentMultiset()
{}
// Create an empty student multiset.

bool StudentMultiset::add(unsigned long id)
{
	if (m_multiset.insert(id))
		return true;
	return false;
}
// Add a student id to the StudentMultiset.  Return true if and only
// if the id was actually added.

int StudentMultiset::size() const
{
	return m_multiset.size();
}
// Return the number of items in the StudentMultiset.  If an id was
// added n times, it contributes n to the size.

void StudentMultiset::print() const
{
	unsigned long value;
	int printCounter;
	for (int i = 0; i < m_multiset.uniqueSize(); i++)
	{
		printCounter = m_multiset.get(i, value);
		for (int j = 0; j < printCounter; j++)
			cout << value << endl;
	}
}
// Print to cout every student id in the StudentMultiset one per line;
// print as many lines for each id as it occurs in the StudentMultiset. 