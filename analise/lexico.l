%{
    #include "sintatico.tab.h"
%}

digit  [0-9]
lower_case [a-z]
upper_case [A-Z]
alphabet ({lower_case}|{upper_case})
basic_sep [\t\n\ ]
number {digit}+
identifier {alphabet}({alphabet}|{digit})*
single_line_comment \/\/.*\n
multi_line_comment \$\{(.|\n)*\$\}\n
other .

%%
do              { return (DO);}
else            { return (ELSE);}
if              { return (IF);}
fi              { return (FI);}
in              { return (IN);}
integer         { return (INTEGER);}
read            { return (READ);}
write           { return (WRITE);}
let             { return (LET);}
skip            { return (SKIP);}
while           { return (WHILE);}
then            { return (THEN);}
end             { return (END);}
":="            { return (ASSGNOP);}
{basic_sep}     /* empty */
{single_line_comment} { ; }
{multi_line_comment}  { ; }
{number}        { return (NUMBER);}
{identifier}    { return (IDENTIFIER);}
{other}  { return(yytext[0]); }
%%

int yywrap();

int yywrap()
{
    return 1;
}