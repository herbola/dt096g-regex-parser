#ifndef COUNTER_H
#define COUNTER_H

#include "op.h"


struct counter: op {
    object * eval(object *o) override {
        int counter = atoi(operands[1]->id().c_str()) + 1;
        for(; counter > 0; counter--) {
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
