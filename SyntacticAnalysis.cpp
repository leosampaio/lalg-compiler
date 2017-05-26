#include "SyntacticAnalysis.h"

using namespace std;

#define ERROR ""

string panic(std::vector<std::string>& S) {
    return "blah";
}

void programa(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token != "program") {
        printError("program");
        token = panic(S);
    } 
    token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        token = panic(S);
    }
    token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        token = panic(S);
    }
    corpo(S);
    token = lexicalAnalysis();
    if (token != "dot") {
        printError(".");
        token = panic(S);
    }
}

void corpo(std::vector<string>& S) {
    dc(S);
    string token = lexicalAnalysis();
    if (token != "begin") {
        printError("begin");
        token = panic(S);
    }
    comandos(S);
    token = lexicalAnalysis();
    if (token != "end") {
        printError("end");
        token = panic(S);
    }
}

void dc_c(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token != "const") {
        printError("const");
        token = panic(S);
    }
    token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        token = panic(S);
    }
    token = lexicalAnalysis();
    if (token != "equal") {
        printError("=");
        token = panic(S);
    }
    numero(S);
    token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        token = panic(S);
    }
    dc_c(S);
}

void dc(std::vector<string>& S) {
    dc_c(S);
    dc_v(S);
    dc_p(S);
}

void dc_v(std::vector<string>& S) {
    
}

void variaveis(std::vector<string>& S) {
    
}

void mais_var(std::vector<string>& S) {
    
}

void dc_p(std::vector<string>& S) {
    
}

void parametros(std::vector<string>& S) {
    
}

void lista_par(std::vector<string>& S) {
    
}

void mais_par(std::vector<string>& S) {
    
}

void corpo_p(std::vector<string>& S) {
    
}

void dc_loc(std::vector<string>& S) {
    
}

void lista_arg(std::vector<string>& S) {
    
}

void argumentos(std::vector<string>& S) {
    
}

void mais_ident(std::vector<string>& S) {
    
}

void pfalsa(std::vector<string>& S) {
    
}

void comandos(std::vector<string>& S) {
    
}

void cmd(std::vector<string>& S) {
    
}

void condicao(std::vector<string>& S) {
    expressao(S);
    string token = lexicalAnalysis();
    if (token != "equal"|| token != "different"|| token != "less_than_or_equal" || token != "less_than" 
        ||  token != "greater_than_or_equal" || token != "greater_than") {
        printError("= or <> or <= or < or >= or >");
        token = panic(S);
    } 

    expressao(S);    
}

void expressao(std::vector<string>& S) {
    termo(S);
    outros_termos(S); 
}

void outros_termos(std::vector<string>& S) { //TODO 
    string token = lexicalAnalysis();
    if(token == "op_ad"){
        termo(S);
        outros_termos(S);
    }
    
    else{
        goBackOneToken();
    }
    
}

void termo(std::vector<string>& S) {
    op_un(S);
    fator(S);
    outros_termos(S);    
}

void mais_fatores(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if(token != "op_mul"){
        printError("* or /");
        token = panic(S);
    }
    fator(S);
    outros_termos(S);
 }
    


void fator(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token == "ident")  { return;} 

    else if (token == "paren_left") {
        expressao();
        token = lexicalAnalysis();
        if(token != "paren_right"){
            printError(")");
            token = panic(S);
        }
    }

    else if (numero()) { return;}


    else{
        printError("ident or numero or (");
        token = panic(S);

    }
}

void numero(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token != "real" && token != "integer") {
        printError("real or integer");
    }
}

void op_un(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token == "op_ad"){}
    else{
        goBackOneToken();
    }
}

