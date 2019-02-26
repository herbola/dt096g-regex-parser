#ifndef ANY_H
#define ANY_H

#include "op.h"


struct any: op {
    object *eval(object *o) override{
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "any";
    }
};

#endif /* ANY_H */
