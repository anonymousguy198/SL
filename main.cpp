#include "SL/VM/Runner/Runner.h"
#include <chrono>
//#include <fstream>

using namespace std;

int main(/*int argc,char* argv[]*/) {///todo implement print command and string better
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

    //codeString = "print 3*15+2000/3";

    auto start = chrono::high_resolution_clock::now();
    auto a = SL::Lexer{"print 1 + 2 * 3;"};
    auto diff = chrono::high_resolution_clock::now()-start;
    cout << endl << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    start = chrono::high_resolution_clock::now();
    auto b = SL::Parser{a};
    diff = chrono::high_resolution_clock::now()-start;
    cout << endl << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    start = chrono::high_resolution_clock::now();
    auto c = SL::CodeGenerator{b};
    diff = chrono::high_resolution_clock::now()-start;
    cout << endl << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    start = chrono::high_resolution_clock::now();
    auto d = SL::Runner{c};
    diff = chrono::high_resolution_clock::now()-start;
    cout << endl << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    return 0;
}
