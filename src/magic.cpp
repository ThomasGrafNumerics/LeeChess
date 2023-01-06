#include <iostream>
#include "../include/bitboard.h"
#include "../include/attack_tables.h"
#include "../include/magic.h"

XORshift32::operator unsigned int&() { return random_state; }
XORshift32::operator unsigned int() const { return random_state; }

unsigned int XORshift32::get_random_value(void) const { return random_state;}

void XORshift32::update_random_state(void)
{
    random_state ^= random_state << 13;
    random_state ^= random_state >> 17;
    random_state ^= random_state << 5;
}

unsigned int XORshift32::random_state = 1804289383;

U64 generate_random_U64_number(XORshift32& rng)
{
    U64 n1, n2, n3, n4;
    n1 = (U64)(++rng) & 0xFFFF;
    n2 = (U64)(++rng) & 0xFFFF;
    n3 = (U64)(++rng) & 0xFFFF;
    n4 = (U64)(++rng) & 0xFFFF;
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

U64 generate_magic_number_candidate(XORshift32& rng)
{
    return generate_random_U64_number(rng) & generate_random_U64_number(rng) & generate_random_U64_number(rng);
}

Bitboard BISHOP_MAGIC_NUMBERS_TABLE[64] = {};
Bitboard ROOK_MAGIC_NUMBERS_TABLE[64] = {};

U64 find_magic_number(const unsigned int square, const bool is_bishop, XORshift32& rng)
{
	int relevant_bits = (is_bishop ? BISHOP_RELEVANT_NUMBER_OF_BITS_TABLE[square] : ROOK_RELEVANT_NUMBER_OF_BITS_TABLE[square]);
	int occupancies_variation = 1 << relevant_bits;

	Bitboard *occupancies = new Bitboard[occupancies_variation]();
	Bitboard *attacks = new Bitboard[occupancies_variation]();
	Bitboard *used_attacks = new Bitboard[occupancies_variation]();
	Bitboard attack_mask = (is_bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square));
	
	for (int index = 0; index < occupancies_variation; ++index)
	{
		occupancies[index] = mask_occupancy(attack_mask, index);

		if (is_bishop)
        {
            attacks[index] = mask_bishop_attacks_on_the_fly(occupancies[index], square);
        }
		else
        {
            attacks[index] = mask_rook_attacks_on_the_fly(occupancies[index], square);
        }
	}

	while (true)
	{
		U64 magic_num_candidate = generate_magic_number_candidate(rng);

		if ( Bitboard( (attack_mask * magic_num_candidate) & 0xff00000000000000 ).get_number_of_set_bits() < 6 ) continue;

		std::fill(used_attacks, used_attacks + occupancies_variation, 0);
		bool failed = false;
		for (int index = 0; index < occupancies_variation; ++index)
		{
			int magic_index = int( (occupancies[index] * magic_num_candidate) >> (64 - relevant_bits) );
			if (used_attacks[magic_index] == 0)
            {
                used_attacks[magic_index] = attacks[index];
            }
			else if (used_attacks[magic_index] != attacks[index])
			{
			    failed = true;
				break;
			}
		}
		if (!failed)
		{
			delete[] occupancies;
			delete[] attacks;
			delete[] used_attacks;
			return magic_num_candidate;
		}
	}
}

Bitboard * init_rook_magic_numbers(XORshift32& rng)
{
	for (int square = 0; square < 64; ++square)
	{
		ROOK_MAGIC_NUMBERS_TABLE[square] = find_magic_number(square, false, rng);
	}
    return ROOK_MAGIC_NUMBERS_TABLE;
}

Bitboard * init_bishop_magic_numbers(XORshift32& rng)
{
	for (int square = 0; square < 64; ++square)
	{
		BISHOP_MAGIC_NUMBERS_TABLE[square] = find_magic_number(square, true, rng);
	}
    return BISHOP_MAGIC_NUMBERS_TABLE;
}

void print_magic_numbers(void)
{
    XORshift32 rng;

    Bitboard * magic_rook = init_rook_magic_numbers(rng);
    Bitboard * magic_bishop = init_bishop_magic_numbers(rng);

	std::cout << "rook magic numbers:" << std::endl;
    for (int square = 0; square < 64; ++square)
    {
        std::cout << "0x" << std::hex << magic_rook[square].get_bitboard_value() << "ull," << std::endl;
    }

	std::cout << std::endl << "bishop magic numbers:" << std::endl;

    for (int square = 0; square < 64; ++square)
    {
        std::cout << "0x" <<std::hex << magic_bishop[square].get_bitboard_value() << "ull," << std::endl;
    }
}