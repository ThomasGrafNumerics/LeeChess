#pragma once
#include "types.h"
#include "bitboard.h"

class Pieces_Attacks
{
	public:
		// Pieces_Attacks(void); // default constructor

		Bitboard pawn_attacks_used_to_precompute_attack_tables_later(const bool, const unsigned int) const;
		Bitboard knight_attacks_used_to_precompute_attack_tables_later(const unsigned int) const;
		Bitboard king_attacks_used_to_precompute_attack_tables_later(const unsigned int) const;
		Bitboard rook_attacks_used_to_precompute_attack_tables_later(const Bitboard, const unsigned int) const;
		Bitboard bishop_attacks_used_to_precompute_attack_tables_later(const Bitboard, const unsigned int) const;

		Bitboard rook_mark_all_possible_blocker_squares_for_given_square(const unsigned int) const;
		Bitboard bishop_mark_all_possible_blocker_squares_for_given_square(const unsigned int) const;

		Bitboard give_kth_possible_blocker_configuration_within_given_attack_mask(const Bitboard, const unsigned int) const;

	private:
		static constexpr int ROOK_NUMBER_OF_RELEVANT_SQUARES_TABLE[64] =
		{
			12, 11, 11, 11, 11, 11, 11, 12, 
			11, 10, 10, 10, 10, 10, 10, 11, 
			11, 10, 10, 10, 10, 10, 10, 11, 
			11, 10, 10, 10, 10, 10, 10, 11, 
			11, 10, 10, 10, 10, 10, 10, 11, 
			11, 10, 10, 10, 10, 10, 10, 11, 
			11, 10, 10, 10, 10, 10, 10, 11, 
			12, 11, 11, 11, 11, 11, 11, 12
		};

		static constexpr int BISHOP_NUMBER_OF_RELEVANT_SQUARES_TABLE[64] =
		{
			6, 5, 5, 5, 5, 5, 5, 6, 
			5, 5, 5, 5, 5, 5, 5, 5, 
			5, 5, 7, 7, 7, 7, 5, 5, 
			5, 5, 7, 9, 9, 7, 5, 5, 
			5, 5, 7, 9, 9, 7, 5, 5, 
			5, 5, 7, 7, 7, 7, 5, 5, 
			5, 5, 5, 5, 5, 5, 5, 5, 
			6, 5, 5, 5, 5, 5, 5, 6
			};
};