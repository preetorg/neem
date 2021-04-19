#include "parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

fstream source;

string keywords[] = {"package", "use", "struct", "end", "if", "else", "while", "var", "let", "const", "operator"};
string seperators[] = {" ", "\n"};
string relationaloperators[] = {"&&", "||", "<", ">","<=",">=","!", "!=", "=="};
char mathoperators[] = {'+', '-', '/','*', '^', '%'};

struct State {
    int is(Context context,string buffer) {

    }
};


struct Keyword: State {
    int is(Context context, string buffer) {
        int i = 0;
        for(string keyword: keywords) {                
            if(keyword == buffer)
                return i;
            i = i + 1;
        }
    }
};

struct Seperator: State {
   
    int is(Context context, string buffer) {
        int i = 0;
        for(string sep: seperators) {
            if(buffer == sep)
                return i;
            i = i + 1;
        }
    }
};

struct RelationOperator: State {

};

struct Identifier: State {
    int i = 0;
    string s;
    int is(Context state, string buffer) {
        if(i == 0 && ( buffer == "_" || isdigit(buffer.c_str()) ) )
            return 0;       
        s += buffer;		
    }
};

struct Name: Identifier {};

struct Value: State {};

struct IntegerLiteral: Value {
     string integer;
     int is(Context state, string buffer) {
         integer += buffer;
     }
};

struct FloatLiteral: Value {
      string f;
      int is(Context state,string buffer) {
          f+= buffer;
      }
};

struct DoubleLiteral: Value {
      string d;
      int is(Context state, string buffer) {
          d += buffer;
      }
};

struct StringLiteral: Value {
      string s;
      int is(Context state, string buffer) {
          s += buffer;
      }
};


struct Condition: State {
      Value value1;
      RelationOperator r;
      Value value2;

      int is(Context state, string buffer) {
          state.setState(new Value);
          state.setState(new RelationOperator);
          state.setState(new Value);
      }
};

struct Declaration: State {
      Keyword keyword;
      Identifier identifier;

      int is(Context state, string buffer) {
          state.setState(new Keyword);
          state.setState(new Identifier);
      }
};

struct StructBlock: State {
      vector<Declaration> declarations;
      int is(Context state, string buffer) {
          while(state.not(new Keyword)) {
              state.setState(new Declaration);
          }
      }
};

struct Struct: State {
    Keyword keyword;
    Identifier identifier;
    StructBlock block;
    int is(Context state, string buffer) {
        state.setState(new Keyword);
        state.setState(new Identifier);
        state.setState(new StructBlock);
    }
};

struct Block: State {
    vector<Declaration> declarations;
    int is(Context state, string buffer) {
        state.setState(new Declaration);
    }
};

struct If: Block{
    Keyword keyword;
    Condition condition;
    int is(Context state, string buffer) {
        state.setState(new Keyword);
        state.setState(new Condition);
    }
};

struct ElseIf: Block {
    Keyword keyword;
    Condition condition;
    int is(Context state, string buffer) {
        state.setState(new Keyword);
        state.setState(new Conditon);
    }
};

struct Else: Block {
    Keyword keyword;
    Condition condition;
};

struct While: Block {
    Keyword keyword;
    Condition condition;
    int is(Context state, string buffer) {
        state.setState(new Keyword);
        state.setState(new Condition);
    }
};

struct FunctionArgs: State {
    vector<Identifier> functionArgs;
    int is(Context state, string buffer) {
        while(state.not(new Seperator)) {
            functionArgs.push_back(state.setState(new Identifier));
        }
    }
};


struct Function: Block {
    Identifier type;
    Identifier name;
    FunctionArgs args;
    int is(Context state, string buffer) {
        state.setState(new Identifier);
        state.setState(new Identifier);
        state.setState(new FunctionArgs);
    }
};

struct FunctionCall: State {
    Name name;
    vector<Value> args;

    
    int is(Context state, string buffer) {
        state.setState(new Name);
        while(state.not(new Seperator))
            args.push_back(state.setState(new Value));
    }
};

struct Package: State {
    Keyword keyword;
    Identifier name;
    Module codegen() {
        
    }
    int is(Context state, string buffer) {
        state.setState(new Keyword);
        state.setState(new Identifier);
    }
};


struct Use: State {
    Keyword keyword;
    Identifier identifier;

    int is(Context state, string buffer) {
        state.setState(new Keyword);
        state.setState(new Identifier);
    }
};

struct Context {
     State state;
     string buffer; 
   
     State setState(State* state) {
         this->state = *state;
     }

     int take(char c) {
         buffer += c;
         state.is(this,buffer);
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
