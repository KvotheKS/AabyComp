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
    std::cout << "IMM: " << num << std::endl;
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

std::string getvar(std::unordered_map<std::string, int>& symTable, std::string& var)
{
    std::string temp = std::to_string((symTable[var])*4);
    // std::cout << temp << " TEEEMP\n";
    return  "\tlw t0, " + temp+ "(s11)\n";
}

std::string pushvar(std::unordered_map<std::string, int>& symTable, std::string& var)
{
    return getvar(symTable,var) + pushstack();
}

std::string assignvar(std::unordered_map<std::string, int>& symTable, std::string var)
{
    std::string temp = std::to_string((symTable[var])*4);
    return  gettop() + "\tsw t0, " +  temp + "(s11)\n";
}

std::string writecall()
{
    return gettop()+ pop() + 
    "\tadd a0, t0, zero\n\taddi a7, zero, 1\n\tecall" + 
    "\n\taddi a0, zero, 10\n\taddi a7, zero, 11\n\tecall\n";
}

std::string readcall(std::unordered_map<std::string, int>& symTable, std::string& var)
{
    return "\taddi a7, zero, 5\n\tecall\n\tadd t0, zero, a0\n" + pushstack() + assignvar(symTable, var);
}

inline void _shldtraverse(
    std::string& f_out, 
    std::unordered_map<std::string, int>& symTable, 
    std::vector<std::string>::iterator& it
)
{
    if(operation_table.find((*(++it))[0]) == operation_table.end())
    {
        // std::cout << *it << '\n';
        if(symTable.find(*it) == symTable.end())
            f_out += pushimm(*it);
        else
            f_out += pushvar(symTable, *it);
    }
    else
    {
        // std::cout << *it << '\n';
        _traverse(f_out, symTable, it);
    }
}

void _traverse(
    std::string& f_out, 
    std::unordered_map<std::string, int>& symTable, 
    std::vector<std::string>::iterator& it
)
{
    char op = (*it)[0];
    
    if(it->size() == 1 && operation_table.find(op) != operation_table.end())
    {    
        _shldtraverse(f_out, symTable, it);
        _shldtraverse(f_out, symTable, it);

        f_out += loadargs();
        f_out += pop(1);
        
        if(op == '>')
            f_out += "\tsub t0, t0, t1\n\tslt t0, zero, t0\n";
        else if(op == '=')
            f_out += std::string("\tsub t0, t0, t1\n\tadd t1, zero, t0\n\t") + 
            "slt t0, t1, zero\n\tslt t1, zero, t1\n\tadd t0, t0, t1\n\txori t0, t0, 1\n";
        else
            f_out += "\t" + operation_table[op] + " t0, t0, t1\n"; 
    }
    else if(symTable.find(*it) == symTable.end())
        f_out += pushimm(*it);
    else
        f_out += pushvar(symTable, *it);
    
    f_out += storetop();
}

std::string programheader()
{
    return ".text\nmain:\n\tla s11, vars\n";
}

std::string exitprogram(std::unordered_map<std::string, int>& symTable)
{
    return std::string("\taddi a0, zero,0\n\taddi a7,zero, 10\n\tecall\n") +
            ".data\nvars:\n.space " + 
            std::to_string(symTable.size()*4) + '\n';
}

std::string TraverseExp(
    std::unordered_map<std::string, int>& symTable, 
    std::string& expr
)
{
    std::vector<std::string> tokvec; 
    tokenize(tokvec, expr);
    std::vector<std::string>::iterator it = tokvec.begin();
    std::string f_out = "";
    _traverse(f_out,symTable,it);
    return f_out;
}
