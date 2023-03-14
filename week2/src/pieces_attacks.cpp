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

// Bitboard Pieces_Attacks::knight_attacks_used_to_precompute_attack_tables_later(const unsigned int square) const
// {
// 	Bitboard attack(0), temp(0);
// 	temp.set_bit(square);

// 	return attack;
// }

// Bitboard Pieces_Attacks::king_attacks_used_to_precompute_attack_tables_later(const unsigned int square) const
// {
// 	Bitboard attack(0), temp(0);
// 	temp.set_bit(square);

// 	return attack;
// }

// Bitboard Pieces_Attacks::rook_attacks_used_to_precompute_attack_tables_later(const Bitboard blockers, const unsigned int square) const
// {
// 	Bitboard attack(0);


// 	return attack;
// }

// Bitboard Pieces_Attacks::bishop_attacks_used_to_precompute_attack_tables_later(const Bitboard blockers, const unsigned int square) const
// {
// 	Bitboard attack(0);


// 	return attack;
// }