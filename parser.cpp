#include <iostream>
#include "sintatico.hh"

extern void scan_begin(int argc, char** argv);
extern void scan_end ();
extern int semanticErrors;

int main (int argc, char** argv) {

    /* skip over program name */
    ++argv;
    --argc;
    scan_begin(argc, argv);
	yy::parser parse;
    parse ();
    if (semanticErrors == 0) {
        std::cout << "Programa semanticamente correto\n";
    } else {
        std::cout << "Programa semanticamente incorreto\n";
    }
}
