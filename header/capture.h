#ifndef CAPTURE_H
#define CAPTURE_H

#include "op.h"


struct capture: op {
    object *eval(object *o) override{
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "capture";
    }
};

#endif /* CAPTURE_H */
