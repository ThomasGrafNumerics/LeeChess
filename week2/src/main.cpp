#include <iostream>
#include "types.h"
#include "bitboard.h"
#include "pieces_attacks.h"

int main(void)
{
	Pieces_Attacks attacks;
	Bitboard board;
	Bitboard blockers;
	blockers.set_bit(D4);
	blockers.set_bit(D2);
	blockers.set_bit(A6);
	blockers.set_bit(F6);
	blockers.set_bit(B6);
	blockers.set_bit(D7);
	blockers.set_bit(H1);

	board = attacks.rook_attacks_used_to_precompute_attack_tables_later(blockers, H1);
	board.print_bitboard();

	for (unsigned square = 0; square < 64; ++square)
	{
		board = attacks.bishop_attacks_used_to_precompute_attack_tables_later(blockers, square);
		board.print_bitboard();
	}

	return 0;
}
