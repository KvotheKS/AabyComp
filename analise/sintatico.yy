%language "c++"
%require "3.7.4"
%header

%define api.token.constructor
%define api.value.type variant
/* %define parse.assert */

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
        std::unordered_map<std::string, Symbol> symTable;
        int errors = 0;
        int variableCount = 0;
        int branchcount = 0;
        std::string currentChain = "0";
        //std::ofstream _file("o.txt");
        std::string _f_out;
        extern std::string __immediate;
        extern std::string __badToken;
        extern int yylineno;
        RegisterTracker registerTracker;
        std::vector<CompileError> compileErrors;
}

/* %define parse.trace
%define parse.error detailed
%define parse.lac full */

%start program

/* %union {
        Expression Expression;
        std::string string;
} */

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
%left error
/* %right '^' */

/* %type<std::string> exp fst_exp sec_exp thr_exp command command_seq if_loop */
%type <std::string> command command_seq if_loop
%type <Expression> exp

%%


program: LET declarations IN command_seq END { 
        _f_out = programheader() + $4 + exitprogram(symTable); 
}
;

declarations: /*empty*/
        | INTEGER id_seq IDENTIFIER '.' {
                std::string name = $3;
                std::unordered_map<std::string, Symbol>::iterator tracer = symTable.find(name);
                if (tracer != symTable.end()) {
                        // Variável já declarada, erro.
                        std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Variable with same name already declared: " + name + "\n";
                        CompileError newError(yylineno, errorMsg);
                        compileErrors.push_back(newError);
                        errors++;
                } else {
                        Symbol newVar;
                        newVar.name = name;
                        newVar.value = 0;
                        newVar.assemblyLabel = "VAR" + std::to_string(variableCount);
                        symTable.emplace(name, newVar);
                        variableCount++;
                }
        }
        | INTEGER id_seq error '.' {
                std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Bad variable name: " + __badToken + "\n";
                CompileError newError(yylineno, errorMsg);
                compileErrors.push_back(newError);
                errors++;
        }
;

id_seq: /* empty */
        | id_seq IDENTIFIER ',' {
                        std::string name = $2;
                        std::unordered_map<std::string,Symbol>::iterator tracer = symTable.find(name);
                        if (tracer != symTable.end()) {
                                // Variável já declarada, erro.
                                std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Variable with same name already declared: " + name + "\n";
                                CompileError newError(yylineno, errorMsg);
                                compileErrors.push_back(newError);
                                errors++;
                        } else {
                                Symbol newVar;
                                newVar.name = name;
                                newVar.value = 0;
                                newVar.assemblyLabel = "VAR" + std::to_string(variableCount);
                                symTable.emplace(name, newVar);
                                variableCount++;
                        }
                }
        | id_seq error ',' {
                std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Bad variable name: " + __badToken + "\n";
                CompileError newError(yylineno, errorMsg);
                compileErrors.push_back(newError);
                errors++;
        }
;

command_seq: {$$ = "";}
        | command_seq command {$$ = $1 + $2;}
;

