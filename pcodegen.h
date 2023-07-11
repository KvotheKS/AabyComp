#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>


// Representa um registrador RISC-V.
class Register {
 public:
    std::string name;
    bool isBeingUsed {false};
};

// Mantém um registro dos registradores sendo usados na hora de calcular expressões.
// Usamos todos os registradores t e a, exceto t0 e t1.
class RegisterTracker {

 public:
    RegisterTracker ();
    std::vector<Register> registerVector;
    void freeRegister (std::string name);
    std::string useRegister ();
    void freeAllRegisters ();
};

// Registro de variável mais aprimorado.
class Symbol {
 public:
    std::string name;
    int value {0};
    bool changedByUser {false};
    std::string assemblyLabel; // Nome da label que será usada na seção .data.
};

// Dirá se a expressão só contém imediatos ou contém variável.
enum LocationType {REGISTER, STACK, MEMORY};

// Representa uma expressão gerada por sintático.yy.
class Expression {
 public:
    int value {0};
    std::string code {""}; // Código gerado até agora para calcular a expressão.
    bool knownInCompileTime {true}; // Diz se a expressão pode ser calculada em tempo de compilação.
    std::string location {""}; // Local onde será armazenada. Pode ser num registrador, na pilha ou em .data.
    LocationType locationType {MEMORY};
};


// void tokenize(std::vector<std::string>&, std::string&);
// std::string TraverseExp(std::unordered_map<std::string, Symbol>&, std::string&);
// void _traverse( 
//     std::string&,
//     std::unordered_map<std::string, Symbol>&, 
//     std::vector<std::string>::iterator&);
std::string programheader();
std::string exitprogram(std::unordered_map<std::string, Symbol>&);
std::string assignvar(std::unordered_map<std::string, Symbol>&, std::string);
std::string writecall();
std::string readcall(std::unordered_map<std::string, Symbol>&, std::string&);
// std::string pushvar(std::unordered_map<std::string, Symbol>& , std::string& );
// std::string getvar(std::unordered_map<std::string, Symbol>&, std::string& );
std::string loadargs();
// std::string pushimm(std::string&);
// std::string getimm(std::string&);
// std::string pushstack();
// std::string storetop();
// std::string gettop();
// std::string pop(int);

Expression processExpressions (Expression& first, Expression& second, char operation, RegisterTracker& tracker);
std::string generateInstruction (char operation);
int calculateValue (int first, int second, char operation);