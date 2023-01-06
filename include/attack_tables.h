#pragma once
#include "../include/bitboard.h"

// extern Bitboard PAWN_ATTACKS_TABLE[2][64];
// extern Bitboard KNIGHT_ATTACKS_TABLE[64];
// extern Bitboard KING_ATTACKS_TABLE[64];
// extern Bitboard BISHOP_ATTACKS_MASK_TABLE[64];
// extern Bitboard ROOK_ATTACKS_MASK_TABLE[64];
// extern Bitboard BISHOP_ATTACKS_TABLE[64][512];
// extern Bitboard ROOK_ATTACKS_TABLE[64][4096];

Bitboard mask_pawn_attacks(const bool, const unsigned int);
Bitboard mask_knight_attacks(const unsigned int);
Bitboard mask_king_attacks(const unsigned int);
Bitboard mask_rook_attacks(const unsigned int);
Bitboard mask_bishop_attacks(const unsigned int);
Bitboard mask_occupancy(const Bitboard&, const unsigned int);
Bitboard mask_bishop_attacks_on_the_fly(const Bitboard&, const unsigned int);
Bitboard mask_rook_attacks_on_the_fly(const Bitboard&, const unsigned int);
Bitboard mask_occupancy(const Bitboard&, const unsigned int);
void init_leaper_attack_tables(void);