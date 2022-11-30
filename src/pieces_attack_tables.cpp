#include "pieces_attack_tables.hpp"
#include "board.hpp"
#include <iostream>

Bitboard PAWN_ATTACK_TABLE[2][64] = {};
Bitboard KNIGHT_ATTACK_TABLE[64] = {};
Bitboard KING_ATTACK_TABLE[64] = {};

Bitboard BISHOP_ATTACK_MASK_TABLE[64] = {};
Bitboard ROOK_ATTACK_MASK_TABLE[64] = {};
Bitboard BISHOP_ATTACK_TABLE[64][512] = {};
Bitboard ROOK_ATTACK_TABLE[64][4096] = {};

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

Bitboard mask_bishop_attack_on_the_fly(const Bitboard& occupancy, const int square)
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

	for (int r = rank + 1, f = file + 1; r <= 7 && f <= 7; ++r, ++f)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	for (int r = rank + 1, f = file - 1; r <= 7 && f >= 0; ++r, --f)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	for (int r = rank - 1, f = file + 1; r >= 0 && f <= 7; --r, ++f)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; --r, --f)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	return attack;
}

Bitboard mask_rook_attack_on_the_fly(const Bitboard& occupancy, const int square)
{
	Bitboard attack(0);

	int rank = square / 8;
	int file = square % 8;

	for (int r = rank + 1, f = file; r <= 7; ++r)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	for (int r = rank - 1, f = file; r >= 0; --r)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	for (int r = rank, f = file + 1; f <= 7; ++f)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	for (int r = rank, f = file - 1; f >= 0; --f)
	{
		Bitboard bitboard = 1ull << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & occupancy) break;
	}

	return attack;
}

void init_leaper_attack_tables(void)
{
	for (int square = 0; square < 64; ++square)
	{
		PAWN_ATTACK_TABLE[white][square] = mask_pawn_attack(white, square);
		PAWN_ATTACK_TABLE[black][square] = mask_pawn_attack(black, square);

		KNIGHT_ATTACK_TABLE[square] = mask_knight_attack(square);
		KING_ATTACK_TABLE[square] = mask_king_attack(square);
	}
}

// void init_slider_attack_tables(void)
// {
// 	for (int square = 0; square < 64; ++square)
// 	{
// 		//init bishop && rook attack mask
// 		BISHOP_ATTACK_MASK_TABLE[square] = MaskBishopAttack(square);
// 		ROOK_ATTACK_MASK_TABLE[square] = MaskRookAttack(square);

// 		//really it is just hashing the occupancy into the magic index
// 		int occupancies_variation = 1 << BISHOP_RELEVANT_BITS_TABLE[square];
// 		for (int index = 0; index < occupancies_variation; ++index)
// 		{
// 			Bitboard attack_mask_and_occupancy = MaskOccupancy(BISHOP_ATTACK_MASK_TABLE[square], index);
// 			int magic_index = static_cast<int>((attack_mask_and_occupancy * BISHOP_MAGIC_NUM_TABLE[square]) >> (64 - BISHOP_RELEVANT_BITS_TABLE[square]));
// 			BISHOP_ATTACK_TABLE[square][magic_index] = MaskBishopAttackOnFly(square, attack_mask_and_occupancy);
// 		}

// 		occupancies_variation = 1 << ROOK_RELEVANT_BITS_TABLE[square];
// 		for (int index = 0; index < occupancies_variation; ++index)
// 		{
// 			Bitboard attack_mask_and_occupancy = MaskOccupancy(ROOK_ATTACK_MASK_TABLE[square], index);
// 			int magic_index = static_cast<int>((attack_mask_and_occupancy * ROOK_MAGIC_NUM_TABLE[square]) >> (64 - ROOK_RELEVANT_BITS_TABLE[square]));
// 			ROOK_ATTACK_TABLE[square][magic_index] = MaskRookAttackOnFly(square, attack_mask_and_occupancy);
// 		}
// 	}
// }