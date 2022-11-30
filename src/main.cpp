#include "bitboard.hpp"
#include "board.hpp"
#include "pieces_attack_tables.hpp"
#include <iostream>

#include <vector>
using namespace std;

int main(void)
{
	init_leaper_attack_tables();
	init_slider_attack_tables();
	//print_attacks();
	return 0;
}



