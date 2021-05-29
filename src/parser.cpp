#include "parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

fstream source;

string keywords[] = 
{"import", "export", "record", "end", "if", "else", 
"while", "var", "let", "const", 
"operator","null", "foreach"};

string seperators[] = {" ", "\n"};
string relationaloperators[] = {"&&", "||", "<", ">","<=",">=","!", "!=", "=="};
char mathoperators[] = {'+', '-', '/','*', '**', '%'};
char bitwiseoperators[] = {'&','|','^','~','>>','<<'};


struct State {
    string buffer;
    int take(char c) {
        buffer = buffer + c;
    }
};

struct Keyword: State {
    int take(char c) {
        int i = 0;
        State::take(c);
        for(string keyword: keywords) {                
            if(keyword == buffer)
                return i;
            i = i + 1;
        }
    }
};

struct Seperator: State {
   
    int take(char c) {
        int i = 0;
        State::take(c);
        for(string sep: seperators) {
            if(buffer == sep)
                return i;
            i = i + 1;
        }
    }
};

struct RelationOperator: State {
    int take(char c) {
        int i = 0;
        State::take(c);
        for(string op: relationaloperators) {
            if(buffer == op)
                return i;
            i = i + 1;
        }
    }
};

struct MathOperator: State {
    int take(char c) {
        int i = 0;
        State::take(c);
        for(;i<6;i++) {
            if(buffer[0] == mathoperators[i])
                return i;
        }
    }
};

struct BitwiseOperator: State {
    int take(char c) {
        int i = 0;
        State::take(c);
        for(;i<6;i++) {
            if(buffer[0] == bitwiseoperators[i])
                return i;
        }
    }
};

struct Identifier: State {
    int i = 0;
    int take(char c) {
        State::take(c);
        if(i == 0 && ( buffer == "_" || isdigit(buffer[0]) ) )
            return 0;       		
    }
};


struct Literal: State{
      int take(char c) {
          State::take(c);
      }
};

struct Context {
     Keyword keyword;
     Seperator seperator;
     int take(char c) {
         
        
     }
     
};




int readFile(string sourcefilename) {
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
