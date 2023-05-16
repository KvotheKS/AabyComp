%{
#include <stdio.h>
#define YYDEBUG 1
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


program: LET declarations IN command_seq END { printf("Programa correto\n"); }
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
main (int argc, char** argv) 
{
        yydebug = 0;
        extern FILE *yyin;
        /* skip over program name */
        ++argv;
        --argc;
        if ( argc > 0 )
                yyin = fopen( argv[0], "r" );
        else
                yyin = stdin;

	yyparse ();
}
yyerror (s) /* Called by yyparse on error */
	char *s;
{
	printf ("Problema com a analise sintatica!\n", s);
}


