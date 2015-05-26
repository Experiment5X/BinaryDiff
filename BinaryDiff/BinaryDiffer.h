#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

class BinaryDiffer
{
public:
	BinaryDiffer(std::string fileAPath, std::string fileBPath);

	std::vector<std::pair<uint8_t, uint8_t>> getByteDiffs();
	std::vector<std::pair<uint16_t, uint16_t>> getUint16Diffs();
	std::vector<std::pair<uint32_t, uint32_t>> getUint32Diffs();
	std::vector<std::pair<uint64_t, uint64_t>> getUint64Diffs();

private:
	std::string m_fileAPath;
	std::string m_fileBPath;

	std::vector<std::pair<uint8_t, uint8_t>> m_byteDiffs;
	std::vector<std::pair<uint16_t, uint16_t>> m_uint16Diffs;
	std::vector<std::pair<uint32_t, uint32_t>> m_uint32Diffs;
	std::vector<std::pair<uint64_t, uint64_t>> m_uint64Diffs;

	// generic function for comparing arbitrary sized integers (8, 16, 32, and 64 bit)
	template <typename T>
	std::vector<std::pair<T, T>> getDiffs()
	{
		size_t diffUnitLength = sizeof(T);
		std::vector<std::pair<T, T>> diffs;

		// open both the files for reading
		std::fstream fileA(m_fileAPath, std::ios_base::in | std::ios_base::binary);
		std::fstream fileB(m_fileBPath, std::ios_base::in | std::ios_base::binary);

		while (!fileA.eof() && !fileB.eof())
		{
			// read the next ints in from the files
			std::pair<T, T> curDifference;
			fileA.read((char*)&curDifference.first, diffUnitLength);
			fileB.read((char*)&curDifference.second, diffUnitLength);

			// check for a difference
			if (curDifference.first != curDifference.second)
				diffs.push_back(curDifference);
		}

		return diffs;
	}
};

