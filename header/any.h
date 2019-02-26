#ifndef ANY_H
#define ANY_H

#include "op.h"


struct any: op {
    object *eval(object *o) override{
        std::cout<<"any: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "any";
    }
};

#endif /* ANY_H */
