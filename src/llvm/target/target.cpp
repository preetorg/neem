#include <string>
#include <iostream>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TargetMachine.h"
#include "llvm/Support/TargetOptions.h"

using namespace std;

int emitTarget(Module TheModule) {
    auto TargetTriple = sys::getDefaultTargetTriple();
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMcs();
    InitializeAllAsmParsers();
    InitializaAllAsmPrinters();

    string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);
    if(!Target) {
      cout << Error;
      return 1;
    }

    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTripe,CPU,Features,opt,RM);

    TheModule->setDataLayout(TargetMachine->createDataLayout());
    TheModule->setTargetTriple(TargetTriple);

    auto filename = "output.o"
    std::error_code EC;
    raw_fd_ostream dest(filename,EC,sys::fs::OF_None);
    if(EC) {
        cout << "Error";
    }

    legacy::PassManager pass;
    auto FileType = CGFT_ObjectFile;

    if(TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        cout << "Error";
    }

    pass.runFile(*TheModule);
    dest.flush();
	    
}
