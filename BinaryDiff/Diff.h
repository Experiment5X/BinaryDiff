#pragma once

#include <cstdint>

template <typename T>
class Diff
{
public:
	Diff(uint64_t address, T firstValue, T secondValue) :
		m_address(address), m_firstValue(firstValue), m_secondValue(secondValue)
	{ 
	}

	uint64_t address() { return m_address;  }
	T firstValue() { return m_firstValue; }
	T secondValue() { return m_secondValue;  }

private:
	uint64_t m_address;
	T m_firstValue;
	T m_secondValue;
};

