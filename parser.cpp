#include <iostream>
#include <fstream>
#include "sintatico.hh"

extern void scan_begin(int argc, char** argv);
extern void scan_end ();
extern int errors;
extern std::vector<CompileError> compileErrors;
extern std::string _f_out;

int main (int argc, char** argv) {

    /* skip over program name */
    ++argv;
    --argc;
    scan_begin(argc, argv);
	yy::parser parse;
    parse();
    if (errors == 0) {
        std::cout << "Programa correto\n";
    } else {
        if (argc > 0) {
            std::ifstream file;
            file.open(argv[0]);
            int lineCount = 1;
            int i = 0;
            while (!file.eof()) {
                std::string buffer;
                std::getline(file, buffer);
                while (i < compileErrors. size() && lineCount == compileErrors[i].lineNum) {
                    std::cout << compileErrors[i].msg << "> " << buffer << std::endl;
                    i++;
                }
                lineCount++;
            }
            file.close();
        }
        std::cout << "Programa incorreto\n";
    }
    if(!errors)
    {
        if(argc >= 2)
        {
            std::ofstream out_file(argv[1]);
            out_file << _f_out;
        }
        else
            std::cout << _f_out;
        
    }
}
