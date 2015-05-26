#include "BinaryDiffer.h"

BinaryDiffer::BinaryDiffer(std::string fileAPath, std::string fileBPath) :
	m_fileAPath(fileAPath), m_fileBPath(fileBPath)
{
}

std::vector<Diff<uint8_t>> BinaryDiffer::getByteDiffs()
{
	if (m_byteDiffs.size() == 0)
		m_byteDiffs = getDiffs<uint8_t>();
	return m_byteDiffs;
}

std::vector<Diff<uint16_t>> BinaryDiffer::getUint16Diffs()
{
	if (m_uint16Diffs.size() == 0)
		m_uint16Diffs = getDiffs<uint16_t>();
	return m_uint16Diffs;
}

std::vector<Diff<uint32_t>> BinaryDiffer::getUint32Diffs()
{
	if (m_uint32Diffs.size() == 0)
		m_uint32Diffs = getDiffs<uint32_t>();
	return m_uint32Diffs;
}

std::vector<Diff<uint64_t>> BinaryDiffer::getUint64Diffs()
{
	if (m_uint64Diffs.size() == 0)
		m_uint64Diffs = getDiffs<uint64_t>();
	return m_uint64Diffs;
}

uint64_t BinaryDiffer::FileLength(std::fstream &file)
{
	uint64_t originalPosition = file.tellg();

	// get the file length
	file.seekg(0, std::ios_base::end);
	uint64_t fileLength = file.tellg();

	// reset the position to where it was before
	file.seekg(originalPosition, std::ios_base::beg);

	return fileLength;
}