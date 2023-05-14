%{
#include <stdio.h> 
%}
%start program
%token LET
%token IN
%token INTEGER
%token SKIP
%token IF
%token FI
%token THEN
%token ELSE
%token END
%token WHILE
%token DO
%token READ
%token WRITE
%token ASSGNOP
%token NUMBER
%token IDENTIFIER
%left '-' '+'
%left '*' '/'
%right '^'
%%
program: LET declarations IN command_seq END {;}
;

declarations: /*empty*/
        | INTEGER id_seq IDENTIFIER '.' {;}
;

id_seq: /* empty */
        | id_seq IDENTIFIER ',' {;}
;

command_seq: /* empty */
        | command_seq command ';' {;}
;

command: SKIP
        | READ IDENTIFIER   {;}
        | WRITE exp {;}
        | IDENTIFIER ASSGNOP exp    {;}
        | IF exp THEN command_seq ELSE command_seq FI   {;}
        | WHILE exp DO command_seq END {;}
;

exp: NUMBER {;}
        | IDENTIFIER    {;}
        | exp '<' exp   {;}
        | exp '=' exp   {;}
        | exp '>' exp   {;}
        | exp '+' exp   {;}
        | exp '-' exp   {;}
        | exp '*' exp   {;}
        | exp '/' exp   {;}
        | exp '^' exp   {;}
        | '(' exp ')'   {;}
;

%%
main () 
{
	yyparse ();
}
yyerror (s) /* Called by yyparse on error */
	char *s;
{
	printf ("Problema com a analise sintatica!\n", s);
    printf ("%s\n", s);
}


