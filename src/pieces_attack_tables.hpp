#pragma once
#include "bitboard.hpp"

Bitboard mask_pawn_attack(const int, const int);
Bitboard mask_knight_attack(const int);
Bitboard mask_king_attack(const int);
Bitboard mask_rook_attack(const int);
Bitboard mask_bishop_attack(const int);
Bitboard mask_occupancy(const Bitboard&, const int);
Bitboard mask_rook_attack_on_the_fly(const Bitboard&, const int);
