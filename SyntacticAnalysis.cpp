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

void dc(std::vector<string>& S) {
    dc_c(S);
    dc_v(S);
    dc_p(S);
}

void dc_c(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token == "const") {
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
    } else {
        goBackOneToken();
    }
}

void dc_v(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token == "var") {
        variaveis(S);
        token = lexicalAnalysis();
        if (token != "colon") {
            printError(":");
            token = panic(S);
        }
        tipo_var(S);
        token = lexicalAnalysis();
        if (token != "tipe_real" &&  token != "tipo_integer") {
            printError("tipe real or integer");
            token = panic(S);
        }
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            token = panic(S);
        }
        dc_v(S);
    } else {
        goBackOneToken();
    }
}

void variaveis(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        token = panic(S);
    }
    mais_var(S);
}

void mais_var(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "comma") {
        printError(",");
        token = panic(S);
    }
    variaveis(S);
}

void dc_p(std::vector<string>& S) {
    string token = lexicalAnalysis();
    if (token == "procedure") {
        token = lexicalAnalysis();
        if (token != "ident") {
            printError("ident");
            token = panic(S);
        }
        parametros(S);
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            token = panic(S);
        }
        corpo_p(S);
        dc_p(S);
    } else {
        goBackOneToken();
    }
}

void parametros(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "paren_left") {
        printError("(");
        token = panic(S);
    }
    lista_par(S);
    token = lexicalAnalysis();
    if (token != "paren_right") {
        printError(")");
        token = panic(S);
    }
}

void lista_par(std::vector<string>& S) {
    variaveis(S);
    token = lexicalAnalysis();
    if (token != "colon") {
        printError(":");
        token = panic(S);
    }
    tipo_var(S);
    mais_var(S);
}

void mais_par(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        token = panic(S);
    }
    lista_par(S);
}

void corpo_p(std::vector<string>& S) {
    dc_loc(S);
    token = lexicalAnalysis();
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

void dc_loc(std::vector<string>& S) {
    dc_v(S);
}

void lista_arg(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "paren_left") {
        printError("(");
        token = panic(S);
    }
    argumentos(S);
    token = lexicalAnalysis();
    if (token != "paren_right") {
        printError(")");
        token = panic(S);
    }
}

void argumentos(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        token = panic(S);
    }
    cmd(S);
}

void mais_ident(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        token = panic(S);
    }
    argumentos(S);
}

void pfalsa(std::vector<string>& S) {
    token = lexicalAnalysis();
    if (token != "else") {
        printError("else");
        token = panic(S);
    }
    cmd(S);
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
