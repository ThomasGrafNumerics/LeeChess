#include "pieces_attacks.h"

Bitboard Pieces_Attacks::pawn_attacks_used_to_precompute_attack_tables_later(const bool side, const unsigned int square) const
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

Bitboard Pieces_Attacks::knight_attacks_used_to_precompute_attack_tables_later(const unsigned int square) const
{
	Bitboard attack(0), temp(0);
	temp.set_bit(square);

	attack |= ((temp >> 17) & NOT_H_FILE_MASK );
	attack |= ((temp >> 15) & NOT_A_FILE_MASK );
	attack |= ((temp >> 10) & NOT_GH_FILE_MASK);
	attack |= ((temp >>  6) & NOT_AB_FILE_MASK);

	attack |= ((temp << 17) & NOT_A_FILE_MASK );
	attack |= ((temp << 15) & NOT_H_FILE_MASK );
	attack |= ((temp << 10) & NOT_AB_FILE_MASK);
	attack |= ((temp <<  6) & NOT_GH_FILE_MASK);

	return attack;
}

Bitboard Pieces_Attacks::king_attacks_used_to_precompute_attack_tables_later(const unsigned int square) const
{
	Bitboard attack(0), temp(0);
	temp.set_bit(square);

	attack |= ((temp >> 9) & NOT_H_FILE_MASK);
	attack |= ( temp >> 8);
	attack |= ((temp >> 7) & NOT_A_FILE_MASK);
	attack |= ((temp >> 1) & NOT_H_FILE_MASK);

	attack |= ((temp << 9) & NOT_A_FILE_MASK);
	attack |= ( temp << 8);
	attack |= ((temp << 7) & NOT_H_FILE_MASK);
	attack |= ((temp << 1) & NOT_A_FILE_MASK);
	
	return attack;
}

Bitboard Pieces_Attacks::rook_attacks_used_to_precompute_attack_tables_later(const Bitboard blockers, const unsigned int square) const
{
	Bitboard attack(0);
	const int rank = square / 8;
	const int file = square % 8;

	// ray to South
	for (int r = rank + 1, f = file; r <= 7; ++r)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}

	// ray to North
	for (int r = rank - 1, f = file; r >= 0; --r)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}

	// ray to East
	for (int r = rank, f = file + 1; f <= 7; ++f)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}
	
	// ray to West
	for (int r = rank, f = file - 1; f >= 0; --f)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}

	return attack;
}

Bitboard Pieces_Attacks::bishop_attacks_used_to_precompute_attack_tables_later(const Bitboard blockers, const unsigned int square) const
{
	Bitboard attack(0);

	const int rank = square / 8;
	const int file = square % 8;

	// 
	for (int r = rank + 1, f = file + 1; r <= 7 && f <= 7; ++r, ++f)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}

	// 
	for (int r = rank + 1, f = file - 1; r <= 7 && f >= 0; ++r, --f)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}

	// 
	for (int r = rank - 1, f = file + 1; r >= 0 && f <= 7; --r, ++f)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}

	// 
	for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; --r, --f)
	{
		Bitboard bitboard = 1_int64 << (r * 8 + f);
		attack |= bitboard;
		if (bitboard & blockers) break;
	}

	return attack;
}

Bitboard Pieces_Attacks::rook_give_reduced_attack_mask_for_given_square(const unsigned int square) const
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

Bitboard Pieces_Attacks::bishop_give_reduced_attack_mask_for_given_square(const unsigned int square) const
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

Bitboard Pieces_Attacks::give_kth_possible_blocker_configuration_within_given_reduced_attack_mask(const Bitboard reduced_attack_mask, const unsigned int k) const
{
	Bitboard kth_possible_blocker_configuration{0};
	Bitboard temp = reduced_attack_mask;
	const unsigned int number_of_set_bits_in_reduced_attack_mask = temp.get_number_of_set_bits();

	for (unsigned int nth_square_within_reduced_attack_mask = 0; nth_square_within_reduced_attack_mask < number_of_set_bits_in_reduced_attack_mask; ++nth_square_within_reduced_attack_mask)
	{
		unsigned int square = temp.get_index_of_least_significant_set_bit();

		if ((1_int64 << nth_square_within_reduced_attack_mask) & k)
		{
			kth_possible_blocker_configuration.set_bit(square);
		}

		temp.clear_least_significant_set_bit();
	}
	return kth_possible_blocker_configuration;
}










void Pieces_Attacks::precompute_leaper_pieces_attack_tables(void)
{
	for (unsigned square = 0; square < 64; ++square)
	{
		KING_ATTACKS_TABLE[square] = king_attacks_used_to_precompute_attack_tables_later(square);
	}

}

Bitboard Pieces_Attacks::precomputed_king_attacks(unsigned int square) const
{
	return KING_ATTACKS_TABLE[square];
}