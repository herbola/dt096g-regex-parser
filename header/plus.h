#ifndef PLUS_H
#define PLUS_H

#include "op.h"
#include "object.h"


struct plus : op {
    object *eval(object *o) override{
        std::cout<<"plus: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "plus";
    }
};

#endif /* PLUS_H */