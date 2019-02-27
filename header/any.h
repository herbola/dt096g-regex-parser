#ifndef ANY_H
#define ANY_H

#include "op.h"

struct any: op {
    object *eval(object *o) override {
        if(++o->rhs != o->end) {
            return o;
        }
        return nullptr;
    }
    std::string id() override{
        return "any";
    }
};

#endif /* ANY_H */
