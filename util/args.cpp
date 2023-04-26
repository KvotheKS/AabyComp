#include "args.h"

std::string terminalArgs::arg_rep("--[a-zA-Z]+");
std::regex terminalArgs::arg_re(terminalArgs::arg_rep);

terminalArgs::terminalArgs(
    const std::initializer_list<std::pair<std::string, terminalType>>& init_list
)
{
    InitArgs(init_list);
}

void terminalArgs::InitArgs(
    const std::initializer_list<std::pair<std::string, terminalType>>& init_list
)
{
    for(auto& it : init_list)
        terminal_names.insert({it.first, it.second});
}

void terminalArgs::UnpackArgs(int argc, char** argv)
{
    for(int i = 0; i < argc, i+=2)
    {
        std::string arg(argv[i]);
        
        if(std::regex_match(arg_re, arg))
            Failure(std::string("Arg doesnt match the regex ") + arg_rep);
        
        arg = arg.substring(2);
        
        if(terminal_names.find(arg) == terminal_names.end())
            Failure(std::string("Arg name was not declared"));

        if(terminal_names[arg] == terminalType::BOOL)
        {
            
            i--;
        }

        else if(!PrepArg(argv[i+1]))
            Failure(std::string("Arg value doesnt match its type")); 
    }
}

bool terminalArgs::PrepArg(
    const std::string& var_name, 
    const std::string& arg_val
)
{
    switch(terminal_names[var_name])
    {
        case INT: var_table[var_name] = std::stoi(arg_val);
        break;
        case LONG: var_table[var_name] = std::stol(arg_val);
        break;
        case FLOAT: var_table[var_name] = std::stof(arg_val);
        break;
        case DOUBLE: var_table[var_name] = std::stod(arg_val);
        break;
        case STRING: var_table[var_name] = arg_val;
        break;
    }
}

void terminalArgs::Failure(const std::string& err_msg)
{
    std::cerr << err_msg;
    exit(EXIT_FAILURE); 
}

void terminalArgs::GetVar(const std::string& name, int& var)
{ 
    if(var_table.find(name) == var_table.end())
        Failure("Argument name not expected");
    var = std::any_cast<int>(var_table[name]); 
}

void terminalArgs::GetVar(const std::string& name, float& var)
{ 
    if(var_table.find(name) == var_table.end())
        Failure("Argument name not expected");
    var = std::any_cast<float>(var_table[name]); 
}

void terminalArgs::GetVar(const std::string& name, long long& var)
{ 
    if(var_table.find(name) == var_table.end())
        Failure("Argument name not expected");
    var = std::any_cast<long long>(var_table[name]); 
}

void terminalArgs::GetVar(const std::string& name, double& var)
{ 
    if(var_table.find(name) == var_table.end())
        Failure("Argument name not expected");
    var = std::any_cast<double>(var_table[name]); 
}

void terminalArgs::GetVar(const std::string& name, std::string& var)
{ 
    if(var_table.find(name) == var_table.end())
        Failure("Argument name not expected");
    var = std::any_cast<std::string>(var_table[name]); 
}

void terminalArgs::GetVar(const std::string& name, bool& var)
{
    var = var_table.find(name) != var_table.end();
}