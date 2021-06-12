#include "parser.h"
#include "ast.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

fstream source;

string keywords[] = 
{"import", "export", "record", "end", "if", "else", "def"
"while", "val", "let", "const", 
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
     Identifier identifier;
     RelationOperator relop;
     MathOperator mathop;
     BitwiseOperator bitwiseop;
     Literal literal;
     int next = 0;
     int index = -1;
     int issep = false;
     bool match = false;
     Ast ast;

     int parse_keyword() {
         if(index == 0) {
            ast.importStatement(keywords[index]);
            issep = true;
            next = 1;
        } else if(index == 1) {
            ast.exportStatement(keywords[index]);
            issep = true;
            next = 1;
        } else if(index == 2) {
            ast.recordStatement(keywords[index]);
            issep = true;
            next = 1;
        } else if(index == 3) {
            //ast.end(keywords[index]);
        } else if(index == 4) {
            ast.ifStatement(keywords[index]);
            next = 1;
        } else if(index == 5) {
            ast.elseStatement(keywords[index]);
            next = 1;
        } else if(index == 6) {
            //ast.ifElseStatement(keywords[index]);
            next = 1;
        } else if(index == 7) {
            ast.whileStatement(keywords[index]);
            next = 1;
        } else if(index == 8) {
            ast.object(keywords[index]);
            next = 1;
        } else if(index == 9) {
            ast.declaration(keywords[index]);
            next = 1;
        } else if(index == 10) {
            ast.constant(keywords[index]);
            next = 1;
        } else if(index == 11) {
            //ast.oper(keywords[index]);
        } else if(index == 12) {
            ast.null(keywords[index]);
        } else if(index == 13) {
            ast.forEachStatement(keywords[index]);
        }

     }
     
     int take(char c) {
        if(issep) {
          seperator.take(c);
          return;
        }
        if(next == 0)
          index = keyword.take(c);
        else if(next == 1)
          index = identifier.take(c);
        else if(next == 2)
          if(c == '=')
            return 1;
        else if(next == 3)
          index = relop.take(c);
        else if(next == 4)
          index = mathop.take(c);
        else if(next == 5)
          index = bitwiseop.take(c);

        if(index != -1) {
            if(next == 0) {
                parse_keyword();
            }
        }
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
