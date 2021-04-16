#include "parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

fstream source;

string keywords[] = {"package", "use", "struct", "end", "if", "else", "while"};
string seperators[] = {" ", "\n"};

struct State {
    int setState(char c) {

    }
};

struct Context {
    vector<State> tokens;

    int take(char c) {

    }
};

struct Keyword: State {
    int setState(char c) {

    }
};

struct Seperator: State {
    int setState(char c) {

    }
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
