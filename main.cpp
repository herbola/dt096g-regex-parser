#include <cstdlib>
#include <iostream>
#include <string>
#include "header/op.h"
#include "header/token.h"
#include "header/re.h"
#include "header/simple_re.h"
#include "header/substitute.h"




/*
    
<RE>	::=	<simple-RE> | <substitute> 
<substitute>	::=	<simple-RE>  "|" <RE>
<simple-RE>	::=	<basic-RE> |  concatenation> 
<concatenation>	::=	<basic-RE> <simple-RE> 
<basic-RE>	::=	 <elementary-RE> | <plus> | <star> 
<star>	::=	<elementary-RE> "*" ändra sida
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
op* _count(it first , it last);
op* _digit(it first , it last);
op* _character(it first , it last);
op* _any(it first , it last);


op* _simple_re(it first , it last) {
    op* basic_re_or_concat = new simple_re;
    token tk = next_token(first, last);
}

op* _substitute(it first, it last) {
    token simple_re_tk = next_token(first, last);
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
    token re_tk = next_token(first, last);
    op* re_expr = new re;
    re_expr = _re(first, last);
    if(!re_expr) {
        std::cout<<"Syntax error in substitute, RE\n";
        return nullptr;
    }
    substitute_expr->operands.push_back(re_expr);
    return substitute_expr;
}

op* _re(it first, it last) {
    op* expr = new re;
    token tk = next_token(first, last);

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

