#include <iostream>
#include <cassert>
#include "../include/bitboard.h"

Bitboard::Bitboard() : bitboard{0} {}
Bitboard::Bitboard(const U64 init_bitboard) : bitboard{init_bitboard} {}
Bitboard::Bitboard(const Bitboard& rhs) : bitboard{rhs.bitboard} {}

Bitboard::operator U64&() { return bitboard; }
Bitboard::operator U64() const { return bitboard; }

bool Bitboard::get_bit(const unsigned int square) const
{
	return (bitboard >> square) & 1ull;
}

void Bitboard::print_bitboard(void) const
{
	for (unsigned int rank = 0; rank < 8; ++rank)
	{
		std::cout << (8 - rank) << " ";
		for (unsigned int file = 0; file < 8; ++file)
		{
			int square = rank * 8 + file;
			std::cout << get_bit(square) << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << "  a  b  c  d  e  f  g  h" << std::endl << std::endl;
}

U64 Bitboard::get_bitboard_value(void) const
{
	return bitboard;
}

void Bitboard::set_bit(const unsigned int square)
{
	bitboard |= (1ull << square);
}

void Bitboard::clear_bit(const unsigned int square)
{
	bitboard &= (~(1ull << square));
}

void Bitboard::invert_bit(const unsigned int square)
{
	bitboard ^= (1ull << square);
}

void Bitboard::clear_LS_set_bit(void)
{
  bitboard &= (bitboard - 1ull);
}

void Bitboard::clear_bitboard(void)
{
	bitboard = 0ull;
}

unsigned int Bitboard::get_number_of_set_bits(void) const
{
	// using Brian Kernighan’s Algorithm: https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
	U64 temp = bitboard;
	unsigned int count = 0;
	while (temp)
	{
		temp &= (temp - 1ull);
		++count;
	}
	return count;
}

unsigned int Bitboard::get_index_of_LS_set_bit(void) const
{
    assert(bitboard != 0);
	Bitboard temp((bitboard & -bitboard) - 1ull);
	return temp.get_number_of_set_bits();    
}