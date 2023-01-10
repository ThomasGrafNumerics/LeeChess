#include <iostream>
#include "../include/bitboard.h"
#include "../include/attack_tables.h"
#include "../include/magic.h"


int main(void)
{
    print_magic_numbers();
    init_leaper_attack_tables();
    init_slider_attack_tables();

    return 0;
} 