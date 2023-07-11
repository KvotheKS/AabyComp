#include "pcodegen.h"
#include <sstream>
#include <map>

std::map<char, std::string> operation_table{
    {'+', "add"},
    {'-', "sub"},
    {'*', "mul"},
    {'/', "div"},
    {'>', "slt"}, 
    {'=', "slt"}, 
    {'<', "slt"}
};

void tokenize(std::vector<std::string>& tokvec, std::string& expr)
{
    int j = 0;
    std::stringstream ss(expr);
    
    std::string temp;
    while(!ss.eof())
    {
        ss >> temp;
        tokvec.push_back(temp);
    }
    tokvec.resize(tokvec.size()-1);
}

std::string pop(int num = 1)
{
    return "\taddi sp, sp," + std::to_string(num*4) + "\n";
}

std::string gettop()
{
    return "\tlw t0, 0(sp)\n";
}

std::string storetop()
{
    return "\tsw t0, 0(sp)\n";
}

std::string pushstack()
{
    return "\taddi sp, sp, -4\n\tsw t0, 0(sp)\n";
}

std::string getimm(std::string& num)
{
    // int base = std::stoi(num);
    // std::string upper = std::to_string(base >> 12);
    // std::string lower = std::to_string((base << 20) >> 20); 
    // return "\tlui t0," + upper + "\n\taddi t0, t0, " + lower + "\n"; 
    return "\taddi t0, zero, " + num + "\n";
}

std::string pushimm(std::string& num)
{
    // std::cout << "IMM: " << num << std::endl;
    return getimm(num) + pushstack();
}

std::string strreplace(std::string str1, std::string str2, std::string str3)
{
    int i;
    while((i = str1.find(str2)) != std::string::npos) str1.replace(i,str3.size(), str3);
    return str1;
}

std::string loadargs()
{
    return "\tlw t0, 4(sp)\n\tlw t1, 0(sp)\n";
}

// std::string getvar(std::unordered_map<std::string, Symbol>& symTable, std::string& var)
// {
//     std::string temp = std::to_string((symTable[var].order)*4);
//     // std::cout << temp << " TEEEMP\n";
//     return  "\tlw t0, " + temp+ "(s11)\n";
// }

// std::string pushvar(std::unordered_map<std::string, Symbol>& symTable, std::string& var)
// {
//     return getvar(symTable,var) + pushstack();
// }

// Deposita o valor de t0 no endereço de memória da variável.
std::string assignvar(std::unordered_map<std::string, Symbol>& symTable, std::string var)
{
    std::string code = "";
    std::string label = symTable[var].assemblyLabel;
    // Coloca o endereço da variável em t0.
    code = code + "\tla t1, " + label + "\n";
    code = code + "\tsw t0, 0(t1)\n";
    return code;
}

// Presume que o valor a ser escrito já está em t0.
std::string writecall()
{
    return "\tadd a0, t0, zero\n\taddi a7, zero, 1\n\tecall\n\taddi a0, zero, 10\n\taddi a7, zero, 11\n\tecall\n";
}

std::string readcall(std::unordered_map<std::string, Symbol>& symTable, std::string& var)
{
    std::string code = "\taddi a7, zero, 5\n\tecall\n";
    // Ecall recebe valor em a0.
    std::string label = symTable[var].assemblyLabel;
    // Coloca o endereço da variável em t0.
    code = code + "\tla t0, " + label + "\n";
    code = code + "\tsw a0, 0(t0)\n";
    return code;
}

// inline void _shldtraverse(
//     std::string& f_out, 
//     std::unordered_map<std::string, Symbol>& symTable, 
//     std::vector<std::string>::iterator& it
// )
// {
//     if(operation_table.find((*(++it))[0]) == operation_table.end())
//     {
//         // std::cout << *it << '\n';
//         if(symTable.find(*it) == symTable.end())
//             f_out += pushimm(*it);
//         else
//             f_out += pushvar(symTable, *it);
//     }
//     else
//     {
//         // std::cout << *it << '\n';
//         _traverse(f_out, symTable, it);
//     }
// }

