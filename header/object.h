#ifndef OBJECT_H
#define OBJECT_H
#include <string>


struct object {
    std::string::iterator lhs, rhs, end;
    object(std::string source){
        this->lhs = this->rhs = source.begin();
        this->end = source.end();
    }
};

#endif /* OBJECT_H */
