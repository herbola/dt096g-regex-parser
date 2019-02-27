# DT096G-Parsing-Labb1

Edit the input file and the source file
There is a few quickfixes issued to pointers
### Run
c++ compiler required.
run Make in cmd 
and run file output.exe

## Grammar

<RE> ::= <substitute>  |  <simple-RE>
<substitute>	::=	<simple-RE>  "|" <RE>
<simple-RE>	::=  concatenation> | <basic-RE> 
<concatenation> ::= <basic-RE> <simple-RE> 
<basic-RE>	::= <star> | <plus> | <counter> | <lowercase> | <capture> | <elementary-RE>
<capture> ::= <elementary-RE> "\O" <counter>
<lowercase> ::= <elementary-RE> "\I"
<star>	::=	<elementary-RE> "*"
<counter> ::= <elementary-Re>  "{" <digit> "}"
<plus> ::= <elementary-RE> "+"
<elementary-RE>	::=	 <char> | <group> | <any> 
<group>	::=	"(" <RE> ")"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<any>	::=	"."
<charachter>	::= <char>
  
### Output

![1](https://user-images.githubusercontent.com/43444902/53501921-51f0ce80-3aad-11e9-983e-a042ade41a46.PNG)
![2](https://user-images.githubusercontent.com/43444902/53501922-52896500-3aad-11e9-92f2-63b48aace06a.PNG)

