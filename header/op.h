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
    void print(std::string str, object* o) {
        std::cout<<std::endl<<"type: "<<str<<" ";
        std::string::iterator start, end;
        start = o->lhs;
        end = o->rhs;
        for(;start!=end+1; start++) { 
        std::cout<<*start;          
        }   
        std::cout<<std::endl;
    }
};

#endif /* OP_H */

