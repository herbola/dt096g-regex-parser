#ifndef GROUP_H
#define GROUP_H

#include "op.h"
#include "object.h"

struct group: op {
    object *eval(object *o) override{
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "group";
    }
};

#endif /* GROUP_H */
