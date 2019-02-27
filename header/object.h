#ifndef OBJECT_H
#define OBJECT_H
#include <string>
using it = std::string::iterator;

struct iter {
    it lhs;
    it rhs;
};

struct object {
    it lhs, rhs, end;
    bool lower = false;
    size_t captured = 0;
    std::vector<iter> cap;
};

#endif /* OBJECT_H */
