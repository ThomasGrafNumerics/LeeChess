#include "pieces_attack_tables.hpp"
#include "board.hpp"
#include <iostream>

Bitboard PAWN_ATTACK_TABLE[2][64] = {};
Bitboard KNIGHT_ATTACK_TABLE[64] = {};

// generate pawn attack mask
Bitboard mask_pawn_attack(const int side, const int square)
{
	Bitboard attack(0), temp(0);
	temp.set_bit(square);

	if (side == white)
	{
		attack |= ((temp >> 7) & NOT_A_FILE_MASK);
		attack |= ((temp >> 9) & NOT_H_FILE_MASK);
	}
	else
	{
		attack |= ((temp << 7) & NOT_H_FILE_MASK);
		attack |= ((temp << 9) & NOT_A_FILE_MASK);
	}

	return attack;
}

Bitboard mask_knight_attack(const int square)
{
	Bitboard attack(0), temp(0);
	temp.set_bit(square);

	attack |= ((temp >> 17) & NOT_H_FILE_MASK);
	attack |= ((temp >> 15) & NOT_A_FILE_MASK);
	attack |= ((temp >> 10) & NOT_GH_FILE_MASK);
	attack |= ((temp >>  6) & NOT_AB_FILE_MASK);

	attack |= ((temp << 17) & NOT_A_FILE_MASK);
	attack |= ((temp << 15) & NOT_H_FILE_MASK);
	attack |= ((temp << 10) & NOT_AB_FILE_MASK);
	attack |= ((temp <<  6) & NOT_GH_FILE_MASK);

	return attack;
}

Bitboard mask_king_attack(const int square)
{
	Bitboard attack(0), temp(0);
	temp.set_bit(square);

	attack |= ((temp >> 9) & NOT_H_FILE_MASK);
	attack |=  (temp >> 8);
	attack |= ((temp >> 7) & NOT_A_FILE_MASK);
	attack |= ((temp >> 1) & NOT_H_FILE_MASK);

	attack |= ((temp << 9) & NOT_A_FILE_MASK);
	attack |=  (temp << 8);
	attack |= ((temp << 7) & NOT_H_FILE_MASK);
	attack |= ((temp << 1) & NOT_A_FILE_MASK);

	return attack;
}

Bitboard mask_rook_attack(const int square)
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

	for (int r = rank + 1, f = file; r <= 6; ++r) { attack |= (1ull << (r * 8 + f)); }
	for (int r = rank - 1, f = file; r >= 1; --r) { attack |= (1ull << (r * 8 + f)); }
	for (int r = rank, f = file + 1; f <= 6; ++f) { attack |= (1ull << (r * 8 + f)); }
	for (int r = rank, f = file - 1; f >= 1; --f) { attack |= (1ull << (r * 8 + f)); }

	return attack;
}

Bitboard mask_bishop_attack(const int square)
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

	for (int r = rank + 1, f = file + 1; r <= 6 && f <= 6; ++r, ++f) { attack |= (1ull << (r * 8 + f)); }
	for (int r = rank + 1, f = file - 1; r <= 6 && f >= 1; ++r, --f) { attack |= (1ull << (r * 8 + f)); }
	for (int r = rank - 1, f = file + 1; r >= 1 && f <= 6; --r, ++f) { attack |= (1ull << (r * 8 + f)); }
	for (int r = rank - 1, f = file - 1; r >= 1 && f >= 1; --r, --f) { attack |= (1ull << (r * 8 + f)); }

	return attack;
}

Bitboard mask_occupancy(const Bitboard& attack_mask, const int index_filter_mask)
{
	Bitboard occupancy(0);
	Bitboard temp = attack_mask;
	int relevant_bits = temp.count_set_bits();
	for (int index = 0; index < relevant_bits; ++index)
	{
		int square = temp.get_ls1b_index();
		temp.pop_bit();

		if ((1 << index) & index_filter_mask)
			occupancy.set_bit(square);

	}

	return occupancy;
}

Bitboard mask_rook_attack_on_the_fly(const Bitboard& occupancy, const int square)
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

	for (int r = rank + 1; r <= 7; ++r)
	{
		attack.set_bit(r * 8 + file);
		if ( (1ull << (r * 8 + file)) & occupancy ) break;
	}

	for (int r = rank - 1; r >= 0; --r)
	{
		attack.set_bit(r * 8 + file);
		if ( (1ull << (r * 8 + file)) & occupancy ) break;
	}

	for (int f = file + 1; f <= 7; ++f)
	{
		attack.set_bit(rank * 8 + f);
		if ( (1ull << (rank * 8 + f)) & occupancy ) break;
	}

	for (int f = file - 1; f >= 0; --f)
	{
		attack.set_bit(rank * 8 + f);
		if ( (1ull << (rank * 8 + f)) & occupancy ) break;
	}

	return attack;
}
