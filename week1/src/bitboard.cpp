#include "bitboard.h"

// default constructor
Bitboard::Bitboard(void) : bitboard{0_int64} {}

// constructor
Bitboard::Bitboard(const uint64_t init_bitboard) : bitboard{init_bitboard} {}


bool Bitboard::get_bit(const unsigned int square) const
{
	return (bitboard) & (1_int64 << square);
} 
