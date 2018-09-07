%{
#include "ast.h"
#include <bits/stdc++.h>
using namespace std;
#include "bison.tab.hpp"
#define getToken() yylval.strin=new string(yytext);
#define YY_DECL extern "C" int yylex()
FILE * fp = fopen ("flex_output.txt", "w");;
 
%}

%option noyywrap
%%
"class"         {fprintf(fp, "%s\n","CLASS");return CLASS;}
"Program"       {fprintf(fp, "ID: %s\n",yytext);return PROGRAM;}
"{"             {return LCB;}
"}"             {return RCB;}
"["             {return LSB;}
"]"             {return RSB;}
"("             {return LRB;}
")"             {return RRB;}
","             {return COM;}
";"             {return SC;}
"\'"            {return SQ;}
"\""            {return DQ;}
"void"          {getToken();return VOID;}
"int"           {fprintf(fp, "INT_DECLARATION\n");getToken();return INT;}
"boolean"       {fprintf(fp, "BOOLEAN_DECLARATION\n");getToken();return BOOL;}
"if"            {return IF;}
"else"          {return ELSE;}
"for"           {return FOR;}
"break"         {return BREAK;}
"continue"      {return CONTINUE;}
"return"        {return RETURN;}
"callout"       {fprintf(fp, "%s\n","CALLOUT");return CALLOUT;}
"!"             {getToken();return NOT;}
"+"             {getToken();return PLUS;}
"-"             {getToken();return DIFF;}
"*"             {getToken();return MULT;}
"/"             {getToken();return DIV;}
"%"             {getToken();return MOD;}
"="             {getToken();return EQ;}
"+="            {getToken();return PLUSEQ;}
"-="            {getToken();return DIFFEQ;}
"<"             {getToken();return LT;}
">"             {getToken();return GT;}
"<="            {getToken();return LE;}
">="            {getToken();return GE;}
"=="            {getToken();return DEQ;}
"!="            {getToken();return NEQ;}
"&&"            {getToken();return AND;}
"||"            {getToken();return OR;}
"true"          {fprintf(fp, "BOOLEAN: false\n");return TRUE;}
"false"         {fprintf(fp, "BOOLEAN: true\n");return FALSE;}
[_a-zA-Z][_a-zA-Z0-9]* {fprintf(fp, "ID: %s\n",yytext);getToken();return ID;}
[0-9][0-9]*          {fprintf(fp, "INT: %s\n",yytext);yylval.integer=atoi(yytext);return DIGIT;}
"0x"[a-fA-F0-9][a-fA-F0-9]*      {sscanf(yytext, "%x", &yylval.integer);return HEXDIGIT;}
\'.\'		{fprintf(fp, "CHARACTER: %s\n",yytext);yylval.alnum=yytext[0]; return CHARLITERAL;}
\"(\\.|[^\\"])*\"	{fprintf(fp, "STRING: %s\n",yytext);getToken(); return STRINGLITERAL;}
[\n\t \v]+      { ; }  
<<EOF>>         {return 0;}
.               { return yytext[0]; }
%%