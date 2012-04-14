#include <string>

#include <gmpxx.h>

mpz_class decode(const std::string& s, size_t base);
std::string encode(mpz_class a, size_t base);

