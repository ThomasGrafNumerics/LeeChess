#include "bitboard.h"
#include <iostream>
#include <cassert>

Bitboard::Bitboard(void) : bitboard{0_int64} {}
Bitboard::Bitboard(const uint64_t init_bitboard) : bitboard{init_bitboard} {}
Bitboard::Bitboard(const Bitboard& rhs) : bitboard{rhs.bitboard} {}

Bitboard::operator uint64_t&() { return bitboard; }
Bitboard::operator uint64_t() const { return bitboard; }

bool Bitboard::get_bit(const unsigned int square) const
{
	return (bitboard) & (1_int64 << square);
}

void Bitboard::print_bitboard(void) const
{
	for (unsigned int rank = 0; rank < 8; ++rank)
	{
		std::cout << (8 - rank) << "| ";
		for (unsigned int file = 0; file < 8; ++file)
		{
			unsigned int square = rank * 8 + file;
			std::cout << get_bit(square) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "   A B C D E F G H" << "\n\n";
}

uint64_t Bitboard::get_bitboard_value(void) const
{
	return bitboard;
}

void Bitboard::set_bit(const unsigned square)
{
	(bitboard) |= (1_int64 << square);
}

void Bitboard::clear_bit(const unsigned int square)
{
	bitboard &= (~(1_int64 << square));
}

void Bitboard::invert_bit(const unsigned int square)
{
	bitboard ^= (1_int64 << square);
}

void Bitboard::clear_least_significant_set_bit(void)
{
	bitboard &= (bitboard - 1_int64);
}

void Bitboard::clear_bitboard(void)
{
	bitboard = 0_int64;
}

unsigned int Bitboard::get_number_of_set_bits(void) const
{
	// using Brian Kernighan’s Algorithm: https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
	uint64_t temp = bitboard;
	unsigned int count = 0;
	while (temp)
	{
		temp &= (temp - 1_int64);
		++count;
	}
	return count;
}

unsigned int Bitboard::get_index_of_least_significant_set_bit(void) const
{
	assert(bitboard != 0);
	Bitboard temp( (bitboard & -bitboard) - 1_int64 );
	return temp.get_number_of_set_bits();    
}