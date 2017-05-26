#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>

std::string lexicalAnalysis();
void syntacticAnalysis();
std::string panic(std::vector<std::string>& S);
void printError(std::string expected);
void goBackOneToken();

void programa(std::vector<std::string>& S);
void corpo(std::vector<std::string>& S);
void dc(std::vector<std::string>& S);
void dc_v(std::vector<std::string>& S);
void dc_c(std::vector<std::string>& S);
void variaveis(std::vector<std::string>& S);
void mais_var(std::vector<std::string>& S);
void dc_p(std::vector<std::string>& S);
void parametros(std::vector<std::string>& S);
void lista_par(std::vector<std::string>& S);
void mais_par(std::vector<std::string>& S);
void corpo_p(std::vector<std::string>& S);
void dc_loc(std::vector<std::string>& S);
void lista_arg(std::vector<std::string>& S);
void argumentos(std::vector<std::string>& S);
void mais_ident(std::vector<std::string>& S);
void pfalsa(std::vector<std::string>& S);
void comandos(std::vector<std::string>& S);
void cmd(std::vector<std::string>& S);
void condicao(std::vector<std::string>& S);
void expressao(std::vector<std::string>& S);
void outros_termos(std::vector<std::string>& S);
void termo(std::vector<std::string>& S);
void mais_fatores(std::vector<std::string>& S);
void fator(std::vector<std::string>& S);
