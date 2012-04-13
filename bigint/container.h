#ifndef containerH
#define containerH

#include <cstddef>
#include <iostream>

typedef long long digit_t;

class badindex{};

struct container
{
    explicit container(size_t size = 0);
    container(const container&);
    container& operator=(const container&);
    void resize(size_t);
    size_t size() const;
    digit_t& operator[](size_t);
    digit_t operator[](size_t) const;
    ~container();
    void swap(container&);
private:
    container(const container&, size_t);
    size_t size_;
    union {
        digit_t * digits_;
        digit_t digit_;
    };

    friend std::ostream& operator<<(std::ostream&, const container&);
};

#endif
