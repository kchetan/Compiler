/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_BISON_TAB_HPP_INCLUDED
# define YY_YY_BISON_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    PROGRAM = 259,
    SQ = 260,
    DQ = 261,
    LCB = 262,
    RCB = 263,
    SC = 264,
    COM = 265,
    LSB = 266,
    RSB = 267,
    LRB = 268,
    RRB = 269,
    VOID = 270,
    INT = 271,
    BOOL = 272,
    IF = 273,
    ELSE = 274,
    FOR = 275,
    RETURN = 276,
    BREAK = 277,
    CONTINUE = 278,
    CALLOUT = 279,
    NOT = 280,
    PLUS = 281,
    DIFF = 282,
    MULT = 283,
    DIV = 284,
    MOD = 285,
    LT = 286,
    GT = 287,
    LE = 288,
    GE = 289,
    EQ = 290,
    PLUSEQ = 291,
    DIFFEQ = 292,
    DEQ = 293,
    NEQ = 294,
    AND = 295,
    OR = 296,
    TRUE = 297,
    FALSE = 298,
    DIGIT = 299,
    HEXDIGIT = 300,
    ID = 301,
    CHARLITERAL = 302,
    STRINGLITERAL = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 24 "bison.ypp" /* glr.c:2555  */

	double num; 
	string *strin;
	unsigned int hex;
	int integer;
	int typ;
	bool binar;
	char alnum;

	Program *prg;
	FieldDecl *fld;
	vector <FieldDecl*> *vfl;
	MethodDecl *met;
	vector <MethodDecl*> *vmt;
	Decl *de;
	vector <Decl*> *vde;
	ARG *ar;
	vector <ARG*> *var;
	Expression *exp;
	Literal *lit;
	INT_LITERAL *ilit;
	BOOL_LITERAL *blit;
	Location *loc;
	VarDecl *vdc;
	Statement *stm;
	Block *blk;
	MethodCall *mcl;
	MethodCall1 *mc1;
	MethodCall2 *mc2;
	Callout *clo;
	Statement *ieb;
	Statement *fbl;
	Ret *ret;
	vector <string*> *vil;
	vector <VarDecl*> *vvd;
	vector <Statement *> *vst;
	vector <Expression*> *vxp;
	vector <Callout*> *vco;
	ASSIGN_OP * asp;


#line 145 "bison.tab.hpp" /* glr.c:2555  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_HPP_INCLUDED  */
