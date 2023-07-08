#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>

void tokenize(std::vector<std::string>&, std::string&);
std::string TraverseExp(std::unordered_map<std::string, int>&, std::string&);
void _traverse( 
    std::string&,
    std::unordered_map<std::string, int>&, 
    std::vector<std::string>::iterator&);
std::string programheader();
std::string exitprogram(std::unordered_map<std::string, int>&);
std::string assignvar(std::unordered_map<std::string, int>&, std::string);
std::string writecall();
std::string readcall(std::unordered_map<std::string, int>&, std::string&);
std::string pushvar(std::unordered_map<std::string, int>& , std::string& );
std::string getvar(std::unordered_map<std::string, int>&, std::string& );
std::string loadargs();
std::string pushimm(std::string&);
std::string getimm(std::string&);
std::string pushstack();
std::string storetop();
std::string gettop();
std::string pop(int);