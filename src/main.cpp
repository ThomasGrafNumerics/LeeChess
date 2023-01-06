#include <iostream>
#include "../include/bitboard.h"
#include "../include/attack_tables.h"
#include "../include/magic.h"


int main(void)
{
    init_leaper_attack_tables();
    Bitboard b;

    for (int square = 0; square < 64; ++square)
    {
        b = KING_ATTACKS_TABLE[square];
        b.print_bitboard();
    }
    return 0;
} 