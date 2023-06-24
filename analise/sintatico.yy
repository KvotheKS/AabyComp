%language "c++"
%require "3.7.4"
%header

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
        #include <iostream>
        #include <unordered_map>
        #include "sintatico.hh"
}


%code {
        # define YY_DECL \
        yy::parser::symbol_type yylex ()
        YY_DECL;
        std::unordered_map<std::string,int> symTable;
        int semanticErrors = 0;
}

/* %define parse.trace */
/* %define parse.error detailed */
/* %define parse.lac full */

%start program

%define api.token.prefix {TOK_}
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
%token <std::string> IDENTIFIER

%left '<' '>' '='
%left '-' '+'
%left '*' '/'
%right '^'

%%


program: LET declarations IN command_seq END { std::cout << "Programa sintaticamente correto\n"; }
;

declarations: /*empty*/
        | INTEGER id_seq IDENTIFIER '.' {
                std::string name = $3;
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer != symTable.end()) {
                        // Variável já declarada, erro.
                        std::cout << "Variable with same name already declared: " << name << "\n";
                        semanticErrors++;
                } else {
                        std::cout << "New variable: " << name << "\n";
                        symTable.emplace(name,0);
                }
        }
;

id_seq: /* empty */
        | id_seq IDENTIFIER ',' {
                        std::string name = $2;
                        std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                        if (tracer != symTable.end()) {
                                // Variável já declarada, erro.
                                std::cout << "Variable with same name already declared: " << name << "\n";
                                semanticErrors++;
                        } else {
                                std::cout << "New variable: " << name << "\n";
                                symTable.emplace(name,0);
                        }
                }
;

command_seq: /* empty */
        | command_seq command ';' {;}
;

command: SKIP
        | READ IDENTIFIER   {
                std::string name = $2;
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
        }
        | WRITE exp {;}
        | IDENTIFIER ASSGNOP exp    {
                std::string name = $1;
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
        }
        | IF exp THEN command_seq ELSE command_seq FI   {;}
        | WHILE exp DO command_seq END {;}
;

exp: NUMBER {;}
        | IDENTIFIER    {
                std::string name = $1;
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
        }
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

void yy::parser::error (const std::string& m) /* Called by yyparse on error */
{
	std::cerr << m << '\n';
}


