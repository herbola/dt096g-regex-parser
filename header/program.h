#ifndef PROGRAM_H
#define PROGRAM_H

#include "op.h"
#include "object.h"

struct program : op {
    object *eval(object *o) override{
        while(o->rhs != o->end) {
            std::cout<<"re: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
            object * re = operands[0]->eval(o);
            if(re) {
                return re;
            }
            o->lhs = ++o->rhs;
        }
        return nullptr;
    }
    std::string id() override{
        return "program";
    }
};

#endif /* PROGRAM_H */
 