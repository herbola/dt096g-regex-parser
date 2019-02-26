#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include "op.h"
#include "object.h"


struct substitute : op {
    object *eval(object *o) override{
        std::cout<<"sub: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "substitute";
    }
};

#endif /* SUBSTITUTE_H */