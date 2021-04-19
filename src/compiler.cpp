#include "parser.h"

#include <string>
#include "llvm/IR/Module.h"
#include "llvm/ir/llvmir.h"

using namespace std;
using namespace llvm;
int compile(string sourcefilename) {
    Module mod = readFile(sourcefilename);
    runcodegen(mod);
}
