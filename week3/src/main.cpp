#include <iostream>
#include "types.h"
#include "bitboard.h"
#include "pieces_attacks.h"

int main(void)
{
	Pieces_Attacks attacks;
	Bitboard king;
	attacks.precompute_leaper_pieces_attack_tables();

	for (unsigned square = 0; square < 64; ++square)
	{
		king = attacks.precomputed_king_attacks(square);
		king.print_bitboard();
	}

	return 0;
}
