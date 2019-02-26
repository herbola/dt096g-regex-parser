#ifndef CONCAT_H
#define CONCAT_H

#include "op.h"


struct concat : op {
    object *eval(object *o){
       
    }
    std::string id() override{
        return "concat";
    }
};

#endif /* CONCAT_H */
