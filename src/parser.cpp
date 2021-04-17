#include "parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

fstream source;

string keywords[] = {"package", "use", "struct", "end", "if", "else", "while", "var", "let", "const"};
string seperators[] = {" ", "\n"};
string relationaloperators[] = {"&&", "||", "<", ">","<=",">=","!", "!=", "=="};
char mathoperators[] = {'+', '-', '/','*', '^', '%'};

struct State {
    vector<State> tokens;
    
    int setState(char c) {

    }
};

struct Keyword: State {
    int setState(string keyword) {
        
    }
};

struct Seperator: State {
   
    int setState(char c) {
    }
};

struct Identifier: State {
    int i = 0;
    string s;
    int setState(char c) {
        if(i == 0 && ( c == '_' || isdigit(c) ) )
            return 0;       
        s += c;		
    }
};

struct IntegerLiteral: State {
     string integer;
     int setState(char c) {
         integer += c;
     }
};

struct FloatLiteral: State {
      string f;
      int setState(char c) {
          f+= c;
      }
};

struct DoubleLiteral: State {
      string d;
      int setState(char c) {
          d += c;
      }
};

struct StringLiteral: State {
      string s;
      int setState(char c) {
          s += c;
      }
};

struct Condition: State {

};

struct StructBlock: State {
        
};

struct Struct: State {
    Keyword keyword;
    Identifier identifier;
    vector<Identifier> args;
    StructBlock block;
};

struct Block: State {

};

struct If: Block{
    Keyword keyword;
    Condition condition;
};

struct ElseIf: Block {
    Keyword keyword;
    Condition condition;
};

struct Else: Block {
    Keyword keyword;
    Condition condition;
};

struct While: Block {
    Keyword keyword;
    Condition condition;
};

struct FunctionArgs: State {
    vector<Identifier> functionArgs;
};


struct Function: Block {
    Identifier type;
    Identifier name;
    FunctionArgs args;
};

struct Package: State {
    Keyword keyword;
    Identifier name;
};


struct Use: State {
    Keyword keyword;
    Identifier identifier;
};

struct Context {
     
     Identifier parseIdentifier() {
         Identifier identifier;
	 return identifier;
     }
     
     Keyword parseKeyword(string s) {
         Keyword keyword;
	 return keyword;
     }

     Package parsePackage() {
         Package package;
	 package.keyword = parseKeyword(keywords[0]);
	 package.name = parseIdentifier();
     }

     Use parseUse() {
         Use use;
	 use.keyword = parseKeyword(keywords[1]);
	 use.identifier = parseIdentifier();
     }

     Struct parseStruct() {
          Struct s;
	  s.keyword = parseKeyword(keywords[2]);
	  s.identifier = parseIdentifier();
     }

     FunctionArgs parseFunctionArgs() {
          FunctionArgs functionArgs;
	  return functionArgs;
     }

     Function parseFunction() {
         Function function;
         function.type = parseIdentifier();
         function.name = parseIdentifier();
         function.args = parseFunctionArgs();
     }

     Condition parseCondition() {
         Condition condition;
     }

     If parseIf() {
         Keyword keyword;
	 Condition condition;
     }

     ElseIf parseElseIF() {
         Keyword keyword;
	 Condition condition;
     }

     Else parseElse() {
         Keyword keyword;
     }

     While parseWhile() {
         Keyword keyword;
	 Condition condition;
     }

     int parse() {
         return 0;
     }
};

int readFile(char* sourcefilename) {
    struct Context context;
    source.open(sourcefilename,ios::in);
    if(!source)
	printf("file not found");
    char c = 0;
    while(!source.eof()) {
        source.read(&c,1);
	context.parse();
	cout << c;
    }
    return 0;
}
