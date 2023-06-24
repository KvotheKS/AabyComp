%{
#include <iostream>
#include "sintatico.hh"
# define YY_DECL \
  yy::parser::symbol_type yylex ()
YY_DECL;
%}

/* %option debug */

digit  [0-9]
lower_case [a-z]
upper_case [A-Z]
alphabet ({lower_case}|{upper_case})
basic_sep [\t\n ]
number {digit}+
identifier {alphabet}({alphabet}|{digit})*
single_line_comment \/\/.*\n
multi_line_comment \$\{(.|\n)*\$\}\n
other .

%%

do                return yy::parser::token::TOK_DO;
else              return yy::parser::token::TOK_ELSE;
if                return yy::parser::token::TOK_IF;
fi                return yy::parser::token::TOK_FI;
in                return yy::parser::token::TOK_IN;
integer           return yy::parser::token::TOK_INTEGER;
read              return yy::parser::token::TOK_READ;
write             return yy::parser::token::TOK_WRITE;
let               return yy::parser::token::TOK_LET;
skip              return yy::parser::token::TOK_SKIP;
while             return yy::parser::token::TOK_WHILE;
then              return yy::parser::token::TOK_THEN;
end               return yy::parser::token::TOK_END;
":="              return yy::parser::token::TOK_ASSGNOP;
{single_line_comment} { ; }
{multi_line_comment}  { ; }
{basic_sep}       { ; }
{number}          return yy::parser::token::TOK_NUMBER;
{identifier}      {return yy::parser::make_IDENTIFIER (yytext);}
{other}           return yytext[0];
<<EOF>>           return yy::parser::token::TOK_YYEOF;
%%

void scan_begin (int argc, char** argv) {
  yy_flex_debug = 1;
  if ( argc > 0 ) {
            std::string filename = argv[0];
            yyin = fopen( argv[0], "r" );
    } else
            yyin = stdin;
}

void scan_end () {
  fclose (yyin);
}

int yywrap() {
  return 1;
}