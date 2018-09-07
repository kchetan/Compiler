#include <bits/stdc++.h>
#include <llvm/IR/Value.h>
using namespace std;

static FILE * out_xml = fopen ("XML_visitor.txt", "w");
class ASTnode
{
    public:
        ASTnode(){}
        virtual void accept(class Visitor &v) = 0;
};


class Callout: public ASTnode
{
    private:
        string _str;
    public:
        Callout()
        {}
        Callout(string *str)
        {
            if(str!=NULL)
                _str=*str;
        }
        string getstring()
        {
            return _str;
        }
        virtual void print()
        {
            fprintf(out_xml,"<string value=\"%s\">\n",_str.c_str());
        }
        virtual void accept(Visitor &v);
};



class Expression: public Callout
{
    private:
        Expression *_expr;
    public:
        Expression()
        {}
        Expression(Expression *expr)
        {
            _expr=expr;
        }

        virtual void print()
        {
            _expr->print();
        }
        virtual void accept(Visitor &v);
};



class UExpression : public Expression
{
    private:
        Expression *right1;	
        string _oper;
    public:	
        UExpression()
        {}

        UExpression(string *oper,Expression *right)
        {
            if(oper!=NULL)
                _oper=*oper;
            right1=right;
        }
        string getop()
        {
            return _oper;
        }
        Expression *getexp()
        {
            return right1;
        }

        virtual void print()
        {
            string type;
            if(_oper =="-")
                type = "minus";
            else if (_oper == "!")
                type = "not";
            fprintf(out_xml, "<unary_expression type=\"%s\">\n",type.c_str() );
            right1->print();
            fprintf(out_xml, "</unary_expression>\n");
        }
        virtual void accept(Visitor &v);
};



class BiExpression: public Expression
{

    private:
        Expression *left1,*right1;
        string _oper;
    public:
        BiExpression()
        {}

        BiExpression(Expression *left,string *oper,Expression *right)
        {
            if(oper!=NULL)
                _oper=*oper;
            left1=left;
            right1=right;
        }
        string getop()
        {
            return _oper;
        }
        Expression *getleftexp()
        {
            return left1;
        }
        Expression *getrightexp()
        {
            return right1;
        }
        virtual void print()
        {
            string op_name;
            op_name="equal";
            if (_oper == "+") {_oper = "addition";}
            else if (_oper == "-") {op_name = "subtration";}
            else if (_oper == "*") {op_name = "multiplication";}
            else if (_oper == "/") {op_name = "division";}
            else if (_oper == "%") {op_name = "remainder";}
            else if (_oper == "<") {op_name = "less_than";}
            else if (_oper == ">") {op_name = "greater_than";}
            else if (_oper == "<=") {op_name = "less_equal";}
            else if (_oper == ">=") {op_name = "greater_equal";}
            else if (_oper == "==") {op_name = "is_equal";}
            else if (_oper == "!=") {op_name = "not_equal";}
            else if (_oper == "&&") {op_name = "and";}
            else if (_oper == "||") {op_name = "or";}
            if (op_name!="equal")
                fprintf(out_xml, "<binary_expression type=\"%s\">\n",op_name.c_str() );
            left1->print();
            right1->print();
            if (op_name!="equal")
                fprintf(out_xml, "</binary_expression>\n");
        }
        virtual void accept(Visitor &v);        
};



class Literal: public Expression
{
    private:
        char _cl;
    public:
        Literal()
        {}
        Literal(char cl)
        {
            _cl=cl;
        }
        char getch()
        {
            return _cl;
        }
        virtual void print()
        {
            fprintf(out_xml, "<character value=\"%c\"/>\n",_cl );
        }
        virtual void accept(Visitor &v);   
};



class INT_LITERAL :public Literal
{
    private:
        int _il;
        unsigned int _hex;
        int flag;
    public :
        INT_LITERAL()
        {}
        INT_LITERAL(int il)
        {
            _il=il;
            flag = 1;
        }
        INT_LITERAL(unsigned int hex)
        {
            _hex=hex;
            flag = 2;
        }
        int getinteger()
        {
            return _il;
        }
        unsigned int gethex()
        {
            return _hex;
        }
        virtual void print()
        {
            fprintf(out_xml, "<integer value=\"%d\"/>\n",int(_il) );
        }
        virtual void accept(Visitor &v);   
};



