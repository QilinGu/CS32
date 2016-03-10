#include "provided.h"
#include <string>
#include <vector>
using namespace std;

const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
	string aggregateString = "";

	for (int i = 0; i < numbers.size(); i++)
	{
		aggregateString += convertNumberToBitString(numbers[i]); // converting every number in the vector to binary form and adding the result to a string
	}

	for (int j = 0; j < aggregateString.size(); j++)
	{
		switch (aggregateString[j]) // changes 1s to tabs ('\t') and 0s to spaces (' ')
		{
		case '1':
			aggregateString[j] = '\t';
			break;
		case '0':
			aggregateString[j] = ' ';
			break;
		}
	}

	return aggregateString;
}

bool BinaryConverter::decode(const string& bitString,
	vector<unsigned short>& numbers)
{
	if (bitString.size() % 16 != 0) // checking if the bitString is a multipe of 16
		return false;

	numbers.clear(); // clearing the vector of existing data

	string subString = "";

	for (int i = 0; i < bitString.size(); i++) 
	{
		switch (bitString[i])
		{
		case '\t':
			subString += '1';
			break;
		case ' ':
			subString += '0';
			break;
		default:
			return false;
			break;
		}

		if ((i + 1) % 16 == 0) // after every 16 binary characters is added to the substring, the subString is converted to an unsigned short and the result is pushed into a vector
		{
			unsigned short number;

			if (convertBitStringToNumber(subString, number))
				numbers.push_back(number);
			else
				return false;

			subString = ""; // resetting the substring after 16 binary characters have been processed
		}
	}
	return true;
}

string convertNumberToBitString(unsigned short number)
{
	string result(BITS_PER_UNSIGNED_SHORT, '0');
	for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
	{
		k--;
		if (number % 2 == 1)
			result[k] = '1';
	}
	return result;
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
	if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
		return false;
	number = 0;
	for (size_t k = 0; k < bitString.size(); k++)
	{
		number *= 2;
		if (bitString[k] == '1')
			number++;
		else if (bitString[k] != '0')
			return false;
	}
	return true;
}
