#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

#include "Diff.h"

enum class ByteOrder
{
	BigEndian,
	LittleEndian
};

class BinaryDiffer
{
public:
	BinaryDiffer(std::string fileAPath, std::string fileBPath, ByteOrder byteOrder = ByteOrder::BigEndian);

	std::vector<Diff<uint8_t>> getByteDiffs();
	std::vector<Diff<uint16_t>> getUint16Diffs();
	std::vector<Diff<uint32_t>> getUint32Diffs();
	std::vector<Diff<uint64_t>> getUint64Diffs();

	ByteOrder byteOrder();
	void setByteOrder(ByteOrder byteOrder);

private:
	std::string m_fileAPath;
	std::string m_fileBPath;
	ByteOrder m_byteOrder;

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

		// get the file lengths
		uint64_t fileALength = FileLength(fileA);
		uint64_t fileBLength = FileLength(fileB);

		// loop until there isn't a full integer left to read at the end of the file
		while (fileALength - fileA.tellg() > diffUnitLength)
		{
			// read the next ints in from the files
			T first, second;
			uint64_t address = fileA.tellg();

			// read the next integer from the file
			fileA.read((char*)&first, diffUnitLength);
			fileB.read((char*)&second, diffUnitLength);

			// change the byte order if necessary
			if (m_byteOrder == ByteOrder::BigEndian)
			{
				SwapIntegerByteOrder((uint8_t*)&first, diffUnitLength);
				SwapIntegerByteOrder((uint8_t*)&second, diffUnitLength);
			}

			// create a diff object to hold the info
			Diff<T> diff(address, first, second);

			// check for a difference
			if (diff.firstValue() != diff.secondValue())
				diffs.push_back(diff);
		}

		fileA.close();
		fileB.close();

		return diffs;
	}

	static uint64_t FileLength(std::fstream &file);
	static void SwapIntegerByteOrder(uint8_t *integer, size_t length);
};

