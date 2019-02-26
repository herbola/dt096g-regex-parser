#ifndef COUNTER_H
#define COUNTER_H

#include "op.h"


struct counter: op {
    object *eval(object *o) override{
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "counter";
    }
};

#endif /* COUNTER_H */
