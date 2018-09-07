#include<bits/stdc++.h>
using namespace std;

class Visitor	{
	public:
		virtual void visit(ASTnode *e) = 0;
		virtual void visit(Location_expr *e) = 0;
		virtual void visit(Program *e) = 0;
		virtual void visit(Callout *e) = 0;
		virtual void visit(Expression *e) = 0;
		virtual void visit(UExpression *e) = 0;
		virtual void visit(BiExpression *e) = 0;
		virtual void visit(Literal *e) = 0;
		virtual void visit(INT_LITERAL *e) = 0;
		virtual void visit(Decl *e) = 0;
		virtual void visit(FieldDecl *e) = 0;
		virtual void visit(BOOL_LITERAL *e) = 0;
		virtual void visit(Location *e) = 0;
		virtual void visit(VarDecl *e) = 0;
		virtual void visit(ASSIGN_OP *e) = 0;
		virtual void visit(Statement *e) = 0;
		virtual void visit(Block *e) = 0;
		virtual void visit(Statement1 *e) = 0;
		virtual void visit(ARG *e) = 0;
		virtual void visit(MethodDecl *e) = 0;
		virtual void visit(MethodCall *e) = 0;
		virtual void visit(MethodCall1 *e) = 0;
		virtual void visit(MethodCall2 *e) = 0;
		virtual void visit(Ret *e) = 0;
};

void ASTnode::accept(Visitor &v)	{
	v.visit(this);
}

void Location_expr::accept(Visitor &v)	{
	v.visit(this);
}

void Program::accept(Visitor &v)	{
	v.visit(this);
}

void Callout::accept(Visitor &v)	{
	v.visit(this);
}

void Expression::accept(Visitor &v)	{
	v.visit(this);
}

void UExpression::accept(Visitor &v)	{
	v.visit(this);
}

void BiExpression::accept(Visitor &v)	{
	v.visit(this);
}

void Literal::accept(Visitor &v)	{
	v.visit(this);
}

void INT_LITERAL::accept(Visitor &v)	{
	v.visit(this);
}

void Decl::accept(Visitor &v)	{
	v.visit(this);
}

void FieldDecl::accept(Visitor &v)	{
	v.visit(this);
}

void BOOL_LITERAL::accept(Visitor &v)	{
	v.visit(this);
}

void Location::accept(Visitor &v)	{
	v.visit(this);
}

void VarDecl::accept(Visitor &v)	{
	v.visit(this);
}

void ASSIGN_OP::accept(Visitor &v)	{
	v.visit(this);
}
void Statement::accept(Visitor &v)	{
	v.visit(this);
}

void Block::accept(Visitor &v)	{
	v.visit(this);
}

void Statement1::accept(Visitor &v)	{
	v.visit(this);
}
void ARG::accept(Visitor &v)	{
	v.visit(this);
}

void MethodDecl::accept(Visitor &v)	{
	v.visit(this);
}

void MethodCall::accept(Visitor &v)	{
	v.visit(this);
}
void MethodCall1::accept(Visitor &v)	{
	v.visit(this);
}

void MethodCall2::accept(Visitor &v)	{
	v.visit(this);
}

void Ret::accept(Visitor &v)	{
	v.visit(this);
}
