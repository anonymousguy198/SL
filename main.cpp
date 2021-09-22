#include "SL/VM/Runner/Runner.h"
#include <chrono>
#include <fstream>

using namespace std;

void run(const string&);

std::ostream *SL::Var::output = &cout;
std::istream *SL::Var::input = &cin;

int main(int argc,char* argv[]) {
    string codeString;
    if(argc < 2){
        cout << "ERR: no input" << endl;
        return 1;
    }
    ifstream file{argv[1]};
    if(!file.is_open()){
        cout << "ERR: cannot open the file" << endl;
        return 1;
    }
    std::string line;
    while(getline(file,line)){
        codeString += line + '\n';
    }
    run(codeString);
    return 0;
}

void run(const string &codeString){
    try {
        double total = 0;
        auto start = chrono::high_resolution_clock::now();
        auto a = SL::Lexer{codeString};
        auto diff = chrono::high_resolution_clock::now() - start;
        total += chrono::duration<double, milli>(diff).count();
        *SL::Var::output << "Lexer:\t\t\t" << chrono::duration<double, milli>(diff).count() << "ms" << endl;
        start = chrono::high_resolution_clock::now();
        auto b = SL::Parser{a};
        diff = chrono::high_resolution_clock::now() - start;
        total += chrono::duration<double, milli>(diff).count();
        *SL::Var::output << "Parser:\t\t\t" << chrono::duration<double, milli>(diff).count() << "ms" << endl;
        start = chrono::high_resolution_clock::now();
        auto c = SL::CodeGenerator{b};
        diff = chrono::high_resolution_clock::now() - start;
        total += chrono::duration<double, milli>(diff).count();
        *SL::Var::output << "CodeGenerator:\t" << chrono::duration<double, milli>(diff).count() << "ms" << endl;
        *SL::Var::output << "------------Program Begin------------" << endl;
        start = chrono::high_resolution_clock::now();
        auto d = SL::Runner{c};
        diff = chrono::high_resolution_clock::now() - start;
        total += chrono::duration<double, milli>(diff).count();
        *SL::Var::output << "\n------------Program End------------" << endl;
        *SL::Var::output << "Runner:\t\t\t" << chrono::duration<double, milli>(diff).count() << "ms" << endl;
        *SL::Var::output << "Total:\t\t\t" << total << "ms" << endl;
    }catch (const std::exception &e){
        *SL::Var::output << e.what();
    }
}
