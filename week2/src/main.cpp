#include <iostream>
#include "types.h"
#include "bitboard.h"
#include "pieces_attacks.h"

int main(void)
{
	Pieces_Attacks attacks;
	Bitboard board;

	for (unsigned square = 0; square < 64; ++square)
	{
		board = attacks.pawn_attacks_used_to_precompute_attack_tables_later(WHITE, square);
		board.print_bitboard();
	}

	return 0;
}
