#include "provided.h"
#include "HashTable.h"; 
#include <string>
#include <vector>
using namespace std;

unsigned int computeHash(unsigned short someKey)
{
	return (someKey*someKey);
}

unsigned int computeHash(string someKey)
{
	unsigned int total = 0;

	for (unsigned int i = 0; i < someKey.length(); i++)
		total = total + ((i + 1) * someKey[i]);

	return(total);
}

void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
	int C;
	int N = s.size();

	if ((N / 2) + 512 < 16384) // computing the capacity of the hash table
		C = (N / 2) + 512;
	else
		C = 16384;

	numbers.clear(); // clearing the vector of existing data

	HashTable<string, unsigned short> H(2 * C, C); // to achieve a load factor of 0.5, there has to be twice as many buckets as max capacity

	string charHolder;
	for (unsigned int j = 0; j <= 255; j++) // adding each character and its numerical equivalent to the hash table
	{
		charHolder = static_cast<char>(j);
		H.set(charHolder, j, true);
	}

	string runSoFar = "";
	vector<unsigned short> V;
	char c;
	unsigned short nextFreeID = 256;

	for (int i = 0; i < N; i++)
	{
		c = s[i];
		string expandedRun = runSoFar + c;
		unsigned short someValue;
		if (H.get(expandedRun, someValue))
		{
			runSoFar = expandedRun; // if a string already exists in the hashtable, the program continues to increase the size of the string until an unfamiliar string is obtained
			continue;
		}
		else
		{
			unsigned short x;
			H.get(runSoFar, x);
			V.push_back(x);
			H.touch(runSoFar);
			runSoFar = "";
			unsigned short cv;
			string someChar;
			someChar = c;
			H.get(someChar, cv);
			V.push_back(cv);

			if (!H.isFull())
			{
				H.set(expandedRun, nextFreeID);
				nextFreeID++;
			}
			else
			{
				unsigned short discardedValue;
				string discardedKey;
				H.discard(discardedKey, discardedValue);
				H.set(expandedRun, discardedValue);
			}
		}
	}
	if (runSoFar.size() != 0)
	{
		unsigned short y;
		H.get(runSoFar, y);
		V.push_back(y);
	}
	V.push_back(C);
	numbers = V;
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
	int N = numbers.size();
	int C = numbers.back();
	HashTable<unsigned short, string> H(2 * C, C); // for a load factor of 0.5, there has to be twice as many buckets as max capacity

	string charHolder;
	for (unsigned short j = 0; j <= 255; j++)
	{
		charHolder = static_cast<char>(j);
		H.set(j, charHolder, true);
	}

	string runSoFar = "";
	string output = "";
	string expandedRun;
	char c;
	unsigned short nextFreeID = 256;

	for (int i = 0; i < N - 1; i++) // as the last value in the vector is the capacity of the hastable, its value will be ignored when decompressing
	{
		unsigned short us = numbers[i];
		if (us <= 255)
		{
			string someCharacter;
			H.get(us, someCharacter);
			output += someCharacter;

			if (runSoFar.size() == 0)
			{
				runSoFar = someCharacter;
				continue;
			}
			else
			{
				expandedRun = runSoFar + someCharacter;
			}

			if (!H.isFull())
			{
				H.set(nextFreeID, expandedRun);
				nextFreeID++;
			}
			else // the least data entry is deleted if the hash table reaches capacity
			{
				string discardedValue;
				unsigned short discardedKey;
				H.discard(discardedKey, discardedValue);
				H.set(discardedKey, expandedRun);
			}
			runSoFar = "";
		}
		else // the following code is executed if the number passed in does not represent a single character
		{
			string S;
			if (!H.get(us, S))
				return false;
			H.touch(us);
			output += S;
			runSoFar = S;
			continue;
		}
	}
	s = output;
	return true;
}
