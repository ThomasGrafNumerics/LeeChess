#pragma once
#include "bitboard.hpp"

constexpr int BISHOP_RELEVANT_BITS_TABLE[64] =
{
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

constexpr int ROOK_RELEVANT_BITS_TABLE[64] =
{
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

extern Bitboard PAWN_ATTACK_TABLE[2][64];
extern Bitboard KNIGHT_ATTACK_TABLE[64];
extern Bitboard KING_ATTACK_TABLE[64];

extern Bitboard BISHOP_ATTACK_MASK_TABLE[64];
extern Bitboard ROOK_ATTACK_MASK_TABLE[64];
extern Bitboard BISHOP_ATTACK_TABLE[64][512];
extern Bitboard ROOK_ATTACK_TABLE[64][4096];

Bitboard mask_pawn_attack(const int, const int);
Bitboard mask_knight_attack(const int);
Bitboard mask_king_attack(const int);
Bitboard mask_rook_attack(const int);
Bitboard mask_bishop_attack(const int);
Bitboard mask_occupancy(const Bitboard&, const int);
Bitboard mask_bishop_attack_on_the_fly(const Bitboard&, const int);
Bitboard mask_rook_attack_on_the_fly(const Bitboard&, const int);

void init_leaper_attack_tables(void);
void init_slider_attack_tables(void);


void print_attacks(void);