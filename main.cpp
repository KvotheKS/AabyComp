#include "./util/args.h"

int main(int argc, char** argv)
{
    argc--; argv++;

    terminalArgs unpacker;
    
    unpacker.InitArgs(
        {
            {"file", terminalType::STRING},
            {"help", terminalType::BOOL}
        }
    );

    unpacker.UnpackArgs(argc, argv);

    std::string file;
    unpacker.GetVar("file", file);

    bool h;
    unpacker.GetVar("help", h);

    if(h)
    {
        std::cout << "Para usar o programa, basta rodar \"aaby --file <input_file>\"";
        return;
    }

    
}