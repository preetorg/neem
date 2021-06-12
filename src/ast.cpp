#include <string>
#include <vector>
using namespace std;

enum AstType {
    Declaration, ImportStatement, ExportStatement, FunctionStatement, FunctionName,  FunctionArgs, IfStatement, 
    ElseStatement, ElseIfStatement, WhileStatement, ForEachStatement, Expression,
    RecordStatement, Assign, Math, Bitwise, Relational, Object, Constant, Record, Null
};

struct AstNode{
    enum AstType type;
    string match;
    string content;      
};

struct Ast{
    vector<AstNode> program;
    int insert(enum AstType type, string match, string content) {
        AstNode node;
        node.type = type;
        node.match = match;
        node.content = content;
        program.push_back(node);
    }

    int declaration(string content) {
        insert(AstType::Declaration,"Keyword",content);
    }

    int object(string content) {
        insert(AstType::Object, "Keyword", content);
    }

    int constant(string content) {
        insert(AstType::Constant, "Keyword", content);
    }

    int null(string content) {
        insert(AstType::Null, "keyword", content);
    }

    int identifier(string content) {
        insert(AstType::Declaration,"Identifier",content);
    }

    int importStatement(string content) {
        insert(AstType::ImportStatement,"Keyword", content);
    }

    int exportStatement(string content) {
        insert(AstType::ExportStatement, "Keyword", content);
    }

    int recordStatement(string content) {
        insert(AstType::RecordStatement, "Keyword", content);
    }

    int functionStatement(string content) {
        insert(AstType::FunctionStatement, "Keyword", content);
    }

    int ifStatement(string content) {
        insert(AstType::IfStatement, "Keyword", content);
    }

    int elseStatement(string content) {
        insert(AstType::ElseStatement, "keyword", content);
    }

    int whileStatement(string content) {
        insert(AstType::WhileStatement, "keyword", content);
    }

    int forEachStatement(string content) {
        insert(AstType::ForEachStatement, "keyword", content);
    }

};