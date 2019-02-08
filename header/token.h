#include <string>
#include <cctype>
struct token {

    enum id {
        ID,
        ANY,
        PLUS, 
        STAR,
        OR,
        SLASH, 
        LEFT_PAR,
        RIGHT_PAR,
        LEFT_BRA,
        RIGHT_BRA, 
        END_PROGRAM
    };
    id id;
    std::string text;
};


using it = std::string::iterator;

token next_token(it& first, it& last) {
    while (std::isspace(*first)) {
        first++;
    }

    if( first == last) {
        return { token::END_PROGRAM, ""};
    }

    token tk;

    switch(*first) {
        case '+':
            tk = {token::PLUS, "+"};
            break;
        case '*':
            tk = {token::STAR, "*"};
            break;
        case '.':
            tk = {token::ANY, "."};
            break;
        case '|':
            tk = {token::OR, "|"};
        break;
        case '(':
            tk = {token::LEFT_PAR, "("};
            break;
        case ')':
            tk = {token::RIGHT_PAR, ")"};
            break;
        case '{':
            tk = {token::LEFT_BRA, "{"};
            break;
        case '}':
            tk = {token::RIGHT_BRA, "}"};
            break;
        case '/':
            tk = {token::SLASH, "/"};
            break;
        default: 
            tk = {token::ID, std::string(first, first+1)};
    };
    return tk;
}