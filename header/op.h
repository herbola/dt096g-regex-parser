#ifndef OP_H
#define OP_H

#include <string>
#include <vector>

struct op {
    virtual std::string eval(std::string source) = 0;
    virtual std::string id() = 0;
    std::vector<op*> operands;
};

#endif /* OP_H */