command: SKIP ';' {$$ = "";}
        | READ IDENTIFIER ';'  {
                std::string name = $2;
                std::unordered_map<std::string,Symbol>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Variable not declared: " + name + "\n";
                        CompileError newError(yylineno, errorMsg);
                        compileErrors.push_back(newError);
                        errors++;
                }
                if(!errors) {
                        // $$ = readcall(symTable, $2) + pushstack(); // Por que pushstack() aqui?
                        $$ = readcall(symTable, $2);
                }
        }
        | WRITE exp ';' {
                if(!errors)
                {
                        std::string code = $2.code; // Código gerado no cálculo da expressão.
                        if ($2.knownInCompileTime) {
                                // Coloca imediato em t0.
                                code += "\tli t0, " + std::to_string($2.value) + "\n";
                        } else {
                                switch ($2.locationType) {
                                        case MEMORY:
                                                code += "\tla t0, " + $2.location + "\n";
                                                code += "\tlw t0, 0(t0)\n";
                                                break;
                                        case REGISTER:
                                                code += "\tadd t0, zero, " + $2.location + "\n";
                                                break;
                                        case STACK:
                                                code += "\tlw t0, 0(sp)\n";
                                                code += "\taddi sp, sp, 4\n"; // Não esquecendo de liberar a pilha.
                                                break;
                                }
                        }
                        code += writecall();
                        $$ = code;
                        registerTracker.freeAllRegisters();
                }
        }
        | IDENTIFIER ASSGNOP exp ';' {
                std::string name = $1;
                std::unordered_map<std::string,Symbol>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Variable not declared: " + name + "\n";
                        CompileError newError(yylineno, errorMsg);
                        compileErrors.push_back(newError);
                        errors++;
                }
                if(!errors)
                {
                        std::string code = $3.code;
                        if ($3.knownInCompileTime) {
                                code += "\tli t0, " + std::to_string($3.value) + "\n";
                        } else {
                                switch ($3.locationType) {
                                        case MEMORY:
                                                code += "\tla t0, " + $3.location + "\n";
                                                code += "\tlw t0, 0(t0)\n";
                                                break;
                                        case REGISTER:
                                                code += "\tadd t0, zero, " + $3.location + "\n";
                                                break;
                                        case STACK:
                                                code += "\tlw t0, 0(sp)\n";
                                                code += "\taddi sp, sp, 4\n"; // Não esquecendo de liberar a pilha.
                                                break;
                                }
                        }
                        code += assignvar(symTable, $1); // Armazena valor de t0 na variável.
                        $$ = code;
                }
                registerTracker.freeAllRegisters();
        }
        | IF exp THEN command_seq if_loop FI ';' {
                std::string if_cmd = "";
                if(!errors)
                {
                        std::string branchnum = std::to_string(branchcount++);
                        // Armazena s0 anterior em s1 por enquanto.
                        if_cmd += "\tadd s1, zero, s0\n";
                        std::string conditionCode = "";
                        if ($2.knownInCompileTime) {
                                conditionCode += "\tli s0, " + std::to_string($2.value) + "\n";
                        } else {
                                switch ($2.locationType) {
                                        case MEMORY:
                                                conditionCode += "\tla t0, " + $2.location + "\n";
                                                conditionCode += "\tlw s0, 0(t0)\n";
                                                break;
                                        case REGISTER:
                                                conditionCode += "\tadd s0, zero, " + $2.location + "\n";
                                                break;
                                        case STACK:
                                                conditionCode += "\tlw s0, 0(sp)\n";
                                                conditionCode += "\taddi sp, sp, 4\n"; // Não esquecendo de liberar a pilha.
                                                break;
                                }
                        }

                        // Teste de condição.
                        if_cmd += $2.code;
                        if_cmd += conditionCode;
                        // Armazena s0 anterior (que está em s1) na pilha.
                        if_cmd += "\taddi sp, sp, -4\n\tsw s1, 0(sp)\n";

                        if_cmd += "\tbeq s0, zero, ifout" + branchnum + '\n';
                        
                        if_cmd += $4 + "\tjal zero, ifchainout" + currentChain + "\nifout" + 
                                branchnum + ":\n" + $5 + "ifchainout" + currentChain + ":\n";
                        
                        // Retira s0 anterior da pilha.
                        if_cmd += "\tlw s0, 0(sp)\n\taddi sp, sp, 4\n";
                }
                currentChain = std::to_string(branchcount);
                $$ = if_cmd;
                registerTracker.freeAllRegisters();
        }
        | WHILE exp DO command_seq END ';' {
                std::string while_cmd = "";
                if(!errors)
                {
                        std::string branchnum = std::to_string(branchcount++);
                        // Armazena s0 anterior em s1 por enquanto.
                        while_cmd += "\tadd s1, zero, s0\n";
                        std::string conditionCode = "";
                        if ($2.knownInCompileTime) {
                                conditionCode += "\tli s0, " + std::to_string($2.value) + "\n";
                        } else {
                                switch ($2.locationType) {
                                        case MEMORY:
                                                conditionCode += "\tla t0, " + $2.location + "\n";
                                                conditionCode += "\tlw s0, 0(t0)\n";
                                                break;
                                        case REGISTER:
                                                conditionCode += "\tadd s0, zero, " + $2.location + "\n";
                                                break;
                                        case STACK:
                                                // s0 já foi colocado na pilha, então teremos que fazer um ajuste.
                                                conditionCode += "\tlw s0, 4(sp)\n";
                                                conditionCode += "\tsw s1, 4(sp)\n";
                                                conditionCode += "\taddi sp, sp, 4\n"; // Não esquecendo de liberar a pilha.
                                                break;
                                }
                        }

                        // Armazena s0 anterior (que está em s1) na pilha.
                        while_cmd += "\taddi sp, sp, -4\n\tsw s1, 0(sp)\n";

                        while_cmd += "whilecheck" + branchnum + ":\n";

                        // Colocamos o código gerado acima para mudar o valor de s0.
                        while_cmd += $2.code;
                        while_cmd += conditionCode;

                        while_cmd += "\tbeq s0, zero, whileout" + branchnum + "\n" + $4 +
                        "\tjal zero, whilecheck" + branchnum + "\nwhileout" + branchnum + ":\n";

                        // Retira s0 anterior da pilha.
                        while_cmd += "\tlw s0, 0(sp)\n\taddi sp, sp, 4\n";
                }
                $$ = while_cmd;
                registerTracker.freeAllRegisters();
        }
        | IDENTIFIER ASSGNOP error ';' {
                std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Bad expression\n";
                CompileError newError(yylineno, errorMsg);
                compileErrors.push_back(newError);
                errors++;
                yyclearin;
        }
        | error ';' {
                std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Couldn't recognize command\n";
                CompileError newError(yylineno, errorMsg);
                compileErrors.push_back(newError);
                errors++;
                yyclearin;
        }
