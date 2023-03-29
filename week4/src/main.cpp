#include <iostream>
#include "types.h"
#include "bitboard.h"
#include "pieces_attacks.h"

int main(void)
{
	Pieces_Attacks attacks;
	Bitboard A, B, C;
	A.set_bit(A8);
	A.set_bit(B8);
	A.set_bit(D7);
	A.set_bit(F6);

	B.set_bit(H7);
	B.set_bit(H6);


	C = A * B;
	C.print_bitboard();

	return 0;
}