class Decl : public ASTnode
{
    private:
        string _id;
        INT_LITERAL *_ilt;
        int flag;
    public:
        string _ty;
        Decl()
        {}
        Decl(string * id)
        {
            if(id!=NULL)
                _id=*id;
            flag=1;
        }
        Decl(string *id,INT_LITERAL * ilt)
        {
            if(id!=NULL)
                _id=*id;
            _ilt=ilt;
            flag=2;
        }
        int getflag()
        {
            return flag;
        }
        string getstring()
        {
            return _id;
        }
        int getinteger()
        {
            return _ilt->getinteger();
        }
        virtual void accept(Visitor &v);   
};

class FieldDecl: public ASTnode
{
    private:
        string _type;
        vector<Decl *> _ids;
    public:
        FieldDecl(){}
        FieldDecl(string * type, vector<Decl *>* ids)
        {
            if(type!=NULL)
                _type=*type;
            if(ids!=NULL)	
            {
                _ids=*ids;
                reverse(_ids.begin(),_ids.end());
            }
        }
        vector <Decl *> getdecls()
        {
            return _ids;
        }
        string getType()
        {
            return _type;
        }
        void print()
        {
            /*for(int i=0;i<_ids.size();i++)
            {
                if(_ids[i]->getflag() == 1)
                {
                    if(_type=="int")
                        _type = "integer";
                    fprintf(out_xml, "<declaration name=\"%s\" type=\"%s\"/>\n",_ids[i]->getstring().c_str(),_type.c_str());

                }
                else if(_ids[i]->getflag()==2)
                {
                    if(_type=="int")
                        _type="integer";
                    fprintf(out_xml, "<declaration name=\"%s\" count=\"%d\" type=\"%s\"/>\n",_ids[i]->getstring().c_str(),_ids[i]->getinteger(),_type.c_str());
                }

            }*/
        }
        virtual void accept(Visitor &v);   
};



class BOOL_LITERAL : public Literal
{
    private:
        bool _bl;
    public:
        BOOL_LITERAL()
        {}
        BOOL_LITERAL(bool bl)
        {
            _bl=bl;
        }
        bool getbool()
        {
            return _bl;
        }
        virtual void print()
        {
            if(_bl)
                fprintf(out_xml, "<boolean value=\"true\"/>\n");
            else
                fprintf(out_xml, "<boolean value=\"false\"/>\n");
        
        }
        virtual void accept(Visitor &v);   
};



class Location: public Expression
{
    private:
        string *_id;
        Expression *_e;
        int flag;
    public:
        Location()
        {}
        Location(string *id)
        {
            _id=id;
            flag=1;
        }

        Location(string *id,Expression *e)
        {
            _id=id;
            _e=e;
            flag=2;
        }
        int getflag()
        {
            return flag;
        }
        string getstring()
        {
            return *_id;
        }

        Expression *getExpression()
        {
            return _e;
        }
        virtual void print()
        {
            if(flag==1)
            {
                fprintf(out_xml, "<location id=\"%s\"/>\n",(*_id).c_str());
            }
            else if(flag==2)
            {
                fprintf(out_xml, "<location id=\"%s\">\n",(*_id).c_str());
                //cout<<"%"<<*_id<<"[ ";
                fprintf(out_xml, "<position>\n");
                _e->print();
                fprintf(out_xml,"</position>\n");
                fprintf(out_xml, "</location>\n");
            }
        }
        virtual void accept(Visitor &v);   
};
///////////////// 
class Location_expr : public Expression{
    private:
        Location* _loc;
    public:
        Location_expr(Location* loc)
        {
            _loc = loc;
        }
        Location* getloc()
        {
            return _loc;
        }
       
        virtual void accept(Visitor &v);
};
///////////////// 
class VarDecl: public ASTnode
{
    private:
        string _type;
        vector<string *> _id;
    public:
        VarDecl(){}
        VarDecl(string *type,vector<string *> *id)
        {
            if(id!=NULL)
            {
                _id=*id;
            }
            if(type!=NULL)
                _type=*type;
        }

        vector<string *> getstring()
        {
            return _id;
        }

        string getType()
        {
            return _type;
        }
        virtual void accept(Visitor &v);   
};


class ASSIGN_OP : public ASTnode
{
    private :
        string _str;
    public:
        ASSIGN_OP()
        {
        }
        ASSIGN_OP(string * str)
        {
            if(str!=NULL)
                _str=*str;
        }
        string getop()
        {
            return _str;
        }
        virtual void print()
        {
            fprintf(out_xml,"%s",_str.c_str());
        }
        virtual void accept(Visitor &v);   
};



