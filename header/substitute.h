#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include "op.h"
#include "object.h"

using it = std::string::iterator;
struct substitute : op {
    object *eval(object *o) override{
        it start = o->rhs;
        object * simple_re = operands[0]->eval(o);
        if(!simple_re) {
            simple_re = operands[1]->eval(o);
        }
        return simple_re;
    }
    std::string id() override{
        return "substitute";
    }
};

#endif /* SUBSTITUTE_H */