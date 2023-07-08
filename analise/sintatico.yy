%language "c++"
%require "3.7.4"
%header

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
        #include <iostream>
        #include <memory>
        #include <unordered_map>
        #include <fstream>
        #include "sintatico.hh"
        #include "pcodegen.h"
}


%code {
        # define YY_DECL \
        yy::parser::symbol_type yylex ()
        
        YY_DECL;
        std::unordered_map<std::string,int> symTable;
        int semanticErrors = 0;
        int syntaticError = 0;
        int branchcount = 0;
        std::string currentChain = "0";
        //std::ofstream _file("o.txt");
        std::string _f_out;
        extern std::string __immediate;
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
%token ELIF
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

%type<std::string> exp fst_exp sec_exp thr_exp command command_seq if_loop

%%


program: LET declarations IN command_seq END { 
        _f_out = programheader() + $4 + exitprogram(symTable); 
}
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
                        symTable.emplace(name,symTable.size());
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
                                symTable.emplace(name,symTable.size());
                        }
                }
;

command_seq: {$$ = "";}
        | command_seq command ';' {$$ = $1 + $2;}
;

command: SKIP {$$ = "";}
        | READ IDENTIFIER   {
                std::string name = $2;
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
                if(!semanticErrors)
                        $$ = readcall(symTable, $2) + pushstack();
        }
        | WRITE exp {
                if(!semanticErrors)
                {
                        $$ = TraverseExp(symTable, $2)  + writecall();
                }
        }
        | IDENTIFIER ASSGNOP exp    {
                std::string name = $1;
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
                if(!semanticErrors)
                {
                        $$ = TraverseExp(symTable, $3); 
                        $$ += assignvar(symTable, $1) + pop(1);
                }
        }
        | IF exp THEN command_seq if_loop FI   {
                std::string if_cmd;
                if(!semanticErrors)
                {
                        std::string branchnum = std::to_string(branchcount++);
                        if_cmd = TraverseExp(symTable, $2) + pop(1) +
                        "\tbeq t0, zero, ifout" + branchnum + '\n';
                        
                        if_cmd += $4 + "\tjal zero, ifchainout" + currentChain + "\nifout" + 
                                  branchnum + ":\n" + $5 + "ifchainout" + currentChain + ":\n";
                }
                currentChain = std::to_string(branchcount);
                $$ = if_cmd;
        }

        | WHILE exp DO command_seq END {
                std::string while_cmd;
                if(!semanticErrors)
                {
                        std::string branchnum = std::to_string(branchcount++);
                        while_cmd = "whilecheck" + branchnum + ":\n";
                        while_cmd += TraverseExp(symTable, $2) + pop(1) + 
                        "\tbeq t0, zero, whileout" + branchnum + "\n" + $4 +
                        "\tjal zero, whilecheck" + branchnum + "\nwhileout" + branchnum + ":\n";
                }

                $$ = while_cmd;
        }
;

if_loop: {$$ = "";}
        | ELIF exp THEN command_seq if_loop {
                std::string if_cmd;
                std::string branchnum = std::to_string(branchcount++);
                        
                if_cmd = TraverseExp(symTable, $2) + pop(1) +
                "\tbeq t0, zero, ifout" + branchnum + '\n';
                if_cmd += $4 + "\tjal zero, ifchainout" + currentChain + "\nifout" + 
                                branchnum + ":\n" + $5;
                $$ = if_cmd;
        }
        | ELSE command_seq { $$ = $2; }
;

exp:    fst_exp '<' fst_exp   {$$ = "< " + $1 + " " + $3 + " "; }
        | fst_exp '=' fst_exp   {$$ = "= " + $1 + " " + $3 + " "; }
        | fst_exp '>' fst_exp   {$$ = "> " + $1 + " " + $3 + " ";}
        | fst_exp {$$ = $1;}
;

fst_exp: sec_exp '+' fst_exp {$$ = "+ " + $1 + " " + $3 + " ";}
        | sec_exp '-' fst_exp {$$ = "- " + $1 + " " + $3 + " ";}
        | sec_exp {$$ = $1;}
;

sec_exp: thr_exp '*' sec_exp   {$$ = "* " + $1 + " " + $3 + " ";}
        | thr_exp '/' sec_exp   {$$ = "/ " + $1 + " " + $3 + " ";}
        | thr_exp {$$ = $1;}
;

thr_exp: IDENTIFIER    {
                std::string name = $1;
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
                $$ = $1;
        }
        | NUMBER { $$ = __immediate; } 
        | '(' exp ')' {$$ = $2;}
;

%%



void yy::parser::error (const std::string& m) /* Called by yyparse on error */
{
        syntaticError++;
	std::cerr << m << '\n';
}