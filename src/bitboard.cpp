#include "bitboard.hpp"
#include <iostream>
#include <cassert>

// default constructor
Bitboard::Bitboard() : bitboard(0) {}

// constructor
Bitboard::Bitboard(const U64 init_bitboard) : bitboard(init_bitboard) {}

// copy constructor
Bitboard::Bitboard(const Bitboard& rhs) : bitboard(rhs.bitboard) {}

// user-definded conversion functions
Bitboard::operator U64() const { return bitboard; }
Bitboard::operator U64&() { return bitboard; }

// Bitboard operators

// set bit value to 1
void Bitboard::set_bit(const int square)
{
	bitboard |= (1ull << square);
}

// set bit value to 0
void Bitboard::clear_bit(const int square)
{
	bitboard &= (~(1ull << square));
}

// get bit value
bool Bitboard::get_bit(const int square) const
{
	return (bitboard >> square) & 1;
}

// invert (flip) bit value
void Bitboard::invert_bit(const int square)
{
	bitboard ^= (1ull << square);
}

// clear the least significant set bit
void Bitboard::pop_bit(void)
{
  bitboard &= (bitboard - 1);
}

// get the number of set bits
int Bitboard::count_set_bits(void) const
{
	// using Brian Kernighan’s Algorithm:
	// https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
	U64 temp = bitboard;
	int count = 0;
	while (temp)
	{
		temp &= (temp - 1);
		++count;
	}
	return count;
}

// intended for nonzero bitboards only:
// get the index of the least significant set bit
int Bitboard::get_ls1b_index(void) const
{
  assert(bitboard != 0);
	Bitboard temp( (bitboard & -bitboard) - 1 );
	return temp.count_set_bits();
}

// set bitboard to 0
void Bitboard::clear_bitboard(void)
{
	bitboard = 0;
}

// print ASCII representation of a bitboard to standard output.
void Bitboard::print_bitboard() const
{
	for (int rank = 0; rank < 8; ++rank)
	{
		std::cout << (8 - rank) << "   ";
		for (int file = 0; file < 8; ++file)
		{
			int square = rank * 8 + file;
			std::cout << get_bit(square) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "    a b c d e f g h" << std::endl;
}
