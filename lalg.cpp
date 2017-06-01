#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include "lalg.h"
#include "SyntacticAnalysis.h"

using namespace std;

// the extern C lets us link to c file
#ifdef __cplusplus
extern "C" {
#endif

extern int yylex();
extern int yylineno;
extern int yyleng;
extern FILE* yyin;
extern char* yytext;

#ifdef __cplusplus
}
#endif

map<int, string> createMap();
map<int, string> identifiersMap;

// globals for rolling tokens back
string lastReadToken;
bool didAskToGoBackOneToken = false;

int main(void) {

    // auxilars
    identifiersMap = createMap();
    syntacticAnalysis();

    return 0;
}

string lexicalAnalysis() {
    if (didAskToGoBackOneToken) { didAskToGoBackOneToken = false; return lastReadToken; }

    int tokenID = yylex();
    while (tokenID == LEXICAL_ERROR) {
        cerr << "Lexical error on line " << yylineno << ": unexpected token '" << yytext << "\'" << endl;
        tokenID = yylex();
    }

    lastReadToken = identifiersMap[tokenID];
    return lastReadToken;
}

void syntacticAnalysis() {
    set<string> s;
    return programa(s);
}

void printError(std::string expected) {
    cerr << "Syntax Error on line "  
        << yylineno 
        << ": Found '" 
        << yytext 
        << "', expected '" 
        << expected
        << "'"
        << endl;
}

void goBackOneToken() {
    didAskToGoBackOneToken = true;
}

std::set<std::string> merge(std::set<std::string> S, std::set<std::string> extra) {
    S.insert(extra.begin(), extra.end());
    return S;
}

map<int, string> createMap() {
    map<int, string> m;
    m[LEXICAL_ERROR] = "Error";
    m[IDENTIFIER] = "ident";
    m[INTEGER] = "integer";
    m[REAL] = "real";
    m[OP_AD] = "op_ad";
    m[OP_MUL] = "op_mul";
    m[PROGRAM] = "program";
    m[BEGINN] = "begin";
    m[END] = "end";
    m[CONST] = "const";
    m[VAR] = "var";
    m[WHILE] = "while";
    m[DO] = "do";
    m[IF] = "if";
    m[ELSE] = "else";
    m[READ] = "read";
    m[WRITE] = "write";
    m[PROCEDURE] = "procedure";
    m[COLON] = "colon";
    m[ATTRIBUTION] = "attribution";
    m[SEMICOLON] = "semicolon";
    m[DOT] = "dot";
    m[EQUAL] = "equal";
    m[DIFFERENT] = "different";
    m[LESS_THAN_OR_EQUAL] = "less_than_or_equal";
    m[GREATER_THAN_OR_EQUAL] = "greater_than_or_equal";
    m[GREATER_THAN] = "greater_than";
    m[LESS_THAN] = "less_than";
    m[PAREN_LEFT] = "paren_left";
    m[PAREN_RIGHT] = "paren_right";
    m[FOR] = "for";
    m[TO] = "to";
    m[COMMA] = "comma";
    m[TYPE_INTEGER] = "type_integer";
    m[TYPE_REAL] = "type_real";
    m[THEN] = "then";
    m[END_OF_FILE] = "end_of_file";

    return m;
}