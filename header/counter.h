#ifndef COUNTER_H
#define COUNTER_H

#include "op.h"


struct counter: op {
    int counter = -1;
    object * eval(object *o) override {
        int hej;
        std::cin>>hej;
        std::cout<<"\n\n"<<counter<<"\n\n";
        if(counter = -1) {
            counter = atoi(operands[0]->id().c_str());
        }
        if(counter-- > 0) {
            return o;
        }
        return nullptr;
    }
    std::string id() override{
        return "counter";
    }
};

#endif /* COUNTER_H */
