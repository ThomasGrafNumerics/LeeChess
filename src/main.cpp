#include "bitboard.hpp"
#include "board.hpp"
#include "pieces_attack_tables.hpp"
#include <iostream>

#include <vector>
using namespace std;

int main(void)
{
	Bitboard block(0);
	block.print_bitboard();

	block.set_bit(D7);
	block.set_bit(D1);
	block.set_bit(D2);
	block.set_bit(B4);
	block.set_bit(G4);
	block.print_bitboard();


	Bitboard rfly = mask_rook_attack_on_the_fly(block, D4);
	rfly.print_bitboard();
	return 0;
}



