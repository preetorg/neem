#include "parser.h"

#include <string>
#include "llvm/IR/Module.h"


using namespace std;
using namespace llvm;
int compile(string sourcefilename) {
    Module TheModule = readFile(sourcefilename);
}
