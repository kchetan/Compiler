CPP = g++
CPPFLAGS= -o -std=c++11
LEX = flex
BISON= bison
BISONFLAGS= -d

RM = /bin/rm -f

Parser: bison.tab.o lex.yy.o
	${CPP} ${CPPFLAGS} lex.yy.c bison.tab.cpp -o scanner -lfl `llvm-config --libs core jit native --cxxflags` `llvm-config --ldflags --libs`

bison.tab.o: bison.ypp
	${BISON} ${BISONFLAGS} bison.ypp
	
lex.yy.o: flex.l
	${LEX} flex.l
	
clean:
	/bin/rm -f lex.yy.* y.tab.* *.o Parser
