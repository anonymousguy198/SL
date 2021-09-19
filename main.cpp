#include "SL/VM/Runner/Runner.h"
#include <chrono>
#include <fstream>

using namespace std;

int main(/*int argc,char* argv[]*/) {
    std::string codeString;/*
    std::ifstream file(argv[1]);
    if(!file.is_open()){
        cerr << "File can't be open" << endl;
        exit(-1);
    }
    std::string line;
    while(getline(file,line)){
        codeString += '\n' + line;
    }
    cout << codeString << endl;*/

    auto start = chrono::high_resolution_clock::now();
    auto test = SL::Runner{SL::CodeGenerator{SL::Parser{SL::Lexer{codeString}}}};
    auto end = chrono::high_resolution_clock::now();
    auto diff = end-start;
    cout << endl << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    return 0;
}
