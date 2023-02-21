#include "bitboard.h"

// default constructor
Bitboard::Bitboard(void) : bitboard{0ull} {}

// constructor
Bitboard::Bitboard(const uint64_t init_bitboard) : bitboard{init_bitboard} {}


bool Bitboard::get_bit(const unsigned int square) const
{
	return (bitboard >> square) & 1ull;
}