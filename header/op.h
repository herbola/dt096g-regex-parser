#ifndef OP_H
#define OP_H

#include <string>
#include <vector>

class op {
public:
    virtual double eval() = 0;
    virtual std::string id() = 0;
    std::vector<op*> operands;
private:

};

#endif /* OP_H */

