#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

#include "BinaryDiffer.h"

using namespace std;

int main(int argc, char* argv[])
{
	string fileAPath = "C:\\Users\\Adam\\Desktop\\Tiger Woods 2013\\13-TourEvent0";
	string fileBPath = "C:\\Users\\Adam\\Desktop\\Tiger Woods 2013\\13-TourEvent0 new";

	BinaryDiffer differ(fileAPath, fileBPath);
	for (auto diff : differ.getUint32Diffs())
	{
		if (diff.absoluteDifference() < 0x100)
		{
			cout << "0x" << hex << diff.address() << "\t";
			cout << "0x" << hex << (int)diff.firstValue() << " -> " << "0x" << hex << (int)diff.secondValue() << endl;
		}
	}
	cin.get();
	return 0;
}