#include <iostream>
#include "types.h"
#include "bitboard.h"
#include "pieces_attacks.h"
#include "get_magic_number_candidate.h"

int main(void)
{
	Get_Magic_Number_Candidate MNC{123456789};
	for (unsigned int k = 0; k < 1'000'000; ++k)
	{
		// std::cout << MNC.get_and_update_xorshift32_prn() << std::endl;
		MNC.get_and_update_xorshift32_prn();
	}

	return 0;
}
