#pragma once
#include <cstdint>

// user defined literal
constexpr std::int64_t operator "" _int64(unsigned long long v)
{ return static_cast<std::int64_t>(v); }