// void _traverse(
//     std::string& f_out, 
//     std::unordered_map<std::string, Symbol>& symTable, 
//     std::vector<std::string>::iterator& it
// )
// {
//     char op = (*it)[0];
    
//     if(it->size() == 1 && operation_table.find(op) != operation_table.end())
//     {    
//         _shldtraverse(f_out, symTable, it);
//         _shldtraverse(f_out, symTable, it);

//         f_out += loadargs();
//         f_out += pop(1);
        
//         if(op == '>')
//             f_out += "\tsub t0, t0, t1\n\tslt t0, zero, t0\n";
//         else if(op == '=')
//             f_out += std::string("\tsub t0, t0, t1\n\tadd t1, zero, t0\n\t") + 
//             "slt t0, t1, zero\n\tslt t1, zero, t1\n\tadd t0, t0, t1\n\txori t0, t0, 1\n";
//         else
//             f_out += "\t" + operation_table[op] + " t0, t0, t1\n"; 
//     }
//     else if(symTable.find(*it) == symTable.end())
//         f_out += pushimm(*it);
    
//     else
//         f_out += pushvar(symTable, *it);
    
//     f_out += storetop();
// }

std::string programheader()
{
    return ".text\nmain:\n";
}

std::string exitprogram(std::unordered_map<std::string, Symbol>& symTable)
{
    // Ecall de parada.
    std::string code = "\taddi a0, zero, 0\n\taddi a7, zero, 10\n\tecall\n.data\n";

    // Só adicionamos variáveis em .data se elas foram alteradas pelo usuário.
    // Se uma variável não tiver sido alterada pelo usuário, seu valor terá sido calculado em tempo de compilação.
    // E, assim, teria sido substituída por imediatos.
    for (auto& it : symTable) {
        code += it.second.assemblyLabel + ": .word 0\n";
    }
    return code;
}

// std::string TraverseExp(
//     std::unordered_map<std::string, Symbol>& symTable, 
//     std::string& expr
// )
// {
//     std::vector<std::string> tokvec; 
//     tokenize(tokvec, expr);
//     std::vector<std::string>::iterator it = tokvec.begin();
//     std::string f_out = "";
//     _traverse(f_out,symTable,it);
//     return f_out;
// }


RegisterTracker::RegisterTracker () {
    Register newReg;
    newReg.name = "a0";
    registerVector.push_back(newReg);

    newReg.name = "a1";
    registerVector.push_back(newReg);

    newReg.name = "a2";
    registerVector.push_back(newReg);

    newReg.name = "a3";
    registerVector.push_back(newReg);

    newReg.name = "a4";
    registerVector.push_back(newReg);

    newReg.name = "a5";
    registerVector.push_back(newReg);

    newReg.name = "a6";
    registerVector.push_back(newReg);

    newReg.name = "a7";
    registerVector.push_back(newReg);

    newReg.name = "t2";
    registerVector.push_back(newReg);

    newReg.name = "t3";
    registerVector.push_back(newReg);

    newReg.name = "t4";
    registerVector.push_back(newReg);

    newReg.name = "t5";
    registerVector.push_back(newReg);

    newReg.name = "t6";
    registerVector.push_back(newReg);

}

void RegisterTracker::freeRegister (std::string name) {

    for (int i = 0; i < registerVector.size(); ++i) {
        if (name == registerVector[i].name) {
            registerVector[i].isBeingUsed = false;
            break;
        }
    }
}

std::string RegisterTracker::useRegister () {
    for (int i = 0; i < registerVector.size(); ++i) {
        if (registerVector[i].isBeingUsed == false) {
            registerVector[i].isBeingUsed = true;
            return registerVector[i].name;
        }
    }
    return "";
}

void RegisterTracker::freeAllRegisters () {
    for (int i = 0; i < registerVector.size(); ++i) {
        registerVector[i].isBeingUsed = false;
    }
}

