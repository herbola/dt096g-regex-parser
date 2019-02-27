#ifndef GROUP_H
#define GROUP_H

#include "op.h"
#include "object.h"

using it = std::string::iterator;
struct group: op {
    object *eval(object *o) override{
        object * temp = o;
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "group";
    }
};

#endif /* GROUP_H */
