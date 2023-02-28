#pragma once
#include "types.h"
#include "bitboard.h"

class Pieces_Attacks
{
	public:
		Pieces_Attacks(); // default constructor
		Bitboard pawn_attacks_used_to_precompute_attack_tables_later(const bool, const unsigned int) const;
};
