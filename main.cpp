#include "SL/VM/Runner/Runner.h"
#include <chrono>

using namespace std;

int main() {//todo implement bool
    std::string codeString = R"(
print 0.1+1;
)";
    auto start = chrono::high_resolution_clock::now();
    auto test = SL::Runner{SL::CodeGenerator{SL::Parser{SL::Lexer{codeString}}}};
    auto end = chrono::high_resolution_clock::now();
    auto diff = end-start;
    cout << endl << chrono::duration<double,milli>(diff).count() << "ms" << endl;
    return 0;
}
