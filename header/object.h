#ifndef OBJECT_H
#define OBJECT_H
#include <string>


struct object {
    std::string::iterator lhs, rhs, end;
    bool found = false;
};

#endif /* OBJECT_H */