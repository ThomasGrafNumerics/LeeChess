#include "types.h"
#include "get_magic_number_candidate.h"

Get_Magic_Number_Candidate::Get_Magic_Number_Candidate(const uint32_t xorshift32_seed) : current_xorshift32_sequence_element{xorshift32_seed} {}

uint32_t Get_Magic_Number_Candidate::get_and_update_xorshift32_prn(void)
{
	current_xorshift32_sequence_element ^= current_xorshift32_sequence_element << 13;
	current_xorshift32_sequence_element ^= current_xorshift32_sequence_element >> 17;
	current_xorshift32_sequence_element ^= current_xorshift32_sequence_element <<  5;

	return current_xorshift32_sequence_element;
}

// uint64_t Get_Magic_Number_Candidate::get_and_update_special_64bit_prn(void)
// {
// 	uint64_t n0, n1, n2, n3;
// 	n0 = static_cast<uint64_t>( get_and_update_xorshift32_prn() ) & 0xFFFF;
// 	n1 = static_cast<uint64_t>( get_and_update_xorshift32_prn() ) & 0xFFFF;
// 	n2 = static_cast<uint64_t>( get_and_update_xorshift32_prn() ) & 0xFFFF;
// 	n3 = static_cast<uint64_t>( get_and_update_xorshift32_prn() ) & 0xFFFF;

// 	return n0 | (n1 << 16) | (n2 << 32) | (n3 << 48);
// }	

// uint64_t Get_Magic_Number_Candidate::operator()()
// {
// 	return get_and_update_special_64bit_prn() & get_and_update_special_64bit_prn() & get_and_update_special_64bit_prn();
// }
