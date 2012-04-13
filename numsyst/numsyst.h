#include <string>

#include "big_int.h"

big_int decode(const std::string& s, size_t base);
std::string encode(big_int a, size_t base);