Expression processExpressions (Expression& first, Expression &second, char op, RegisterTracker& registerTracker) {
// Agregamos o código gerado até agora.
    Expression returnExp;
    returnExp.code = first.code + second.code;

    if (first.knownInCompileTime && second.knownInCompileTime) {
        returnExp.value = calculateValue(first.value, second.value, op);
    } else {
        returnExp.knownInCompileTime = false;
        if (first.knownInCompileTime) {
            returnExp.code += "\tli t0, " + std::to_string(first.value) + "\n"; // Imediato em t0
        } else {
            switch (first.locationType) {
                case MEMORY:
                    returnExp.code += "\tla t0, " + first.location + "\n";
                    returnExp.code += "\tlw t0, 0(t0)\n"; // Variável em t0
                    break;
                case REGISTER:
                    returnExp.code += "\tadd t0, zero, " + first.location + "\n";
                    // Libera registrador.
                    registerTracker.freeRegister(first.location);
                    break;
                case STACK:
                    // Se a segunda expressão também estiver na stack, a primeira expressão
                    // Vai estar "acima" da segunda.
                    int stackOffset = second.locationType == STACK ? 4 : 0;
                    returnExp.code += "\tlw t0, " + std::to_string(stackOffset) + "(sp)\n";
                    break;
            }
        }

        if (second.knownInCompileTime) {
            returnExp.code += "\tli t1, " + std::to_string(second.value) + "\n"; // Imediato em t1
        } else {
            switch (second.locationType) {
                case MEMORY:
                    returnExp.code += "\tla t1, " + second.location + "\n";
                    returnExp.code += "\tlw t1, 0(t1)\n";
                    break;
                case REGISTER:
                    returnExp.code += "\tadd t1, zero, " + second.location + "\n";
                    // Libera registrador.
                    registerTracker.freeRegister(second.location);
                    break;
                case STACK:
                    // Segunda expressão sempre no topo da pilha.
                    returnExp.code += "\tlw t1, 0(sp)\n";
                    break;
            }
        }

        // Agora, t0 e t1 contém os valores para operação.
        // Calculando valor em RISC-V. Resultado em t0.
        returnExp.code += generateInstruction (op);

        // Liberamos a pilha, caso tenha sido usada.
        if (first.locationType == STACK) {
                returnExp.code += "\taddi sp, sp, 4\n";
        }
        if (second.locationType == STACK) {
                returnExp.code += "\taddi sp, sp, 4\n";
        }

        // Checamos se algum registrador está disponível para armazenar o resultado.
        std::string newLocation = registerTracker.useRegister();
        if (newLocation != "") {
                returnExp.location = newLocation;
                returnExp.locationType = REGISTER;
                returnExp.code += "\tadd " + newLocation + ", t0, zero\n";
        } else {
                // Não há, precisamos usar a pilha. E para isso, geramos mais código RISC-V.
                // A responsabilidade de liberar a pilha fica para a chamada mais acima.
                returnExp.locationType = STACK;
                returnExp.code += "\taddi sp, sp, -4\n\tsw t0, 0(sp)\n";
        }
    }
    return returnExp;
}

// Operandos são t0 e t1, resultado vai em t0.
std::string generateInstruction (char operation) {

    std::string result = "";
    switch (operation) {
        case '+':
            result = "\tadd t0, t0, t1\n";
            break;
        case '-':
            result = "\tsub t0, t0, t1\n";
            break;
        case '*':
            result = "\tmul t0, t0, t1\n";
            break;
        case '/':
            result = "\tdiv t0, t0, t1\n";
            break;
        case '<':
            result = "\tslt t0, t0, t1\n";
            break;
        case '>': // Só invertemos a ordem dos registradores no comando slt.
            result = "\tslt t0, t1, t0\n";
            break;
        case '=':
            result = "\tsub t0, t0, t1\n";
            result += "\tseqz t0, t0\n";
            break;
    }
    return result;
}

int calculateValue (int first, int second, char operation) {

    int result = 0;
    switch (operation) {
        case '+':
            result = first + second;
            break;
        case '-':
            result = first - second;
            break;
        case '*':
            result = first * second;
            break;
        case '/':
            result = first / second;
            break;
        case '<':
            result = first < second;
            break;
        case '>':
            result = first > second;
            break;
        case '=':
            result = first == second;
            break;
    }
    return result;
}
