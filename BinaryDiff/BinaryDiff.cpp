#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

#include "BinaryDiffer.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage: BinaryDiffer binaryFileA binaryFileB" << endl;
		cout << "\tOutputs all the UInt32 differences in the binary file" << endl;
		return -1;
	}

	string fileAPath = string(argv[1]);
	string fileBPath = string(argv[2]);

	try
	{
		// detect the uint32 diffs between the two files
		BinaryDiffer differ(fileAPath, fileBPath);
		auto diffs = differ.getUint32Diffs();

		// if there aren't any differences then output a message so that the user isn't confused when no diff ouput appears
		if (diffs.size() == 0)
			cout << "The files are identical" << endl;

		// print them all out
		for (auto diff : diffs)
		{
			cout << "0x" << hex << diff.address() << "\t";
			cout << "0x" << hex << (int)diff.firstValue() << " -> " << "0x" << hex << (int)diff.secondValue();
			cout << " ( " << "0x" << hex << diff.absoluteDifference() << " )" << endl;
		}
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}