class Statement: public ASTnode
{
    private:
        int _break,_cont;
        Location *_locat;
        Expression *_expr;
        ASSIGN_OP *_assign_operator;
        int flag;
    public:
        Statement()
        {}
        Statement(int fla)
        {
            if(fla==0)
            {
                _break=1;
                _cont=0;
            }
            else if(fla==1)
            {
                _break=0;
                _cont=1;
            }
            flag=1;
        }
        Statement(Location *locat, ASSIGN_OP *assign_operator,Expression *expr)
        {
            _locat=locat;
            _assign_operator=assign_operator;
            _expr=expr;
            flag=2;
        }

        Expression *getExpression()
        {
            return _expr;
        }
        ASSIGN_OP *getAssign()
        {
            return _assign_operator;
        }
        Location *getLocation()
        {
            return _locat;
        }
        int getflag()
        {
            return flag;
        }
        int getbr()
        {
            return _break;
        }
        virtual void print()
        {
            
        }
        virtual void accept(Visitor &v);   
};

class Block:public Statement
{
    private:
        vector<VarDecl *> _vars;
        vector<Statement *> _stmts;
    public:
        Block(){}
        Block(vector<VarDecl *> *vars,vector<Statement *> *stmts)
        {
            if(vars!=NULL)
            {
                _vars=*vars;
            }
            if(stmts!=NULL)
            {
                _stmts=*stmts;
            }
        }
        vector<VarDecl *> getvars()
        {
            return _vars;
        }
        vector<Statement *> getstmts()
        {
            return _stmts;
        }
        virtual void print()
        {
            
        }
        virtual void accept(Visitor &v);   
};

class Statement1:public Statement
{
    private :
        Expression *_cond;
        Block *_ifblock;
        Block *_elseblock;
        string _assign_operator;
        string _id;
        Expression *_init;
        Expression *_term;
        Block *_b;
        int flag;
    public:
        Statement1(Expression *cond, Block *ifblock)
        {
            _cond=cond;
            _ifblock=ifblock;
            flag=1;
        }
        Statement1(Expression *cond, Block *ifblock, Block *elseblock)
        {
            _cond=cond;
            _ifblock=ifblock;
            _elseblock=elseblock;
            flag=2;
        }
        Statement1(string *id,Expression *init, Expression *term, Block *b)
        {
            if(id!=NULL)
                _id=*id;
            _init=init;
            _term=term;
            _b=b;
            flag=3;
        }
        string getid()
        {
            return _id;
        }
        int getflag()
        {
            return flag;
        }
        Expression *getinit()
        {
            return _init;
        }
        Expression *getterm()
        {
            return _term;
        }
        Block *getbblock()
        {
            return _b;
        }
        Block *getifblock()
        {
            return _ifblock;
        }
        Block *getelseblock()
        {
            return _elseblock;
        }
        Expression *getcond()
        {
            return _cond;
        }
        virtual void print()
        {
            
        }
        virtual void accept(Visitor &v);   
};

class ARG:public ASTnode
{
    private:
        string _type;
        string _id;
    public:
        ARG()
        {}
        ARG(string *type,string * id)
        {
            if(type!=NULL)
                _type=*type;
            if(id!=NULL)
                _id=*id;
        }
        string gettype()
        {
            return _type;
        }
        string getname()
        {
            return _id;
        }
        virtual void accept(Visitor &v);   
};



class MethodDecl: public ASTnode
{
    private: 
        string _type;
        string _name;
        vector<ARG *> _typeid;
        Block *_block;

    public:
        MethodDecl(){}
        MethodDecl(string *type,string *name,vector<ARG*> *type_id,Block *block)    
        {
            if(type!=NULL)
                _type=*type;
            if(name!=NULL)
                _name=*name;
            if(type_id!=NULL)
            {
                _typeid=*type_id;
            }
            _block=block;
        }

        string getType()
        {
            return _type;
        }

        string getstring()
        {
            return _name;
        }

        vector<ARG *> getTypeid()
        {
            return _typeid;
        }

        void appendTypestring(ARG *type_id)
        {
            _typeid.push_back(type_id);
        }

        Block *getBlock()
        {
            return _block;
        }

        void print()
        {
            
        }
        virtual void accept(Visitor &v);   
};


