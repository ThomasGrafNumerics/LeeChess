#pragma once
#include "types.h"

class Bitboard
{
	public:
		// constructors
		Bitboard(void); // default constructor
		Bitboard(const uint64_t); // constructor

		bool get_bit(const unsigned int) const;

	private:
		uint64_t bitboard;
};