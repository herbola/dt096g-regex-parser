#ifndef RE_H
#define RE_H

#include "op.h"
#include "object.h"

struct re : op {
    object *eval(object *o) override{
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "re";
    }
};

#endif /* RE_H */
