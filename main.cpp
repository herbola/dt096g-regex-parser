#include <cstdlib>
#include <iostream>
#include <string>
#include "header/op.h"
#include "header/token.h"
#include <regex>


using it = std::string::iterator;

/*
    
<RE>	::=	<union> | <simple-RE>
<union>	::=	<RE> "|" <simple-RE>
<simple-RE>	::=	<concatenation> | <basic-RE>
<concatenation>	::=	<simple-RE> <basic-RE>
<basic-RE>	::=	<star> | <plus> | <elementary-RE>
<star>	::=	<elementary-RE> "*"
<plus>	::=	<elementary-RE> "+"
<elementary-RE>	::=	<group> | <any> | <eos> | <char> | <set>
<group>	::=	"(" <RE> ")"
<any>	::=	"."
<eos>	::=	"$"
<char>	::=	any non metacharacter | "\" metacharacter
<set>	::=	<positive-set> | <negative-set>
<positive-set>	::=	"[" <set-items> "]"
<negative-set>	::=	"[^" <set-items> "]"
<set-items>	::=	<set-item> | <set-item> <set-items>
<set-items>	::=	<range> | <char>
<range>	::=	<char> "-" <char>
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
op* program_parse(it first, it last) {
    auto tk = next_token(first, last);
    first++;
}

int main(int argc, char** argv) {
    std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    std::string input = "lo* could.{3}";
    op* result = program_parse(input.begin(), input.end());
    return 0;
}

