#include <iostream>
#include "types.h"
#include "bitboard.h"

int main(void)
{
	Bitboard b{7};
	for (unsigned int k = 0; k < 64; ++k)
	{
		std::cout << b.get_bit(k) << std::endl;
	}
	return 0;
}