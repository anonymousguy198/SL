#include "SL/VM/Runner/Runner.h"
#include <chrono>
//#include <fstream>

using namespace std;

int main(/*int argc,char* argv[]*/) {
    //std::string codeString{};
    /*
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

    string codeString = "print 3*15+2000/3;";

    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    auto a = SL::Lexer{codeString};
    auto diff = chrono::high_resolution_clock::now()-start;
    total += chrono::duration<double,milli>(diff).count();
    cout << "Lexer: " << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    start = chrono::high_resolution_clock::now();
    auto b = SL::Parser{a};
    diff = chrono::high_resolution_clock::now()-start;
    total += chrono::duration<double,milli>(diff).count();
    cout << "Parser: " << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    start = chrono::high_resolution_clock::now();
    auto c = SL::CodeGenerator{b};
    diff = chrono::high_resolution_clock::now()-start;
    total += chrono::duration<double,milli>(diff).count();
    cout << "CodeGenerator: " << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    cout << "------------Program Begin------------" << endl;
    start = chrono::high_resolution_clock::now();
    auto d = SL::Runner{c};
    diff = chrono::high_resolution_clock::now()-start;
    total += chrono::duration<double,milli>(diff).count();
    cout << "\n------------Program End------------" << endl;
    cout << "Runner: " << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    cout << "Total: " << total << "ms" << endl;
    return 0;
}
