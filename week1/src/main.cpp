#include <iostream>
#include "types.h"
#include "bitboard.h"

int main(void)
{
	Bitboard b{0b0001001111111111111111111111111111111111111111111111111111111010};

	for (unsigned int k = 0; k < 64; ++k)
	{
		std::cout << b.get_bit(k) << std::endl;
	}

	return 0;
}