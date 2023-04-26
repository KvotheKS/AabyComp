#pragma once

#include <iostream>
#include <map>
#include <initializer_list>
#include <any>
#include <string>
#include <vector>
#include <regex>

enum terminalType
{
    INT, LONG, FLOAT, DOUBLE, STRING, BOOL
};

struct terminalArgs
{
public:
    std::map<std::string, terminalType> terminal_names;
    std::map<std::string, std::any> var_table;
    static std::string arg_rep;
    static std::regex arg_re;
public:
    terminalArgs(const std::initializer_list<std::pair<std::string, terminalType>>& = {});

    void InitArgs(const std::initializer_list<std::pair<std::string, terminalType>>&);
    void UnpackArgs(int, char**);
    bool PrepArg(const std::string&, const std::string&);
    void Failure(const std::string&);

    void GetVar(const std::string& name, int& var);
    void GetVar(const std::string& name, long long& var);
    void GetVar(const std::string& name, float& var);
    void GetVar(const std::string& name, double& var);
    void GetVar(const std::string& name, std::string& var);
    void GetVar(const std::string& name, bool& var);
};
