#ifndef LOWERCASE_H
#define LOWERCASE_H
#include <cstring>
#include "op.h"
#include "object.h"

using it = std::string::iterator;
struct lowercase: op {
    object * eval(object* o) override {
        std::cout<<"lower: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        o->lower = true;
        o = operands[0]->eval(o);
        if(o) o->lower = false;
        return o;
    }
    std::string id() override{
        return "lowercase";
    }
};

#endif /* LOWERCASE_H */
