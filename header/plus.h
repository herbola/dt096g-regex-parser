#ifndef PLUS_H
#define PLUS_H

#include "op.h"
#include "object.h"


struct plus : op {
    object *eval(object *o) override{
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "plus";
    }
};

#endif /* PLUS_H */