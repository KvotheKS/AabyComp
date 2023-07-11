#include <iostream>
#include <fstream>
#include "sintatico.hh"

extern void scan_begin(int argc, char** argv);
extern void scan_end ();
extern int semanticErrors;
extern int syntaticError;
extern std::string _f_out;

int main (int argc, char** argv) {

    /* skip over program name */
    ++argv;
    --argc;
    scan_begin(argc, argv);
	yy::parser parse;
    parse();
    if (semanticErrors == 0) {
        std::cout << "Programa semanticamente correto\n";
    } else {
        std::cout << "Programa semanticamente incorreto\n";
    }
    if(!semanticErrors && !syntaticError)
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
