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

struct Name: Identifier {};

struct Value: State {};

struct IntegerLiteral: Value {
     string integer;
     int setState(char c) {
         integer += c;
     }
};

struct FloatLiteral: Value {
      string f;
      int setState(char c) {
          f+= c;
      }
};

struct DoubleLiteral: Value {
      string d;
      int setState(char c) {
          d += c;
      }
};

struct StringLiteral: Value {
      string s;
      int setState(char c) {
          s += c;
      }
};


struct Condition: State {
      Value value1;
      Relation r;
      Value value2;
};

struct Declaration: State {
      Keyword keyword;
      Identifier identifier;
}

struct StructBlock: State {
      vector<Declaration> declarations;
};

struct Struct: State {
    Keyword keyword;
    Identifier identifier;
    vector<Identifier> args;
    StructBlock block;
};

struct Block: State {
    vector<Declaration> declarations;
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

struct FunctionCall: State {
    Name name;
    vector<Value> args;
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

     int take(char c) {
         
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
	context.take(c);
	cout << c;
    }
    return 0;
}
