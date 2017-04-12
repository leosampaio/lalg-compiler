#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include "lalg.h"

using namespace std;

// the extern C lets us link to c file
#ifdef __cplusplus
extern "C" {
#endif

extern int yylex();
extern int yylineno;
extern char* yytext;

#ifdef __cplusplus
}
#endif

map<int, string> createMap();

int main(void) {

    // auxilars
    int tokenID;

    tokenID = yylex();
    map<int, string> identifiersMap = createMap();

    while(tokenID != END_OF_FILE && tokenID != LEXICAL_ERROR) {
        cout << yylineno << ": " << yytext << " - " << identifiersMap[tokenID] << endl;
        if (tokenID == DOT) { break; }
        tokenID = yylex();
    }

    if (tokenID == LEXICAL_ERROR) {
        cerr << "Lexical error on line " << yylineno << " :(" << endl;
    }

    return 0;
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

    return m;
}