#include "SyntacticAnalysis.h"

using namespace std;

map<const string, set<string> > fm;
set<string> first(string token) {
    static bool executedOnce = false;
    if(!executedOnce) {
        fm["corpo"] = merge(fm["dc"], {"begin"});
        fm["dc"] = merge(merge(fm["dc_c"], fm["dc_v"]), fm["dc_p"]);
        fm["dc_c"] = {"const"};
        fm["dc_v"] = {"var"};
        fm["tipo_var"] = {"real", "integer"};
        fm["variaveis"] = {"ident"};
        fm["mais_var"] = {"comma"};
        fm["dc_p"] = {"procedure"};
        fm["parametros"] = {"paren_left"};
        fm["lista_par"] = fm["variaveis"];
        executedOnce = true;
    }
    return fm[token];
}

void panic(set<string> S) {
    string token = lexicalAnalysis();
    while (find(S.begin(), S.end(), token) == S.end()) {
        token = lexicalAnalysis();
    }
    goBackOneToken();
}

void programa(set<string> S) {
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
        panic(merge(S, first("corpo")));
    }
    corpo(merge(S, {"dot"}));
    token = lexicalAnalysis();
    if (token != "dot") {
        printError(".");
        panic(S);
    }
}

void corpo(set<string> S) {
    dc(merge(S, {"begin"}));
    string token = lexicalAnalysis();
    if (token != "begin") {
        printError("begin");
        panic(merge(S, first("comandos")));
    }
    comandos(merge(S, {"end"}));
    token = lexicalAnalysis();
    if (token != "end") {
        printError("end");
        panic(S);
    }
}

void dc(set<string> S) {
    dc_c(merge(S, first("dc_v")));
    dc_v(merge(S, first("dc_p")));
    dc_p(S);
}

void dc_c(set<string> S) {
    string token = lexicalAnalysis();
    if (token == "const") {
        token = lexicalAnalysis();
        if (token != "ident") {
            printError("ident");
            panic(merge(S, {"equal"}));
        }
        token = lexicalAnalysis();
        if (token != "equal") {
            printError("=");
            panic(merge(S, first("numero")));
        }
        numero(merge(S, {"semicolon"}));
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(merge(S, first("dc_c")));
        }
        dc_c(S);
    } else {
        goBackOneToken();
    }
}

void dc_v(set<string> S) {
    string token = lexicalAnalysis();
    if (token == "var") {
        variaveis(merge(S, {"colon"}));
        token = lexicalAnalysis();
        if (token != "colon") {
            printError(":");
            panic(merge(S, first("tipo_var")));
        }
        tipo_var(merge(S, {"semicolon"}));
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(merge(S, first("dc_v")));
        }
        dc_v(S);
    } else {
        goBackOneToken();
    }
}

void variaveis(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        panic(merge(S, first("mais_var")));
    }
    mais_var(S);
}

void mais_var(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "comma") {
        printError(",");
        panic(merge(S, first("variaveis")));
    }
    variaveis(S);
}

void dc_p(set<string> S) {
    string token = lexicalAnalysis();
    if (token == "procedure") {
        token = lexicalAnalysis();
        if (token != "ident") {
            printError("ident");
            panic(merge(S, first("parametros")));
        }
        parametros(merge(S, {"semicolon"}));
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(merge(S, first("corpo_p")));
        }
        corpo_p(merge(S, first("dc_p")));
        dc_p(S);
    } else {
        goBackOneToken();
    }
}

void parametros(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "paren_left") {
        printError("(");
        panic(merge(S, first("lista_par")));
    }
    lista_par(merge(S, {"paren_right"}));
    token = lexicalAnalysis();
    if (token != "paren_right") {
        printError(")");
        panic(S);
    }
}

void lista_par(set<string> S) {
    variaveis(S);
    string token = lexicalAnalysis();
    if (token != "colon") {
        printError(":");
        panic(merge(S, first("tipo_var")));
    }
    tipo_var(merge(S, first("mais_var")));
    mais_var(S);
}

void mais_par(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        panic(merge(S, first("lista_par")));
    }
    lista_par(S);
}

void corpo_p(set<string> S) {
    dc_loc(S);
    string token = lexicalAnalysis();
    if (token != "begin") {
        printError("begin");
        panic(merge(S, first("comandos")));
    }
    comandos(merge(S, {"end"}));
    token = lexicalAnalysis();
    if (token != "end") {
        printError("end");
        panic(S);
    }
}

void dc_loc(set<string> S) {
    dc_v(S);
}

