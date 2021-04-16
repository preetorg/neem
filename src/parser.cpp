#include "parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

struct Context {

    int take(char c) {
      
    }
};

struct Keyword: State {
    int i = 0;
    int setState(char c) {
        for(string keyword: keywords) {
           if(keyword[i] != c)
             i++;
	}
    }
};

struct Seperator: State {
   
    int setState(char c) {
 
    }
};

struct Identifier: State {

};

struct IntegerLiteral: State {

};

struct FloatLiteral: State {

};

struct DoubleLiteral: State {

};

struct StringLiteral: State {

};

struct Condition: State {

};

struct Block: State {

};

struct Struct: State {
    Keyword keyword;
    Identifier identifier;
    vector<Identifier> args;
    Block block;
};

struct If: State{
    Keyword keyword;
    Condition condition;
    Block block;
};

struct ElseIf: State {
    Keyword keyword;
    Condition condition;
    Block block;
};

struct Else: State {
    Keyword keyword;
    Condition condition;
    Block block;
};

struct While: State {
    Keyword keyword;
    Condition condition;
    Block block;
};

struct Function: State {
    Identifier type;
    Identifier name;
    vector<Identifier> args;
    Block block;
};

struct Use: State {
    Keyword keyword;
    Identifier identifier;
};

int parse(char* sourcefilename) {
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
