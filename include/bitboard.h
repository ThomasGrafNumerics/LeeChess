#pragma once
#include <array>

using U64 = unsigned long long;

class Bitboard
{
  private:
    U64 bitboard;

  public:
    // constructors
    Bitboard(); // default constructor
    Bitboard(const U64); // constructor
    Bitboard(const Bitboard&); // copy constructor
    Bitboard& operator=(const Bitboard& rhs) // copy assignment operator
    { 
      bitboard = rhs.bitboard;
      return *this;
    }; 

    // user-defined conversion functions
    operator U64&();
    operator U64() const;

    // Bitboard operations
    bool get_bit(const unsigned int) const;
    void print_bitboard(void) const;
    U64 get_bitboard_value(void) const;
    void set_bit(const unsigned int);
    void clear_bit(const unsigned int);
    void invert_bit(const unsigned int);
    void clear_LS_set_bit(void);
    void clear_bitboard(void);
    unsigned int get_number_of_set_bits(void) const;
    unsigned int get_index_of_LS_set_bit(void) const;
};

constexpr U64 NOT_A_FILE_MASK  = 18374403900871474942ull;
constexpr U64 NOT_H_FILE_MASK  =  9187201950435737471ull;
constexpr U64 NOT_AB_FILE_MASK = 18229723555195321596ull;
constexpr U64 NOT_GH_FILE_MASK =  4557430888798830399ull;

constexpr std::array<const char*, 64> square_to_string_table =
{
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

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

constexpr int BISHOP_NUMBER_OF_RELEVANT_BITS_TABLE[64] =
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

constexpr int ROOK_NUMBER_OF_RELEVANT_BITS_TABLE[64] =
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