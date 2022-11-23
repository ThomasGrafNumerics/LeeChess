#include "bitboard.hpp"
#include <iostream>

int main(void)
{
  Bitboard b(0);
  b.print_bitboard();
  Bitboard a(0b101);
  a.print_bitboard();
  return 0;
}
