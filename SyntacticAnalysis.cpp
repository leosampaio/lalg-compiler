#include "SyntacticAnalysis.h"

using namespace std;

void panic(std::set<std::string> S) {
    string token = lexicalAnalysis();
    while (find(S.begin(), S.end(), token) == S.end()) {
        token = lexicalAnalysis();
    }
    goBackOneToken();
}

void programa(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "program") {
        printError("program");
        panic(merge(S, {"ident"}));
    } 
    token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        panic(merge(S, {"semicolon"}));
    }
    token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        panic(merge(S, {}));
    }
    corpo(S);
    token = lexicalAnalysis();
    if (token != "dot") {
        printError(".");
        panic(S);
    }
}

void corpo(std::set<string> S) {
    dc(S);
    string token = lexicalAnalysis();
    if (token != "begin") {
        printError("begin");
        panic(S);
    }
    comandos(S);
    token = lexicalAnalysis();
    if (token != "end") {
        printError("end");
        panic(S);
    }
}

void dc(std::set<string> S) {
    dc_c(S);
    dc_v(S);
    dc_p(S);
}

void dc_c(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token == "const") {
        token = lexicalAnalysis();
        if (token != "ident") {
            printError("ident");
            panic(S);
        }
        token = lexicalAnalysis();
        if (token != "equal") {
            printError("=");
            panic(S);
        }
        numero(S);
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(S);
        }
        dc_c(S);
    } else {
        goBackOneToken();
    }
}

void dc_v(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token == "var") {
        variaveis(S);
        token = lexicalAnalysis();
        if (token != "colon") {
            printError(":");
            panic(S);
        }
        tipo_var(S);
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(S);
        }
        dc_v(S);
    } else {
        goBackOneToken();
    }
}

void variaveis(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        panic(S);
    }
    mais_var(S);
}

void mais_var(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "comma") {
        printError(",");
        panic(S);
    }
    variaveis(S);
}

void dc_p(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token == "procedure") {
        token = lexicalAnalysis();
        if (token != "ident") {
            printError("ident");
            panic(S);
        }
        parametros(S);
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(S);
        }
        corpo_p(S);
        dc_p(S);
    } else {
        goBackOneToken();
    }
}

void parametros(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "paren_left") {
        printError("(");
        panic(S);
    }
    lista_par(S);
    token = lexicalAnalysis();
    if (token != "paren_right") {
        printError(")");
        panic(S);
    }
}

void lista_par(std::set<string> S) {
    variaveis(S);
    string token = lexicalAnalysis();
    if (token != "colon") {
        printError(":");
        panic(S);
    }
    tipo_var(S);
    mais_var(S);
}

void mais_par(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        panic(S);
    }
    lista_par(S);
}

void corpo_p(std::set<string> S) {
    dc_loc(S);
    string token = lexicalAnalysis();
    if (token != "begin") {
        printError("begin");
        panic(S);
    }
    comandos(S);
    token = lexicalAnalysis();
    if (token != "end") {
        printError("end");
        panic(S);
    }
}

void dc_loc(std::set<string> S) {
    dc_v(S);
}

void lista_arg(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "paren_left") {
        printError("(");
        panic(S);
    }
    argumentos(S);
    token = lexicalAnalysis();
    if (token != "paren_right") {
        printError(")");
        panic(S);
    }
}

void argumentos(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        panic(S);
    }
    cmd(S);
}

void mais_ident(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        panic(S);
    }
    argumentos(S);
}

void pfalsa(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "else") {
        printError("else");
        panic(S);
    }
    cmd(S);
}

void comandos(std::set<string> S) {
    string token = lexicalAnalysis();
    if(token == "read" || token == "write" || token == "while" || token == "if" || token == "ident" || token == "begin"){
        goBackOneToken();
        cmd(S);
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(S);
        }
        comandos(S);
    } else {
        goBackOneToken();
    }
}

void cmd(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token == "read")  { 
        token = lexicalAnalysis();
        if (token != "paren_left") {
            printError("(");
            panic(S);
        }
        variaveis(S);
        token = lexicalAnalysis();
        if (token != "paren_right") {
            printError(")");
            panic(S);
        }
    } else if (token == "write") {
        token = lexicalAnalysis();
        if (token != "paren_left") {
            printError("(");
            panic(S);
        }
        variaveis(S);
        token = lexicalAnalysis();
        if (token != "paren_right") {
            printError(")");
            panic(S);
        }
    } else if (token == "while") {
        token = lexicalAnalysis();
        if (token != "paren_left") {
            printError("(");
            panic(S);
        }
        condicao(S);
        token = lexicalAnalysis();
        if (token != "paren_right") {
            printError(")");
            panic(S);
        }
        token = lexicalAnalysis();
        if (token != "do") {
            printError("do");
            panic(S);
        }
        cmd(S);
    } else if (token == "if") {
        condicao(S);
        token = lexicalAnalysis();
        if (token != "then") {
            printError("then");
            panic(S);
        }
        cmd(S);
        pfalsa(S);
    } else if (token == "ident") {
        token = lexicalAnalysis();
        if(token == "attribution"){
            expressao(S);
        } else {
            goBackOneToken();
            lista_arg(S);
        }
    } else if (token == "begin") {
        comandos(S);
        token = lexicalAnalysis();
        if(token != "end"){
            printError("end");
            panic(S);
        }
    } else {
        printError("read' or 'write' or 'while' or 'if' or 'ident' or 'begin");
        panic(S);
    }
}

void condicao(std::set<string> S) {
    expressao(S);
    string token = lexicalAnalysis();
    if (token != "equal"|| token != "different"|| token != "less_than_or_equal" || token != "less_than" 
        ||  token != "greater_than_or_equal" || token != "greater_than") {
        printError("= or <> or <= or < or >= or >");
        panic(S);
    } 

    expressao(S);    
}

void expressao(std::set<string> S) {
    termo(S);
    outros_termos(S); 
}

void outros_termos(std::set<string> S) { //TODO 
    string token = lexicalAnalysis();
    if(token == "op_ad"){
        termo(S);
        outros_termos(S);
    }
    
    else{
        goBackOneToken();
    }
    
}

void termo(std::set<string> S) {
    op_un(S);
    fator(S);
    outros_termos(S);    
}

void mais_fatores(std::set<string> S) {
    string token = lexicalAnalysis();
    if(token != "op_mul"){
        printError("* or /");
        panic(S);
    }
    fator(S);
    outros_termos(S);
 }
    


void fator(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token == "ident")  { return;} 

    else if (token == "paren_left") {
        expressao(S);
        token = lexicalAnalysis();
        if(token != "paren_right"){
            printError(")");
            panic(S);
        }
    }

    else if (token != "real" && token != "integer") { 
        numero(S); 
        goBackOneToken();
        return; 
    }
    
    else{
        printError("ident or numero or (");
        panic(S);
    }
}

void numero(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "real" && token != "integer") {
        printError("real or integer");
    }
}

void op_un(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token == "op_ad"){}
    else{
        goBackOneToken();
    }
}

void tipo_var(std::set<string> S) {
    string token = lexicalAnalysis();
    if (token != "type_real" && token != "type_integer") {
        printError("real or integer");
    }
}

