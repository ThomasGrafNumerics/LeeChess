#pragma once
#include "types.h"

class Bitboard
{
	public:
		// constructors
		Bitboard(void); // default constructor
		Bitboard(const uint64_t); // constructor
		Bitboard(const Bitboard&); // copy constructor
		Bitboard& operator=(const Bitboard& rhs) // copy assignment operator
		{ 
			bitboard = rhs.bitboard;
			return *this;
		}; 

		// user-defined conversion functions
		operator uint64_t&();
		operator uint64_t() const;

		bool get_bit(const unsigned int) const;
		void print_bitboard(void) const;
		uint64_t get_bitboard_value(void) const;
		void set_bit(const unsigned int);
		void clear_bitboard(void);

	private:
		uint64_t bitboard;
};
