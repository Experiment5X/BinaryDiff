#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

#include "Diff.h"

class BinaryDiffer
{
public:
	BinaryDiffer(std::string fileAPath, std::string fileBPath);

	std::vector<Diff<uint8_t>> getByteDiffs();
	std::vector<Diff<uint16_t>> getUint16Diffs();
	std::vector<Diff<uint32_t>> getUint32Diffs();
	std::vector<Diff<uint64_t>> getUint64Diffs();

private:
	std::string m_fileAPath;
	std::string m_fileBPath;

	std::vector<Diff<uint8_t>> m_byteDiffs;
	std::vector<Diff<uint16_t>> m_uint16Diffs;
	std::vector<Diff<uint32_t>> m_uint32Diffs;
	std::vector<Diff<uint64_t>> m_uint64Diffs;

	// generic function for finding diffs for sized integers (8, 16, 32, and 64 bit) in the two files
	template <typename T>
	std::vector<Diff<T>> getDiffs()
	{
		size_t diffUnitLength = sizeof(T);
		std::vector<Diff<T>> diffs;

		// open both the files for reading
		std::fstream fileA(m_fileAPath, std::ios_base::in | std::ios_base::binary);
		std::fstream fileB(m_fileBPath, std::ios_base::in | std::ios_base::binary);

		// loop until the end of one of the files is reached
		while (!fileA.eof() && !fileB.eof())
		{
			// read the next ints in from the files
			T first, second;
			uint64_t address = fileA.tellg();

			// read the next integer from the file
			fileA.read((char*)&first, diffUnitLength);
			fileB.read((char*)&second, diffUnitLength);

			// create a diff object to hold the info
			Diff<T> diff(address, first, second);

			// check for a difference
			if (diff.firstValue() != diff.secondValue())
				diffs.push_back(diff);
		}

		return diffs;
	}
};

