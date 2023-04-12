#pragma once
#include "types.h"

class Get_Magic_Number_Candidate
{
	public:
		Get_Magic_Number_Candidate(const uint32_t xorshift32_seed);

		uint32_t get_and_update_xorshift32_prn(void);
		uint64_t get_and_update_special_64bit_prn(void);
		uint64_t operator()();

	private:
		uint32_t current_xorshift32_sequence_element;
		
};
