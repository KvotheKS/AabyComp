%{
    #include <stdio.h>    
%}

digit  [0-9]
lower_case [a-z]
upper_case [A-Z]
alphabet ({lower_case}|{upper_case})
basic_sep [\t\n\ ]
number {digit}+{basic_sep}
float  {digit}+\.{digit}*{basic_sep}
identifier {alphabet}({alphabet}|{digit})*{basic_sep}
single_line_comment \/\/.*\n
multi_line_comment \$\{.*\$\}{basic_sep}
other .*\n

%%
-{number} { printf("INTEIRO NEGATIVO IDENTIFICADO\n"); }
[+]?{number} { printf("INTEIRO POSITIVO IDENTIFICADO\n"); }
-{float} { printf("FLOAT NEGATIVO IDENTIFICADO\n"); }
[+]?{float} { printf("FLOAT POSITIVO IDENTIFICADO\n"); }
{identifier} { printf("IDENTIFICADOR IDENTIFICADO\n"); }
{single_line_comment} { printf("COMENTARIO DE LINHA UNICA\n"); }
{multi_line_comment}  { printf("COMENTARIO DE LINHA MULTIPLA\n"); }
{other}  { printf("TOKEN NAO IDENTIFICADO\n"); }
%%

int yywrap();

int main() {
    printf("Digite um token e aperte enter\n");
    yylex();
}

int yywrap()
{
    return 1;
}