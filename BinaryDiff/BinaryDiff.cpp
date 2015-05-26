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
	for (auto diff : differ.getByteDiffs())
		cout << "0x" << hex << (int)diff.first << " -> " << "0x" << hex << (int)diff.second << endl;
	cin.get();
	return 0;
}