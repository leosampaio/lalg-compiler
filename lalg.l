%{
#include "lalg.h"
%}
%option nounput yylineno
%%
[ \t\n]*\{(.*)\}[\n]		;

"program"					return PROGRAM;
"begin"						return BEGINN;
"end"						return END;
"const"						return CONST;
"var"						return VAR;
"while"						return WHILE;
"do"						return DO;
"if"						return IF;
"else"						return ELSE;
"read"						return READ;
"write"						return WRITE;
"procedure"					return PROCEDURE;
":"							return COLON;
":="						return ATTRIBUTION;
";"							return SEMICOLON;
"."							return DOT;
"=" 						return EQUAL;
"<>"						return DIFFERENT;
"<="						return LESS_THAN_OR_EQUAL;
">="						return GREATER_THAN_OR_EQUAL;
"<" 						return GREATER_THAN;
">" 						return LESS_THAN;
"("							return PAREN_LEFT;
")"							return PAREN_RIGHT;
"for"						return FOR;
"to"						return TO;
","							return COMMA;

[a-zA-Z][a-zA-Z0-9]*		return IDENTIFIER;
[0-9][0-9]*					return INTEGER;
[0-9]\.[0-9]+				return REAL;
[+-]						return OP_AD;
[*/]						return OP_MUL;

[ \t\n]						;
.							return LEXICAL_ERROR;
%%