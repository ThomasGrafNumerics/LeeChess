#include "../include/bitboard.h"
#include "../include/attack_tables.h"
#include "../include/magic.h"

Bitboard PAWN_ATTACKS_TABLE[2][64] = {};
Bitboard KNIGHT_ATTACKS_TABLE[64] = {};
Bitboard KING_ATTACKS_TABLE[64] = {};
Bitboard BISHOP_ATTACKS_MASK_TABLE[64] = {};
Bitboard ROOK_ATTACKS_MASK_TABLE[64] = {};
Bitboard BISHOP_ATTACKS_TABLE[64][512] = {};
Bitboard ROOK_ATTACKS_TABLE[64][4096] = {};

Bitboard mask_pawn_attacks(const bool side, const unsigned int square)
{
	Bitboard attack(0), temp(0);
	temp.set_bit(square);

	if (side == WHITE)
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

Bitboard mask_knight_attacks(const unsigned int square)
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

Bitboard mask_king_attacks(const unsigned int square)
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

Bitboard mask_rook_attacks(const unsigned int square)
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

	for (int r = rank + 1, f = file; r <= 6; ++r) { attack.set_bit(r * 8 + f); }
	for (int r = rank - 1, f = file; r >= 1; --r) { attack.set_bit(r * 8 + f); }
	for (int r = rank, f = file + 1; f <= 6; ++f) { attack.set_bit(r * 8 + f); }
	for (int r = rank, f = file - 1; f >= 1; --f) { attack.set_bit(r * 8 + f); }

	return attack;
}

Bitboard mask_bishop_attacks(const unsigned int square)
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

	for (int r = rank + 1, f = file + 1; r <= 6 && f <= 6; ++r, ++f) { attack.set_bit(r * 8 + f); }
	for (int r = rank + 1, f = file - 1; r <= 6 && f >= 1; ++r, --f) { attack.set_bit(r * 8 + f); }
	for (int r = rank - 1, f = file + 1; r >= 1 && f <= 6; --r, ++f) { attack.set_bit(r * 8 + f); }
	for (int r = rank - 1, f = file - 1; r >= 1 && f >= 1; --r, --f) { attack.set_bit(r * 8 + f); }

	return attack;
}

Bitboard mask_rook_attacks_on_the_fly(const Bitboard& occupancy, const unsigned int square)
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

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

Bitboard mask_bishop_attacks_on_the_fly(const Bitboard& occupancy, const unsigned int square)
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

Bitboard mask_occupancy(const Bitboard& attack_mask, const unsigned int specific_occupancy_extractor)
{
	Bitboard occupancy(0);
	Bitboard temp = attack_mask;

	const unsigned int relevant_bits = temp.get_number_of_set_bits();
	for (unsigned int index = 0; index < relevant_bits; ++index)
	{
		int square = temp.get_index_of_LS_set_bit();
		temp.clear_LS_set_bit();

		if ((1 << index) & specific_occupancy_extractor) occupancy.set_bit(square);
	}

	return occupancy;
}

void init_leaper_attack_tables(void)
{
	for (unsigned int square = 0; square < 64; ++square)
	{
		PAWN_ATTACKS_TABLE[WHITE][square] = mask_pawn_attacks(WHITE, square);
		PAWN_ATTACKS_TABLE[BLACK][square] = mask_pawn_attacks(BLACK, square);

		KNIGHT_ATTACKS_TABLE[square] = mask_knight_attacks(square);
		KING_ATTACKS_TABLE[square] = mask_king_attacks(square);
	}
}

void init_slider_attack_tables(void)
{
	for (unsigned int square = 0; square < 64; ++square)
	{
		BISHOP_ATTACKS_MASK_TABLE[square] = mask_bishop_attacks(square);
		ROOK_ATTACKS_MASK_TABLE[square] = mask_rook_attacks(square);

		unsigned int occupancies_variation = 1 << BISHOP_NUMBER_OF_RELEVANT_BITS_TABLE[square];
		for (unsigned int index = 0; index < occupancies_variation; ++index)
		{
			Bitboard attack_mask_and_occupancy = mask_occupancy(BISHOP_ATTACKS_MASK_TABLE[square], index);
			unsigned int magic_index = static_cast<unsigned int>((attack_mask_and_occupancy * BISHOP_MAGIC_NUMBERS[square]) >> (64 - BISHOP_NUMBER_OF_RELEVANT_BITS_TABLE[square]));
			BISHOP_ATTACKS_TABLE[square][magic_index] = mask_bishop_attacks_on_the_fly(attack_mask_and_occupancy, square);
		}

		occupancies_variation = 1 << ROOK_NUMBER_OF_RELEVANT_BITS_TABLE[square];
		for (unsigned int index = 0; index < occupancies_variation; ++index)
		{
			Bitboard attack_mask_and_occupancy = mask_occupancy(ROOK_ATTACKS_MASK_TABLE[square], index);
			unsigned int magic_index = static_cast<unsigned int>((attack_mask_and_occupancy * ROOK_MAGIC_NUMBERS[square]) >> (64 - ROOK_NUMBER_OF_RELEVANT_BITS_TABLE[square]));
			ROOK_ATTACKS_TABLE[square][magic_index] = mask_rook_attacks_on_the_fly(attack_mask_and_occupancy, square);
		}
	}
}

Bitboard get_pawn_attack_exact(const bool attack_side, unsigned int square)
{
	return PAWN_ATTACKS_TABLE[attack_side][square];
}
Bitboard get_knight_attack_exact(unsigned int square)
{
	return KNIGHT_ATTACKS_TABLE[square];
}
Bitboard get_king_attack_exact(unsigned int square)
{
	return KING_ATTACKS_TABLE[square];
}

Bitboard get_bishop_attack_exact(unsigned int square, const Bitboard& occupancy)
{
	//hash occupancy into magic index;
	unsigned int magic_index = static_cast<unsigned int>(((occupancy & BISHOP_ATTACKS_MASK_TABLE[square]) * BISHOP_MAGIC_NUMBERS[square]) >> (64 - BISHOP_NUMBER_OF_RELEVANT_BITS_TABLE[square]));

	return BISHOP_ATTACKS_TABLE[square][magic_index];
}

Bitboard get_rook_attack_exact(unsigned int square, const Bitboard& occupancy)
{
	//hash occupancy into magic index;
	unsigned int magic_index = static_cast<unsigned int>(((occupancy & ROOK_ATTACKS_MASK_TABLE[square]) * ROOK_MAGIC_NUMBERS[square]) >> (64 - ROOK_NUMBER_OF_RELEVANT_BITS_TABLE[square]));

	return ROOK_ATTACKS_TABLE[square][magic_index];
}