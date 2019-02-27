#ifndef ELEMENTARY_RE_H
#define ELEMENTARY_RE_H

#include "op.h"
#include "object.h"
#include <iostream>

struct elementary_re: op {
    object *eval(object *o) override{
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "elementary_re";
    }
};

#endif /* ELEMENTARY_RE_H */
