#include "pieces_attacks.h"

Pieces_Attacks::Pieces_Attacks() : MNC{1804289383} {}
Pieces_Attacks::Pieces_Attacks(const uint32_t xorshift32_seed) : MNC{xorshift32_seed} {}

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


uint64_t Pieces_Attacks::find_magic_number(const bool is_rook, const unsigned int square)
{
	const unsigned int number_of_relevant_squares = (is_rook ?  ROOK_NUMBER_OF_RELEVANT_SQUARES_TABLE[square] : BISHOP_NUMBER_OF_RELEVANT_SQUARES_TABLE[square]);
	const unsigned int max_number_of_possible_blocker_configurations = 1 << number_of_relevant_squares;

	Bitboard *occupancies = new Bitboard[max_number_of_possible_blocker_configurations]();
	Bitboard *attacks = new Bitboard[max_number_of_possible_blocker_configurations]();
	Bitboard *used_attacks = new Bitboard[max_number_of_possible_blocker_configurations]();
	Bitboard reduced_attack_mask = (is_rook ? rook_give_reduced_attack_mask_for_given_square(square) : bishop_give_reduced_attack_mask_for_given_square(square));
	
	for (unsigned int k = 0; k < max_number_of_possible_blocker_configurations; ++k)
	{
		occupancies[k] = give_kth_possible_blocker_configuration_within_given_reduced_attack_mask(reduced_attack_mask, k);

		if (is_rook)
		{

			attacks[k] = rook_attacks_used_to_precompute_attack_tables_later(occupancies[k], square);
		}
		else
		{
			attacks[k] = bishop_attacks_used_to_precompute_attack_tables_later(occupancies[k], square);
		}
	}

	while (true)
	{
		uint64_t magic_number_candidate =  MNC();

		if ( Bitboard( (reduced_attack_mask * magic_number_candidate) & 0xff00000000000000 ).get_number_of_set_bits() < 6 )
		{
			continue;
		}

		std::fill(used_attacks, used_attacks + max_number_of_possible_blocker_configurations, 0);
		bool failed = false;
		for (unsigned int k = 0; k < max_number_of_possible_blocker_configurations; ++k)
		{
			unsigned int magic_index = static_cast<unsigned int> ( (occupancies[k] * magic_number_candidate) >> (64 - number_of_relevant_squares) );
			if (used_attacks[magic_index] == 0)
			{
				used_attacks[magic_index] = attacks[k];
			}
			else if (used_attacks[magic_index] != attacks[k])
			{
				failed = true;
				break;
			}
		}
		if (!failed)
		{
			delete[] occupancies;
			delete[] attacks;
			delete[] used_attacks;
			return magic_number_candidate;
		}
	}
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