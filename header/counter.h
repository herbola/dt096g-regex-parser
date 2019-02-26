#ifndef COUNTER_H
#define COUNTER_H

#include "op.h"


struct counter: op {
    object * eval(object *o) override {
        int counter = atoi(operands[1]->id().c_str());
        for(; counter > 0; counter--) {
            std::cout<<"counter: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<" COUNTER:"<<counter<<std::endl;
            object * temp = operands[0]->eval(o);
            if(!o) {
                return nullptr;
            }
            o = temp;
        }
        return o;
    }
    std::string id() override{
        return "counter";
    }
};

#endif /* COUNTER_H */
