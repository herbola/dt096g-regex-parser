#ifndef STAR_H
#define STAR_H

#include "star.h"
#include "object.h"

struct star : op {
    object *eval(object *o){
          std::cout<<"star";
        object* elem = operands[0]->eval(o);
      
        if(elem) {
            char chr = *elem->rhs;
            while(*(elem->rhs+1) == chr) {
                elem->rhs++;
            }
        } 
        return elem;
    }
    std::string id() override{
        return "star";
    }
};

#endif /* STAR_H */