;

if_loop: /* empty */ {$$ = "";}
        | ELIF exp THEN command_seq if_loop {
                std::string if_cmd = "";
                std::string branchnum = std::to_string(branchcount++);
                // Armazena s0 anterior em s1 por enquanto.
                if_cmd += "\tadd s1, zero, s0\n";
                std::string conditionCode = "";
                if ($2.knownInCompileTime) {
                        conditionCode += "\tli s0, " + std::to_string($2.value) + "\n";
                } else {
                        switch ($2.locationType) {
                                case MEMORY:
                                        conditionCode += "\tla t0, " + $2.location + "\n";
                                        conditionCode += "\tlw s0, 0(t0)\n";
                                        break;
                                case REGISTER:
                                        conditionCode += "\tadd s0, zero, " + $2.location + "\n";
                                        break;
                                case STACK:
                                        conditionCode += "\tlw s0, 0(sp)\n";
                                        conditionCode += "\taddi sp, sp, 4\n"; // Não esquecendo de liberar a pilha.
                                        break;
                        }
                }

                // Teste de condição.
                if_cmd += $2.code;
                if_cmd += conditionCode;
                // Armazena s0 anterior (que está em s1) na pilha.
                if_cmd += "\taddi sp, sp, -4\n\tsw s1, 0(sp)\n";
                        
                if_cmd += "\tbeq s0, zero, ifout" + branchnum + '\n';
                if_cmd += $4 + "\tjal zero, ifchainout" + currentChain + "\nifout" + 
                                branchnum + ":\n" + $5;

                // Retira s0 anterior da pilha.
                if_cmd += "\tlw s0, 0(sp)\n\taddi sp, sp, 4\n";
                
                $$ = if_cmd;
                registerTracker.freeAllRegisters();
        }
        | ELSE command_seq { $$ = $2; }
;

/* exp:    fst_exp '<' fst_exp   {$$ = "< " + $1 + " " + $3 + " "; }
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
                std::unordered_map<std::string,Symbol>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        errors++;
                }
                $$ = $1;
        }
        | NUMBER { $$ = __immediate; } 
        | '(' exp ')' {$$ = $2;}
; */

exp:    NUMBER {
                Expression imm;
                imm.value = std::stoi(__immediate);
                imm.knownInCompileTime = true;
                $$ = imm;
        }
        | IDENTIFIER {
                std::string name = $1;
                std::unordered_map<std::string,Symbol>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Variable not declared: " + name + "\n";
                        CompileError newError(yylineno, errorMsg);
                        compileErrors.push_back(newError);
                        errors++;
                } else {
                        $$.knownInCompileTime = false;
                        $$.location = tracer->second.assemblyLabel;
                        $$.locationType = MEMORY;
                }
        }
        // Se ambos os termos forem imediatos, podemos calcular o valor das expressões agora.
        | exp '<' exp   {$$ = processExpressions($1, $3, '<', registerTracker);}
        | exp '=' exp   {$$ = processExpressions($1, $3, '=', registerTracker);}
        | exp '>' exp   {$$ = processExpressions($1, $3, '>', registerTracker);}
        | exp '+' exp   {$$ = processExpressions($1, $3, '+', registerTracker);}
        | exp '-' exp   {$$ = processExpressions($1, $3, '-', registerTracker);}
        | exp '*' exp   {$$ = processExpressions($1, $3, '*', registerTracker);}
        | exp '/' exp   {$$ = processExpressions($1, $3, '/', registerTracker);}
        /* | exp '^' exp   {$$ = processExpressions($1, $3, $2, registerTracker);} */
        | '(' exp ')'   {$$ = $2;}
        | exp error exp {
                std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Unrecognized operation symbol: " + __badToken + "\n";
                CompileError newError(yylineno, errorMsg);
                compileErrors.push_back(newError);
                errors++;
                yyclearin;
        }
        | '(' error ')' {
                std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Bad expression\n";
                CompileError newError(yylineno, errorMsg);
                compileErrors.push_back(newError);
                errors++;
                yyclearin;
        }
;

%%

void yy::parser::error (const std::string& m) /* Called by yyparse on error */
{
        /* std::string errorMsg = "Error, line " + std::to_string(yylineno) + ": Fatal Syntax Error\n";
        CompileError newError(yylineno, errorMsg);
        compileErrors.push_back(newError); */
	std::cerr << m << '\n';
        errors++;
}