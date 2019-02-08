#include <cstdlib>
#include <iostream>
#include <string>
#include "header/op.h"
#include "header/token.h"
#include "header/re.h"
#include "header/simple_re.h"
#include "header/substitute.h"
#include "header/basic_re.h"
#include "header/concat.h"
#include "header/elementary_re.h"
#include "header/plus.h"
#include "header/star.h"


/*
    
<RE>	::=	<simple-RE> | <substitute> 
<substitute>	::=	<simple-RE>  "|" <RE>
<simple-RE>	::=	<basic-RE> |  concatenation> 
<concatenation>	::=	<basic-RE> <simple-RE> 
<basic-RE>	::=	 <elementary-RE> | <plus> | <star> 
<star>	::=	<elementary-RE> "*" ändra sida?
<plus>	::=	<elementary-RE> "+"  ändra sida?
<elementary-RE>	::=	<char> | <group> | <any> | <counter>
<group>	::=	"(" <RE> ")"
<count> ::= "{" <digit> "}"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<any>	::=	"."
<charachter>	::=	any non metacharacter | "\" metacharacter

*/


/*
+ eller, passar ett av två alternativ. Syntax: OP1+OP2
* flera, passar ett eller flera upprepningar av en operand. Syntax: OP*
() infångningsgrupp, deluttryck. Uttrycket parsas separat. Syntax: (EXPR)
. tecken. matchar varlfritt tecken. Syntax: .
{} räknare. matchar precis N stycken operander. Syntax: OP{3}
\I ignorera versalisering. Syntax EXPR\I
\O{} vilken infångningsgrupp som ska ges som output. Syntax: EXPR\O{2}. Default \O{0} hela matchningen.
*/
using it = std::string::iterator;

op* _re(it first, it last);
op* _substitute(it first, it last);
op* _simple_re(it first , it last);
op* _concat(it first , it last);
op* _basic_re(it first , it last);
op* _star(it first , it last);
op* _plus(it first , it last);
op* _elementary_re(it first , it last);
op* _group(it first , it last);
op* _counter(it first , it last);
op* _digit(it first , it last);
op* _character(it first , it last);
op* _any(it first , it last);

op* _star(it first, it last) {
    op* elementary_re_expr = new elementary_re;
    elementary_re_expr = _elementary_re(first, last);
    if(!elementary_re_expr) {
        std::cout<<"Syntax error in _star, elementary_re_expr\n";
        return nullptr;
    }
    first++;
    token tk = next_token(first, last);
    if(tk.id != token::STAR) {
        std::cout<<"Syntax error in _star, token::STAR\n";
        return nullptr;
    }
    op* expr = new star;
    expr->operands.push_back(elementary_re_expr);
    return expr;
}

op* _plus(it first, it last) {
    op* elementary_re_expr = new elementary_re;
    elementary_re_expr = _elementary_re(first, last);
    if(!elementary_re_expr) {
        std::cout<<"Syntax error in _plus, elementary_re_expr\n";
        return nullptr;
    }
    first++;
    token tk = next_token(first, last);
    if(tk.id != token::PLUS) {
        std::cout<<"Syntax error in _plus, token::PLUS\n";
        return nullptr;
    }
    op* expr = new plus;
    expr->operands.push_back(elementary_re_expr);
    return expr;
}
op* _elementary_re(it first , it last) {
    op* char_group_any_counter = new elementary_re;
    char_group_any_counter = _character(first, first);
    if(!char_group_any_counter) {
        char_group_any_counter = _group(first, last);
        if(!char_group_any_counter) {
            char_group_any_counter = _any(first, last);
            if(!char_group_any_counter) {
                char_group_any_counter = _counter(first, last);
            }
        }
    }
    if(!char_group_any_counter) {
        std::cout<<"Syntax error in _elementary_re\n";
        return nullptr;
    }
    op* expr = new elementary_re;
    expr->operands.push_back(char_group_any_counter);
    return expr;
}
op* _concat(it first , it last) { // <concatenation> ::= <basic-RE> <simple-RE> 
    op* basic_re_expr = new basic_re;
    basic_re_expr = _basic_re(first, last);
    if(!basic_re_expr) {
        std::cout<<"Syntax error in _concat, basic_re\n";
        return nullptr;
    }
    first++;
    op* simple_re_expr = new simple_re;
    simple_re_expr = _simple_re(first, last);
    if(!simple_re_expr) {
        std::cout<<"Syntax error in _concat, simple_re\n";
        return nullptr;
    }
    op* expr = new concat;
    expr->operands.push_back(basic_re_expr);
    expr->operands.push_back(simple_re_expr);
    return expr;
}
op* _basic_re(it first , it last) { // <basic-RE> ::= <elementary-RE> | <plus> | <star> 
    op* elem_or_star_or_plus = _elementary_re(first, last);
    if(!elem_or_star_or_plus) {
        elem_or_star_or_plus = _star(first, last);
        if(!elem_or_star_or_plus) {
          elem_or_star_or_plus = _plus(first, last);  
        }
    }
    if(!elem_or_star_or_plus) {
       std::cout<<"Syntax error in _basic_re\n"; 
       return nullptr;
    }
    op* expr = new _basic_re;
    _basic_re->operands.push_back(elem_or_star_or_plus);
    return expr;
}
op* _simple_re(it first , it last) { // <simple-RE>	::=	<basic-RE> |  concatenation> 
    op* basic_re_or_concat = new simple_re;
    basic_re_or_concat = _basic_re(first, last);
    if(!basic_re_or_concat) {
        basic_re_or_concat = _concat(first, last);
    }
    if(!basic_re_or_concat) {
        std::cout<<"Syntax error in _simple_re\n";
        return nullptr;
    }
    op* expr = new simple_re;
    expr->operands.push_back(basic_re_or_concat);
    return expr;
}

op* _substitute(it first, it last) { // <substitute> ::= <simple-RE>  "|" <RE>
    op* substitute_expr = new substitute;
    op* simple_re_expr = _simple_re(first, last); //lhs
    if(!simple_re_expr) {
        std::cout<<"Syntax error in substitute, SIMPLE_RE\n";
        return nullptr;
    } else {
        substitute_expr->operands.push_back(simple_re_expr);
    }
    first++;
    token or_token = next_token(first, last);
    if(or_token.id = token::OR) {
        std::cout<<"Syntax error in substitute, OR \n";
        return nullptr;
    }
    first++;
    op* re_expr = new re;
    re_expr = _re(first, last);
    if(!re_expr) {
        std::cout<<"Syntax error in substitute, RE\n";
        return nullptr;
    }
    substitute_expr->operands.push_back(re_expr);
    return substitute_expr;
}

op* _re(it first, it last) { // <RE> ::= <simple-RE> | <substitute> 
    op* expr = new re;
    op* simple_or_substitue= _simple_re(first, last);
    if (!simple_or_substitue) {
        simple_or_substitue= _substitute(first, last);
    }
    if(!simple_or_substitue) {
        std::cout<<"Syntax error in _re\n";
        return nullptr;
    }
    expr->operands.push_back(simple_or_substitue);
    return expr;
}

int main(int argc, char** argv) {
    std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    std::string input = "lo* could.{3}";
    op* result = _re(input.begin(), input.end());
    int stop;
    std::cin>>stop;
    return 0;
}

