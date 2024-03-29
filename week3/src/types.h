#pragma once
#include <cstdint>
#include <array>

// user defined literal
constexpr std::int64_t operator "" _int64(unsigned long long v)
{ return static_cast<std::int64_t>(v); }

constexpr uint64_t NOT_A_FILE_MASK  = 18374403900871474942_int64;
constexpr uint64_t NOT_H_FILE_MASK  =  9187201950435737471_int64;
constexpr uint64_t NOT_AB_FILE_MASK = 18229723555195321596_int64;
constexpr uint64_t NOT_GH_FILE_MASK =  4557430888798830399_int64;

constexpr std::array<const char*, 12> unicode_pieces = {"♟", "♞", "♝", "♜", "♛", "♚", "♙", "♘", "♗", "♖", "♕", "♔"};

enum Squares
{
	A8, B8, C8, D8, E8, F8, G8, H8,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A1, B1, C1, D1, E1, F1, G1, H1,
	FORBIDDEN_SQUARE = 64
};

enum Colors {WHITE, BLACK, BOTH_SIDES};

enum Ranks {RANK_8, RANK_7, RANK_6, RANK_5, RANK_4, RANK_3, RANK_2, RANK_1};

enum Files {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};