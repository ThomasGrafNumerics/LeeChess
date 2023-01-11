#include <iostream>
#include "../include/bitboard.h"
#include "../include/attack_tables.h"
#include "../include/magic.h"


int main(void)
{
    //print_magic_numbers();
    init_leaper_attack_tables();
    init_slider_attack_tables();

    Bitboard blocker(0);
    blocker.set_bit(D5);
    blocker.set_bit(E1);
    blocker.set_bit(F4);
    blocker.set_bit(E5);
    blocker.print_bitboard();
    Bitboard b = get_bishop_attack_exact(B7, blocker);
    b.print_bitboard();

    return 0;
} 