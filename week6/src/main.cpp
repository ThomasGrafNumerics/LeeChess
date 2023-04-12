#include <iostream>
#include <fstream>
#include "types.h"
#include "bitboard.h"
#include "pieces_attacks.h"
#include "get_magic_number_candidate.h"

int main(void)
{
	// std::ofstream file;
	// file.open("xorshift32dataWeek6.dat");
	// Get_Magic_Number_Candidate MNC{123456789};
	// for (unsigned int k = 0; k < 10'000; ++k)
	// {
	// 	// std::cout << MNC.get_and_update_special_64bit_prn() << std::endl;
	// 	file << MNC.get_and_update_special_64bit_prn() << "\t" << MNC.get_and_update_special_64bit_prn() << "\t" << MNC.get_and_update_special_64bit_prn() << std::endl;
	// }
	// file.close();

	Pieces_Attacks attacks;
	for(unsigned int square = 0; square < 64; ++square)
	{
		std::cout << attacks.find_magic_number(0, square) << "\n";
	}

	return 0;
}