void lista_arg(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "paren_left") {
        printError("(");
        panic(merge(S, first("argumentos")));
    }
    argumentos(merge(S, {"paren_right"}));
    token = lexicalAnalysis();
    if (token != "paren_right") {
        printError(")");
        panic(S);
    }
}

void argumentos(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "ident") {
        printError("ident");
        panic(merge(S, first("cmd")));
    }
    cmd(S);
}

void mais_ident(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "semicolon") {
        printError(";");
        panic(merge(S, first("argumentos")));
    }
    argumentos(S);
}

void pfalsa(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "else") {
        printError("else");
        panic(merge(S, first("cmd")));
    }
    cmd(S);
}

void comandos(set<string> S) {
    string token = lexicalAnalysis();
    if(token == "read" || token == "write" || token == "while" || token == "if" || token == "ident" || token == "begin"){
        goBackOneToken();
        cmd(merge(S, {"semicolon"}));
        token = lexicalAnalysis();
        if (token != "semicolon") {
            printError(";");
            panic(merge(S, first("comandos")));
        }
        comandos(S);
    } else {
        goBackOneToken();
    }
}

void cmd(set<string> S) {
    string token = lexicalAnalysis();
    if (token == "read")  { 
        token = lexicalAnalysis();
        if (token != "paren_left") {
            printError("(");
            panic(merge(S, first("variaveis")));
        }
        variaveis(merge(S, {"paren_right"}));
        token = lexicalAnalysis();
        if (token != "paren_right") {
            printError(")");
            panic(S);
        }
    } else if (token == "write") {
        token = lexicalAnalysis();
        if (token != "paren_left") {
            printError("(");
            panic(merge(S, first("variaveis"))); 
        }
        variaveis(merge(S, {"paren_right"}));
        token = lexicalAnalysis();
        if (token != "paren_right") {
            printError(")");
            panic(S);
        }
    } else if (token == "while") {
        token = lexicalAnalysis();
        if (token != "paren_left") {
            printError("(");
            panic(merge(S, first("condicao")));
        }
        condicao(merge(S, {"paren_right"}));
        token = lexicalAnalysis();
        if (token != "paren_right") {
            printError(")");
            panic(merge(S, {"do"}));
        }
        token = lexicalAnalysis();
        if (token != "do") {
            printError("do");
            panic(merge(S, first("cmd")));
        }
        cmd(S);
    } else if (token == "if") {
        condicao(merge(S, {"then"}));
        token = lexicalAnalysis();
        if (token != "then") {
            printError("then");
            panic(merge(S, first("corpo")));
        }
        cmd(merge(S, first("pfalsa")));
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
        comandos(merge(S, {"end"}));
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

void condicao(set<string> S) {
    expressao(S);
    string token = lexicalAnalysis();
    if (token != "equal"|| token != "different"|| token != "less_than_or_equal" || token != "less_than" 
        ||  token != "greater_than_or_equal" || token != "greater_than") {
        printError("= or <> or <= or < or >= or >");
        panic(merge(S, first("expressao")));
    } 
    expressao(S);
}

void expressao(set<string> S) {
    termo(S);
    outros_termos(S); 
}

void outros_termos(set<string> S) { //TODO 
    string token = lexicalAnalysis();
    if(token == "op_ad"){
        termo(S);
        outros_termos(S);
    }
    else{
        goBackOneToken();
    }
    
}

void termo(set<string> S) {
    op_un(S);
    fator(S);
    outros_termos(S);    
}

void mais_fatores(set<string> S) {
    string token = lexicalAnalysis();
    if(token != "op_mul"){
        printError("* or /");
        panic(merge(S, first("fator")));
    }
    fator(merge(S, first("outros_termos")));
    outros_termos(S);
 }
    


void fator(set<string> S) {
    string token = lexicalAnalysis();
    if (token == "ident")  { return;} 

    else if (token == "paren_left") {
        expressao(merge(S, {"paren_right"}));   
        token = lexicalAnalysis();
        if(token != "paren_right"){
            printError(")");
            panic(S);
        }
    }

    else if (token != "real" && token != "integer") { 
        numero(S);  //faltou
        goBackOneToken();
        return; 
    }
    else{
        printError("ident or numero or (");
        panic(S);
    }
}

void numero(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "real" && token != "integer") {
        printError("real or integer");
        panic(S);
    }
}

void op_un(set<string> S) {
    string token = lexicalAnalysis();
    if (token == "op_ad"){
        printError("op_ad");
        panic(S);
    } else{
        goBackOneToken();
    }
}

void tipo_var(set<string> S) {
    string token = lexicalAnalysis();
    if (token != "type_real" && token != "type_integer") {
        printError("real or integer");
        panic(S);
    }
}

