#ifndef BASIC_RE_H
#define BASIC_RE_H

#include "op.h"


struct basic_re : op {
    object *eval(object *o) override{
        std::cout<<"basic: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "basic_re";
    }
};

#endif /* BASIC_RE_H */
