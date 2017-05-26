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
    string token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        token = panic(S);
    }
}

void dc(std::vector<string>& S) {
    
}

void dc_v(std::vector<string>& S) {
    
}

void dc_c(std::vector<string>& S) {
    
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
    
}

void expressao(std::vector<string>& S) {
    
}

void outros_termos(std::vector<string>& S) {
    
}

void termo(std::vector<string>& S) {
    
}

void mais_fatores(std::vector<string>& S) {
    
}

void fator(std::vector<string>& S) {
    
}
