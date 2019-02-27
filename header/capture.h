#ifndef CAPTURE_H
#define CAPTURE_H

#include "op.h"


struct capture: op {
    object *eval(object *o) override{
        o->captured = atoi(operands[1]->operands[0]->id().c_str());
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "capture";
    }
};

#endif /* CAPTURE_H */
