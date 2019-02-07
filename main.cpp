#include <cstdlib>
#include <iostream>
#include <string>
#include "header/program.h"
#include "header/op.h"
#include "header/token.h"

using it = std::string::iterator;

op* program_parse(it first, it last) {
    op* ast = new program;
    auto tk = next_token(first, last);
    first++;
}

int main(int argc, char** argv) {
    std::string source = "A = A + B";
    program_parse(source.begin(), source.end());
    return 0;
}

