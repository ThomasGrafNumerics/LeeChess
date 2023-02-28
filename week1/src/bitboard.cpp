#include "bitboard.h"
#include <iostream>

// default constructor
Bitboard::Bitboard(void) : bitboard{0_int64} {}

// constructor
Bitboard::Bitboard(const uint64_t init_bitboard) : bitboard{init_bitboard} {}


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

void Bitboard::clear_bitboard(void)
{
	bitboard = 0_int64;
}
