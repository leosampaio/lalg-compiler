#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>

std::string lexicalAnalysis();
void syntacticAnalysis();
void panic(std::set<std::string> S);
void printError(std::string expected);
void goBackOneToken();
std::set<std::string> merge(std::set<std::string>& S, std::set<std::string> extra);

void programa(std::set<std::string> S);
void corpo(std::set<std::string> S);
void dc(std::set<std::string> S);
void dc_v(std::set<std::string> S);
void dc_c(std::set<std::string> S);
void variaveis(std::set<std::string> S);
void mais_var(std::set<std::string> S);
void dc_p(std::set<std::string> S);
void parametros(std::set<std::string> S);
void lista_par(std::set<std::string> S);
void mais_par(std::set<std::string> S);
void corpo_p(std::set<std::string> S);
void dc_loc(std::set<std::string> S);
void lista_arg(std::set<std::string> S);
void argumentos(std::set<std::string> S);
void mais_ident(std::set<std::string> S);
void pfalsa(std::set<std::string> S);
void comandos(std::set<std::string> S);
void cmd(std::set<std::string> S);
void condicao(std::set<std::string> S);
void expressao(std::set<std::string> S);
void outros_termos(std::set<std::string> S);
void termo(std::set<std::string> S);
void mais_fatores(std::set<std::string> S);
void fator(std::set<std::string> S);
void numero(std::set<std::string> S);
void op_un(std::set<std::string> S);
void tipo_var(std::set<std::string> S);