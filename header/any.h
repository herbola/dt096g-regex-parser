#ifndef ANY_H
#define ANY_H

#include "op.h"


struct any: op {
    std::string eval(std::string source) {
        return source;
    }
    std::string id() override{
        return "any";
    }
};

#endif /* ANY_H */
