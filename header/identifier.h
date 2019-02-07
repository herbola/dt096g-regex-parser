#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <iostream>

#include "op.h"


struct identifier:op {
    double eval() override{
        double val;
        std::cout << "Enter value for " << _id << ":\n";
        std::cin >> val;
        return val;
    };

    std::string id(){
        return _id;
    }
    double _val;
    std::string _id;
};

#endif /* IDENTIFIER_H */