class Program: public ASTnode
{
    private:
        vector<FieldDecl*> _fields;
        vector<MethodDecl*> _methods;
    public:
        Program()
        {
        }
        Program(vector<FieldDecl *>* fields,vector<MethodDecl *>* methods)
        {
            if(fields!=NULL)
                _fields=*fields;
            if(methods!=NULL)
                _methods=*methods;
            int i;
            for(i=0;i<_fields.size();i++)
                _fields[i]->print();
            for(i=0;i<_methods.size();i++)
                _methods[i]->print();
        }

        vector<FieldDecl* > getFields()
        {
            return _fields;
        }

        vector<MethodDecl *> getMethods()
        {
            return _methods;
        }

        void appendField(FieldDecl *field)
        {
            _fields.push_back(field);
        }

        void appendMethof(MethodDecl *method)
        {
            _methods.push_back(method);
        }
        virtual void accept(Visitor &v);
};
/*
class Program: public ASTnode
{
    private:
        vector<FieldDecl*> _fields;
        vector<Statement*> _statements;
    public:
        Program()
        {
        }
        Program(vector<FieldDecl *>* fields,vector<Statement *>* statements)
        {
            if(fields!=NULL)
                _fields=*fields;
            if(statements!=NULL)
                _statements=*statements;
            int i;
        }

        vector<FieldDecl* > getFields()
        {
            return _fields;
        }

        vector<Statement *> getMethods()
        {
            return _statements;
        }

        void appendField(FieldDecl *field)
        {
            _fields.push_back(field);
        }

        void appendMethof(Statement *method)
        {
            _statements.push_back(method);
        }
};*/

class MethodCall: public Statement, public Expression
{
    public:
        MethodCall()
        {}
        virtual void accept(Visitor &v);   
};

class MethodCall1: public MethodCall
{
    private:
        string _name;
        vector<Expression *> _expr;
    public:
        MethodCall1(){}
        MethodCall1(string *name,vector<Expression *> *expr)
        {
            if(name!=NULL)
                _name=*name;
            if(expr!=NULL)
            {
                _expr=*expr;
                reverse(_expr.begin(),_expr.end());
            }
        }

        string getName()
        {
            return _name;
        }

        vector<Expression *> getExpression()
        {
            return _expr;
        }

        void appendExpression(Expression *e)
        {
            _expr.push_back(e);
        }
        virtual void print()
        {
            
        }
        virtual void accept(Visitor &v);   
};




class MethodCall2: public MethodCall
{
    private:
        string _name;
        vector<Callout *> _args;
    public:
        MethodCall2(){}
        MethodCall2(string *name,vector<Callout *> *args)
        {
            if(name!=NULL)
            {    
                _name = *name;
            }
            if(args!=NULL)
                _args=*args;
        }

        string getName()
        {
            return _name;
        }

        vector<Callout *> getArgs()
        {
            return _args;
        }

        void appendArg(Callout *arg)
        {
            _args.push_back(arg);
        }
        virtual void print()
        {
            
        }
        virtual void accept(Visitor &v);   
};

class Ret: public Statement
{
    private:
        Expression *_ret;
        int flag;
    public:
        Ret()
        {
            flag=1;
        }
        Ret(Expression *ret)
        {
            flag=2;
            _ret=ret;
        }

        Expression *getRet()
        {
            return _ret;
        }
        virtual void print()
        {
            
        }
        virtual void accept(Visitor &v);   
};


/*
class MethodCall: public Statement, public Expression
{
    public:
        MethodCall()
        {}
};



class MethodCall2: public MethodCall
{
    private:
        string _name;
        vector<Callout *> _args;
    public:
        MethodCall2(){}
        MethodCall2(string *name,vector<Callout *> *args)
        {
            if(name!=NULL)
            {    
                _name = *name;
            }
            if(args!=NULL)
                _args=*args;
        }

        string getName()
        {
            return _name;
        }

        vector<Callout *> getArgs()
        {
            return _args;
        }

        void appendArg(Callout *arg)
        {
            _args.push_back(arg);
        }
        virtual void print()
        {
            fprintf(out_xml, "<callout function=\"%s\">\n",_name.c_str() );
            // cout<<"call @"<<_name<<"( ";
            for(int i=0;i<_args.size();i++)
            {
                _args[i]->print();
                // if(i<_args.size()-1)
                //     cout<<",";
            }
            //cout<<" );"<<endl;
            fprintf(out_xml, "</callout>\n" );
        }
};
*/

extern Program *root;
