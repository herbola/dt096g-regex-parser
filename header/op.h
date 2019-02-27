#ifndef OP_H
#define OP_H

#include <string>
#include <vector>
#include "object.h"
#include <iostream>


struct op {
    virtual object* eval(object * o) = 0;
    virtual std::string id() = 0;
    std::vector<op*> operands;
};

#endif /* OP_H */

