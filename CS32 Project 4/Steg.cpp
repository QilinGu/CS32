#include "provided.h"
#include <string>
using namespace std;

bool Steg::hide(const string& hostIn, const string& msg, string& hostOut)
{
	if (hostIn.size() == 0)
		return false;

	int lineCount = 0;
	for (int i = 0; i < hostIn.size(); i++) // computing the number of lines in the input string
	{
		if (hostIn[i] == '\n')
			lineCount++;
	}
	
	if (hostIn[hostIn.size() - 1] != '\n') // if the string does not end with a new line character then there is an additional line
		lineCount++;

	string* Lines = new string[lineCount];
	
	Lines[0] = "";
	int lineNumber = 0;
		
	bool foundEndOfLine = true;
	for (int j = hostIn.size() - 1; j >= 0; j--) // adding each line to an index in an array of strings. This is done in reverse order so that tabs and spaces at the end of each line can be ignored
	{
		if (hostIn[j] == '\n')
		{
			foundEndOfLine = true;

			for (int u = 0; u < Lines[lineNumber].size()/2; u++) // reverses the string in the particular index, as characters have been added in reverse order
			{
				char temp = Lines[lineNumber][u];
				Lines[lineNumber][u] = Lines[lineNumber][Lines[lineNumber].size() - 1 - u];
				Lines[lineNumber][Lines[lineNumber].size() - 1 - u] = temp;
			}

			lineNumber++;
			Lines[lineNumber] = "";
			continue;
		}

		if (hostIn[j] == '\r') 
			continue;

		if (foundEndOfLine && (hostIn[j] == '\t' || hostIn[j] == ' ')) // ignoring tabs and spaces at the end of a line
			continue;

		Lines[lineNumber] += hostIn[j]; // 
		foundEndOfLine = false;
	}

	for (int u = 0; u < Lines[lineCount - 1].size() / 2; u++)
	{
		char temp = Lines[lineCount - 1][u];
		Lines[lineCount - 1][u] = Lines[lineCount - 1][Lines[lineCount - 1].size() - 1 - u];
		Lines[lineCount - 1][Lines[lineCount - 1].size() - 1 - u] = temp;
	}
	
	string temp;
	for (int q = 0; q < lineCount/2; q++) // reverses the array of strings, as even the array holds the lines in reverse order
	{
		temp = Lines[q];
		Lines[q] = Lines[lineCount - 1 - q];
		Lines[lineCount - 1 - q] = temp;
	}
	
	vector<unsigned short> compressedMsg;
	Compressor::compress(msg, compressedMsg);

	string hiddenMsg = BinaryConverter::encode(compressedMsg);

	int L = hiddenMsg.size();
	int N = lineCount;

	string* hiddenLines = new string[lineCount];

	int firstSubstrings = L % N;

	int length1 = (L / N) + 1;
	int length2 = L / N;
	
	for (int k = 0; k < firstSubstrings; k++) // adds a portion ( which has a length of (L/N)+1 ) of the hidden message to an array of strings
		hiddenLines[k] = hiddenMsg.substr(length1 * k, length1);

	int start2 = length1*firstSubstrings;

	for (int m = firstSubstrings; m < N; m++) // adds portions of the hidden message (of length L/N) to the rest of the indices in the array
		hiddenLines[m] = hiddenMsg.substr(start2 + (length2 * (m - firstSubstrings)), length2);

	hostOut = ""; 
	for (int p = 0; p < lineCount; p++)
	{
		hostOut += Lines[p] + hiddenLines[p] + '\n';
	}

	delete[] Lines;
	delete[] hiddenLines;

	return true;
}

bool Steg::reveal(const string& hostIn, string& msg)
{
	string reverseBinaryMsg = "";
	int length = hostIn.size();
	bool foundEndOfLine = true;

	for (int i = length - 1; i >= 0; i--) // concatenates all tabs and spaces at the end of each line in the hostIn string. This process is again done in reverse to ignore tabs and spaces in between the content
	{
		if (hostIn[i] == '\n')
		{
			foundEndOfLine = true;
			continue;
		}

		if (hostIn[i] == '\r')
			continue;

		if (foundEndOfLine && (hostIn[i] == '\t' || hostIn[i] == ' ')) // ignores all other tabs and spaces except the one at the end of the lines
		{
			reverseBinaryMsg += hostIn[i];
			continue;
		}

		foundEndOfLine = false;
	}
	
	string binaryMsg = "";
	int lengthOfBinaryString = reverseBinaryMsg.size();

	for (int j = 0; j < lengthOfBinaryString; j++) // reverses the order of the hidden message 
	{
		binaryMsg += reverseBinaryMsg[lengthOfBinaryString - 1 - j];
	}

	vector<unsigned short> compressedMsg;

	if (!BinaryConverter::decode(binaryMsg, compressedMsg)) 
		return false;

	if (!Compressor::decompress(compressedMsg, msg))
		return false;

	return true;
}

/*for (int j = 0; j < hostIn.size(); j++)
{
if (hostIn[j] == '\n')
{
lineNumber++;
Lines[lineNumber] = "";
continue;
}

if (hostIn[j] == '\t' || hostIn[j] == ' ' || hostIn[j] == '\r') // fix needed
continue;

Lines[lineNumber] += hostIn[j];

vector<unsigned short> R;
BinaryConverter::decode(hiddenMsg, R);
string k = "Greetings";
Compressor::decompress(R, k);
cerr << "CHECK FOR FINAL VERDICT: " << k << endl;

string totalHidden = "";
for (int t = 0; t < lineCount; t++)
{
totalHidden += hiddenLines[t];
}
vector<unsigned short> V;
BinaryConverter::decode(totalHidden, V);
string s = "Hey";
Compressor::decompress(V, s);
cerr << "THE FINAL VERDICT: " << s << endl;
}*/