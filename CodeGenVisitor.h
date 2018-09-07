/* NOTE : Can we combine our functions to both generate code and output the xml as well???*/
#include <stack>


#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
//#include <llvm/IR/PassManager.h>
#include <llvm/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
//#include <llvm/ModuleProvider.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/DataTypes.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
static IRBuilder<> Builder(getGlobalContext());


class CodeGenBlock {
    public:
        BasicBlock *block;
        std::map<std::string, Value*> localsymboltable;
};

class CodeGenVisitor : public Visitor {

	public :
		BasicBlock *forbreakblock;
		BasicBlock *forloopblock;
		//static std::unique_ptr<Module> TheModule;
		std::stack<CodeGenBlock *> blocks;
		Module *module;
		std::map<string, Value*> symbolTable;
		Function *mainFunction;
		BasicBlock *bblock;
		Value *exp_ret;
		string global_id;
		Value* global_term;

		CodeGenVisitor()	{
			this->module = new Module("main", getGlobalContext());	
		}
		void pushBlock(BasicBlock *block) 
		{ 
			blocks.push(new CodeGenBlock()); 
			blocks.top()->block = block; 	
		}
    	void popBlock() 
    	{ 
    		CodeGenBlock *top = blocks.top();
    		blocks.pop();
    		delete top;
    	}
    	static AllocaInst* CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName, string type) {

		    IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
		                   TheFunction->getEntryBlock().begin());
		    AllocaInst* alloca;
		    if(type=="int") 
		        alloca = TmpB.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, VarName.c_str());
		    else if(type=="boolean")
		        alloca = TmpB.CreateAlloca(Type::getInt1Ty(getGlobalContext()), 0, VarName.c_str());
		    return alloca;
		}
    	BasicBlock *currentBlock()
    	{ 
    		return blocks.top()->block; 
    	}
		static Type *typeOf(string type) 
		{
			if (strcmp(type.c_str(),"int") == 0)
				return Type::getInt32Ty(getGlobalContext());
			else if (strcmp(type.c_str(),"boolean")==0)
				return Type::getInt1Ty(getGlobalContext());
			return Type::getVoidTy(getGlobalContext());
		}
		virtual void visit(ASTnode *e)
		{

		}
		virtual void visit(Program *e)
		{
        	vector<FieldDecl*> fields;
        	vector<MethodDecl*> methods;
			fields=e->getFields();
			for(int i=0;i<fields.size();i++)
			{
				fields[i]->accept(*this);
			}
			methods=e->getMethods();
			for(int i=0;i<methods.size();i++)
			{
				methods[i]->accept(*this);
			}
			//verifyModule(*module, PrintMessageAction);
			PassManager pm;
			pm.add(createPrintModulePass(&outs()));
			pm.run(*module);
		}
		virtual void visit(Callout *e)
		{
			string value= e->getstring();
			int len = value.length();
			value = value.substr(1,len-2);
			exp_ret = Builder.CreateGlobalStringPtr(value);
			return;
		}
		virtual void visit(Expression *e)
		{
		}
		virtual void visit(UExpression *e)
		{
			// unary operator
			e->getexp()->accept(*this);
			Value *expr = exp_ret;
			int E_size = expr->getType()->getIntegerBitWidth();

			
			if(!strcmp(e->getop().c_str(),"-"))
			{
				Builder.CreateNeg(expr, "negate_op");
			}
			if(!strcmp(e->getop().c_str(),"!"))
			{
				if(E_size != 1)
				{
					cerr << "Logical operation ! not defined on int" << endl;
					exit(0);
				}
				Builder.CreateNot(expr, "not_op");
			}
			
		}
		virtual void visit(BiExpression *e)
		{
			Instruction::BinaryOps instr;
			Expression *lhs = e->getleftexp();
			Expression *rhs = e->getrightexp();
			lhs->accept(*this);
			Value *L = exp_ret;
			rhs->accept(*this);
			Value *R = exp_ret;
			int L_size = L->getType()->getIntegerBitWidth();
			int R_size = R->getType()->getIntegerBitWidth();

			
			if(strcmp(e->getop().c_str(), "+")==0)
			{

				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateAdd(L, R, "addInstruct");
				return;
			}

			else if(strcmp(e->getop().c_str(), "-")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateSub(L, R, "subInstruct");
				return;
			}

			else if(strcmp(e->getop().c_str(), "*")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateMul(L, R, "mulInstruct");
				return;
			}

			else if(strcmp(e->getop().c_str(), "/")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateUDiv(L, R, "divInstruct");
				return;
			}
			
			else if(strcmp(e->getop().c_str(), "%")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateURem(L, R, "remInstruct");
				return;
			}
			
			else if(strcmp(e->getop().c_str(), "&&")==0)
			{
				if(L_size == 32 || R_size == 32)
				{
					cerr << "operation not defined on integer \"&&\"" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateAnd(L, R, "andInst");
				return;
			}
			
			else if(strcmp(e->getop().c_str(), "||")==0)
			{
				if(L_size == 32 || R_size == 32)
				{
					cerr << "operation not defined on ints \"||\"" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateOr(L, R, "orInst");
				return;
			}

			else if(strcmp(e->getop().c_str(), "==")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateICmpEQ(L, R, "cmpisEqualInst");
				return;
			}
			
			else if(strcmp(e->getop().c_str(), "<=")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateICmpULT(L, R, "cmpleInst");
				return;
			}

			else if(strcmp(e->getop().c_str(), ">=")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateICmpUGE(L, R, "cmpgeInst");
				return;
			}
			
			else if(strcmp(e->getop().c_str(), "<")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateICmpULT(L, R, "cmpltInst");
				return;
			}

			else if(strcmp(e->getop().c_str(), ">")==0)
			{
				if(L_size == 1 || R_size == 1)
				{
					cerr << "operation not defined on boolean" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateICmpUGT(L, R, "cmpgtInst");
				return;
			}

			else if(strcmp(e->getop().c_str(), "!=")==0)
			{
				if(L_size!=R_size)
				{
					cerr << "Not similar datatypes in !=" << endl;
					exit(0);
				}
				exp_ret = Builder.CreateICmpNE(L, R, "cmpisNotEqualInst");
				return;
			}

			/*Value *bin=NULL;

			if(L!=NULL && R!=NULL)
				bin = BinaryOperator::Create(instr, L,R, "",  currentBlock());

			exp_ret = bin;
			return;*/
		}
		virtual void visit(Literal *e)
		{
			// has to write for char literal
			exp_ret = ConstantInt::get(Type::getInt8Ty(getGlobalContext()),int(e->getch()),true);
		}
		virtual void visit(INT_LITERAL *e)
		{
			exp_ret = ConstantInt::get(getGlobalContext(), APInt(32, e->getinteger()));
		}
		virtual void visit(Decl *e)
		{
			//cout << e->_ty << "\n" << e->getstring() << endl ;
			if(e->getflag()==1)	
			{
				ConstantInt *C;
				if(e->_ty == "int")
			    {
			    	C = ConstantInt::get(getGlobalContext(), APInt(32, 0));
			    }
			    if(e->_ty == "boolean")
			    {
			    	C = ConstantInt::get(getGlobalContext(), APInt(1, 0));
			    }
				GlobalVariable *gv = new GlobalVariable(*this->module,typeOf(e->_ty),false,GlobalValue::ExternalLinkage,0,e->getstring());
				this->symbolTable[e->getstring()] = gv;
				gv->setInitializer(C);
				/*AllocaInst *alloc = new AllocaInst(typeOf(e->_ty), e->getstring(), this->bblock);
				this->symbolTable[e->getstring()] = alloc;
				Value* v=alloc;
				exp_ret = alloc;*/
			}
			else
			{
				GlobalVariable* gv = new GlobalVariable(*this->module, ArrayType::get(typeOf(e->_ty),e->getinteger()), false, GlobalValue::ExternalLinkage, 0, e->getstring());
    			ConstantAggregateZero* C = ConstantAggregateZero::get(ArrayType::get(typeOf(e->_ty),e->getinteger()));
    			gv->setInitializer(C);
				this->symbolTable[e->getstring()] = gv;
				/*GlobalVariable *gv = new GlobalVariable(*this->module,PointerType::getUnqual(ArrayType::get(typeOf(e->_ty),e->getinteger())),false,GlobalValue::ExternalLinkage,0,e->getstring());
				this->symbolTable[e->getstring()] = gv;
				*/

				/*ArrayType* ArrayTy_6 = ArrayType::get(typeOf(e->_ty), e->getinteger());
        		AllocaInst *alloc = new AllocaInst(ArrayTy_6, e->getstring(), currentBlock());
        		this->symbolTable[e->getstring()] = alloc;
        		Value* v=alloc;
        		exp_ret = alloc;*/
			}
			//Value* V = ConstantInt::get(getGlobalContext(), APInt(32,1));
		}
		virtual void visit(Location_expr *e)
		{
			e->getloc()->accept(*this);
			exp_ret = Builder.CreateLoad(exp_ret, e->getloc()->getstring());
			
		}
		virtual void visit(FieldDecl *e)
		{

			vector<Decl *> d = e->getdecls();
			//cout<<d.size()<<endl;
			for(int i=0;i<d.size();i++)
			{
				//cout << d[i]->getstring() << endl;
				d[i]->accept(*this);
			}
			/*for(vector<Decl *>::iterator it=e->getdecls().begin(); it!=e->getdecls().end(); it++)
			{
				cout << "came" << endl;
				cout << (*it)->getType() << endl;
				//(*it)->accept(*this);
			}*/

		}
		virtual void visit(BOOL_LITERAL *e)
		{
			int value = e-> getbool();
			exp_ret = ConstantInt::get(Type::getInt1Ty(getGlobalContext()),value,true);
		}
		virtual void visit(Location *e)
		{
			Value *V;
			//exp_ret = new LoadInst(blocks.top()->localsymboltable[e->getstring()], "", false, currentBlock());
			/*Expression ex=e->getExpression();
			ex.accept(*this);*/
			Value *Val  = ConstantInt::get(getGlobalContext(), APInt(32,1));
            //Value *V = blocks.top()->localsymboltable[e->getstring()];

            if(e->getExpression() != NULL){
            	e->getExpression()->accept(*this);
                if(Val==NULL){
                	cerr << "error in expression" << endl;
                	exit(0);
                    return ;
                }
                if(symbolTable.find(e->getstring()) == symbolTable.end())
				{
						cerr<<"global Variable not declared "<<e->getstring() <<endl;
						//validity = 1;
						exit(0);
				}
                //cout << e->getstring() << endl;
                vector<Value *> tmp_args;
				tmp_args.push_back(Builder.getInt32(0));
				tmp_args.push_back(exp_ret);
				exp_ret = Builder.CreateInBoundsGEP(symbolTable[e->getstring()], tmp_args, "gep");
				//exp_ret = Builder.CreateLoad(exp_ret, e->getstring());
                /*vector<Value*> Arref   {ConstantInt::get(getGlobalContext(),APInt(32,0,false)), Val};
                
				exp_ret = Builder.CreateLoad(Builder.CreateGEP(symbolTable[e->getstring()], Arref));
				*/return;
                
            }
            if(blocks.top()->localsymboltable.find(e->getstring()) == blocks.top()->localsymboltable.end())
			{
				if(symbolTable.find(e->getstring()) == symbolTable.end())
				{
						cerr<<"Variable not declared "<<e->getstring() <<endl;
						//validity = 1;
						exit(0);
				}
				else
				{
					V = symbolTable[e->getstring()];
				}
			}
			else
			{
				V = blocks.top()->localsymboltable[e->getstring()];
			}
            if (V == NULL){
            	cerr << "variable not found" << endl;
            	exit(0);
                return ;
            }
            //cout << e->getstring()<<endl;
            exp_ret =  V;
            return;
        }
		virtual void visit(VarDecl *e)
		{
			vector<string *> id = e->getstring();
			/*for(int i=0;i<id.size();i++)
			{
				//cout<<*id[i]<<endl;
				AllocaInst *alloc = new AllocaInst(typeOf(e->getType()), *id[i], currentBlock());

				//context.locals()[(*var_)[i]->id_] = alloc;
				blocks.top()->localsymboltable[*id[i]] = alloc;
			}*/
			llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
            for (int i=0;i<id.size();i++) { 
                llvm::Value *InitVal;
                llvm::AllocaInst *Alloca;
                if(!strcmp(e->getType().c_str(),"int")){
                    InitVal = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
                    Alloca = CreateEntryBlockAlloca(TheFunction, *(id[i]), "int");
                }
                else{
                    InitVal = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(1,0));
                    Alloca = CreateEntryBlockAlloca(TheFunction, *(id[i]),"boolean");
                }
                
                Builder.CreateStore(InitVal, Alloca);
                blocks.top()->localsymboltable[*id[i]] = Alloca;
            }
            exp_ret = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,1));
            return ;
		}
		virtual void visit(ASSIGN_OP *e)
		{
			//already written in statement itself in flag = 2;

		}
		virtual void visit(Statement *e)
		{
			
			//l.accept(*this);
			
			if(e->getflag() ==1)
			{
				// need to write for it break and continue
				if(e->getbr() == 1)
				{
					// Value *v=ConstantInt::get(getGlobalContext(), APInt(32,1));
					// exp_ret = v;

					//cout << "came break" << endl;
					Builder.CreateBr(forbreakblock);
					exp_ret = Constant::getNullValue(Type::getInt32Ty(getGlobalContext()));
					return;
				}
				else
				{
   				
					//cout << "came" << global_id <<endl;
					Value* Alloca = blocks.top()->localsymboltable[global_id];
				    Value* CurVar = Builder.CreateLoad(Alloca, global_id.c_str());

				    Value *StepVal = ConstantInt::get(getGlobalContext(), APInt(32, 1));
				    Value *NextVar = Builder.CreateAdd(CurVar, StepVal, "nextvar");

				    Builder.CreateStore(NextVar, Alloca);

				    Value *EndCond = Builder.CreateICmp(CmpInst::ICMP_SLT, NextVar, global_term, "lesstmp");
				    // Insert an explicit fall through from the current block to the LoopBB.
				    Builder.CreateCondBr(EndCond, forloopblock, forbreakblock);
				    exp_ret = Constant::getNullValue(Type::getInt32Ty(getGlobalContext()));
				    return;
					// cout << "came" << endl;
					// Value *V = ConstantInt::get(getGlobalContext(), APInt(32,1));
					// exp_ret = V;
				}
			}
			else if(e->getflag() ==2)
			{
				Expression *ex=e->getExpression();
				ex->accept(*this);
				Value * expr = exp_ret;
				Location *l=e->getLocation();
				Value * V;
				if(blocks.top()->localsymboltable.find(l->getstring()) == blocks.top()->localsymboltable.end())
				{
					if(symbolTable.find(l->getstring()) == symbolTable.end())
					{
							cerr<<"Variable not declared "<<l->getstring() <<endl;
							//validity = 1;
							exit(0);
					}
					else
					{
							V = symbolTable[l->getstring()];
					}
				}
				else
				{
					V = blocks.top()->localsymboltable[l->getstring()];
				}
				
				if(l->getflag()==2)
				{
					l->accept(*this);
					V = exp_ret;	
				}
				Value *val= Builder.CreateLoad(V, l->getstring());
				int V_size = val->getType()->getIntegerBitWidth();
				int E_size = expr->getType()->getIntegerBitWidth();

				if(V_size != E_size)
				{
					cerr << "Datatypes of LHS and RHS not same" << endl;
					exit(0);
				}
				if(!strcmp(e->getAssign()->getop().c_str(),"="))
				{
					/*for(std::map<string,Value *>::iterator it = blocks.top()->localsymboltable.begin(); it != blocks.top()->localsymboltable.end(); ++it) {
  //v.push_back(it->first);
  cout << it->first << endl;
}*/
					//exp_ret global variable;
					/*if(exp_ret!=NULL)
					{

						exp_ret = new StoreInst(exp_ret, blocks.top()->localsymboltable[l->getstring()], currentBlock());
					}
					return;*/
				}
				else if(!strcmp(e->getAssign()->getop().c_str(),"+="))
				{
					/*if(blocks.top()->localsymboltable.find(l->getstring()) == blocks.top()->localsymboltable.end())
					{
						cerr<<"Variable not declared"<<l->getstring() <<endl;
						//validity = 1;
						return;
					}*/
					//exp_ret global variable;
					if(expr!=NULL)
					{
						expr=Builder.CreateAdd(val,expr,"addEqual");
					}
				}
				else if(!strcmp(e->getAssign()->getop().c_str(),"-="))
				{
					/*if(blocks.top()->localsymboltable.find(l->getstring()) == blocks.top()->localsymboltable.end())
					{
						cerr<<"Variable not declared"<<l->getstring() <<endl;
						//validity = 1;
						return;
					}*/
					//expr global variable;
					if(expr!=NULL)
					{

						expr=Builder.CreateAdd(val,expr,"subEqual");
					}
				}
				if(expr==NULL)
					cerr << "error in right Expression" << endl;
				else
					Builder.CreateStore(expr, V);
				exp_ret = ConstantInt::get(getGlobalContext(), APInt(32,1));

			
			}
        	/*ASSIGN_OP a=e->getAssign();
        	a.accept(*this);*/
		}
		virtual void visit(Block *e)
		{
			vector<VarDecl *> v = e->getvars();
			vector<Value *> old;
			exp_ret = ConstantInt::get(getGlobalContext(), APInt(32,1));
			for(int i=0;i<v.size();i++)
			{
				//cout << d[i]->getstring() << endl;
				vector<string *> a = v[i]->getstring();
				for(int j=0;j<a.size();j++)
				{
					//cout << *a[j] << " " << a.size() << endl;
					old.push_back(blocks.top()->localsymboltable[*a[j]]);
				}
				v[i]->accept(*this);

			}
       		vector<Statement *> s = e->getstmts();
       		for(int i=0;i<s.size();i++)
			{
				//cout << d[i]->getstring() << endl;
				s[i]->accept(*this);	
			}
			for(int i=0;i<v.size();i++)
			{
				//cout << d[i]->getstring() << endl;
				vector<string *> a = v[i]->getstring();
				for(int j=0;j<a.size();j++)
				{
					old.push_back(blocks.top()->localsymboltable[*a[j]]);
					if(old[j] == NULL)
            		    blocks.top()->localsymboltable.erase(*a[j]);
        		    else
          		    	blocks.top()->localsymboltable[*a[j]] = old[j];
				}
			}
		}
		virtual void visit(Statement1 *e)
		{
			//cout << "came " << e->getflag() << endl;
			if(e->getflag() == 2  || e->getflag() == 1)
			{
				// if else
				e->getcond()->accept(*this);
				Value *condV  = exp_ret;	
				if(exp_ret!=NULL)
				{
					condV = Builder.CreateICmpEQ(condV, ConstantInt::get(getGlobalContext(), APInt(1, 1, false)), "ifcond");
					Function *TheFunction = Builder.GetInsertBlock()->getParent();
		            
		            BasicBlock *ThenBB = BasicBlock::Create(getGlobalContext(), "then", TheFunction);
		            BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
		            BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

		            Builder.CreateCondBr(condV, ThenBB, ElseBB);
		            
		            Builder.SetInsertPoint(ThenBB);	
		            
		            e->getifblock()->accept(*this);
					Value *ThenV = exp_ret;
		            if (ThenV == 0) {
		                return ;
		            }
		            
		            Builder.CreateBr(MergeBB);
		            // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
		            ThenBB = Builder.GetInsertBlock();

		            // Emit else block.
		            TheFunction->getBasicBlockList().push_back(ElseBB);
		            Builder.SetInsertPoint(ElseBB);
		            
		            
					
		            if (e->getelseblock()){
		               e->getelseblock()->accept(*this);
		            } 
		            Value *ElseV = exp_ret;
		            Builder.CreateBr(MergeBB);
		            // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
		            ElseBB = Builder.GetInsertBlock();
		            TheFunction->getBasicBlockList().push_back(MergeBB);
		            Builder.SetInsertPoint(MergeBB);
		            
		            /*PHINode *PN = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()), 2,"iftmp");
		            
		            PN->addIncoming(ThenV, ThenBB);
		            PN->addIncoming(ElseV, ElseBB);
		            exp_ret = PN;*/
		            return;
				}
			}
			else if(e->getflag() == 3)
			{
				global_id = e->getid();
				e->getinit()->accept(*this);
				Value *StartVal = exp_ret;
	            if (StartVal == 0)
	                return ;
	             e->getterm()->accept(*this);
	            Value *EndCond = exp_ret;
	            Value *term_cond = EndCond;
	            global_term = EndCond;
	            if (EndCond == NULL)
	            {
	            	cout << "endcond is null" << endl;
	                return ;
	            }

	            int init_size = StartVal->getType()->getIntegerBitWidth();
			    int term_size = EndCond->getType()->getIntegerBitWidth();

			    if(init_size != 32 || term_size != 32)
			    {
			        cerr << "For expressions do not evaluate to int" << endl;
			        exit(0);
			    }
	            Function *TheFunction = Builder.GetInsertBlock()->getParent();

	            AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, e->getid(),"int");
	            Builder.CreateStore(StartVal, Alloca);


	            BasicBlock *PreheaderBB = Builder.GetInsertBlock();
	            BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), "forloop", TheFunction);
	            forloopblock = LoopBB;
	            BasicBlock *AfterBB = BasicBlock::Create(getGlobalContext(), "afterforloop", TheFunction);
	            forbreakblock = AfterBB;
	            Value *init_Val = Builder.CreateLoad(Alloca, e->getid());
			    EndCond = Builder.CreateICmp(CmpInst::ICMP_SLT, init_Val, term_cond, "lesstmp");
			    // Insert an explicit fall through from the current block to the LoopBB.
			    Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
			    Builder.SetInsertPoint(LoopBB);
			    Value *OldVal = blocks.top()->localsymboltable[e->getid()];
	            blocks.top()->localsymboltable[e->getid()] = Alloca;
	            e->getbblock()->accept(*this);
	            if (exp_ret == NULL)
	                return ;
	            Value *StepVal = ConstantInt::get(getGlobalContext(), APInt(32, 1));
			    Value *CurVar = Builder.CreateLoad(Alloca, e->getid());
			    Value *NextVar = Builder.CreateAdd(CurVar, StepVal, "addone");
			    Builder.CreateStore(NextVar, Alloca);
			    EndCond = Builder.CreateICmp(CmpInst::ICMP_SLT, NextVar, term_cond, "lesstmp");
			    Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
    			Builder.SetInsertPoint(AfterBB);
    			if (OldVal)
	                blocks.top()->localsymboltable[e->getid()] = OldVal;
	            else
	                blocks.top()->localsymboltable.erase(e->getid());

	            Value *V = ConstantInt::get(getGlobalContext(), APInt(32,1));
	            exp_ret = V;
			}
		}
		virtual void visit(ARG *e)
		{

		}
		virtual void visit(MethodDecl *e)
		{
			vector<Type*> argTypes;
			vector<string> argNames;
			vector<ARG *> t = e->getTypeid();
			for(int i=0;i<t.size();i++)
			{
				//cout << t[i]->gettype() << endl;
				argTypes.push_back(typeOf(t[i]->gettype()));
				argNames.push_back(t[i]->getname());
			}

			FunctionType *ftype = FunctionType::get(typeOf(e->getType()),argTypes,false);
			Function *function = Function::Create(ftype,Function::ExternalLinkage,e->getstring(),this->module);
			unsigned Idx = 0;
            for (Function::arg_iterator AI = function->arg_begin(); Idx != t.size(); ++AI, ++Idx) {
                AI->setName(argNames[Idx]); 
            }
			//return function;
			BasicBlock *bblock_new = BasicBlock::Create(getGlobalContext(), "entry", function, 0);
			Builder.SetInsertPoint(bblock_new);
			/*for(std::map<std::string, Value*>::iterator it = bblock.begin(); it != bblock.end(); ++it) {
			  
			  cout << it->first << "\n";
			}*/
			pushBlock(bblock_new);
			Idx =0;
			for (Function::arg_iterator AI = function->arg_begin(); Idx != t.size(); ++AI, ++Idx) { 
                //cout<<"for "<<argNames[Idx]<<" "<<argTypes[Idx]<<endl;
                //AllocaInst *Alloca = CreateEntryBlockAlloca(function, argNames[Idx],t[Idx]->gettype());
                AllocaInst *Alloca = new AllocaInst(typeOf(t[Idx]->gettype()), t[Idx]->getname(), currentBlock());
                Builder.CreateStore(AI, Alloca);
                //cout<<"stored\n";
                blocks.top()->localsymboltable[t[Idx]->getname()] = Alloca;
                //cout<<"stored in map\n";
            }
			Block *b=e->getBlock();
			b->accept(*this);
			Value *RetVal = exp_ret;
            if (RetVal) {
                // Finish off the function.
                Builder.CreateRet(RetVal);
               
            }
			//ReturnInst::Create(getGlobalContext(),bblock_new);

			/*bloc_->codeGen(context);
			ReturnInst::Create(getGlobalContext(),bblock_new);	*/
			popBlock();
			/*vector<ARG *> t = e->getTypeid();
			for(int i=0;i<t.size();i++)
			{
				//cout << d[i]->getstring() << endl;
				t[i]->accept(*this);
			}
			Block b=e->getBlock();
			b.accept(*this);*/
			exp_ret = function;
			
		}
		virtual void visit(MethodCall *e)
		{

		}
		virtual void visit(MethodCall1 *e)
		{
			Function *function = this->module->getFunction(e->getName());
			if(function==NULL)
			{
				cerr<<e->getName()<<" function not declared"<<endl;
				//validity = 1;
				exit(0);
				return ;
			}
			int i;
			vector<Value*> args;
			vector<Expression *> exprs=e->getExpression();
			for(i=0;i<exprs.size();i++)
			{
				exprs[i]->accept(*this);
				args.push_back(exp_ret);
			}

			CallInst *call = NULL;
			
			exp_ret=Builder.CreateCall(function, args, "methodcall");

		}

		virtual void visit(MethodCall2 *e)
		{
			
			//Function *CalleeF = this->module->getFunction(e->getName());
			string name= e->getName();
			int len = name.length();
			name = name.substr(1,len-2);
            //if (CalleeF == 0)
             //   return ;

            // If argument mismatch error.
            vector<Callout *> c=e->getArgs();
            //cout << "came" << c.size() <<"--" << CalleeF->arg_size() << endl;
            // if (CalleeF->arg_size() != c.size())
            //     return ;
            std::vector<Type*> argtp;
            std::vector<Value*> ArgsV;
            for (int i=c.size()-1;i>=0;i--) {
            	c[i]->accept(*this);
                ArgsV.push_back( exp_ret );
                if (ArgsV.back() == 0) 
                    return ;
                if(i==0)
                	//argtp.push_back(builder.getInt8Ty()­>getPointerTo());
                	argtp.push_back(Builder.getInt8Ty()->getPointerTo());
            }
            //exp_ret = Builder.CreateCall(CalleeF, ArgsV, "calltmp");
            //return ;
            llvm::ArrayRef<llvm::Type*> argsRef(argtp);
            FunctionType* fType = FunctionType::get(Type::getInt32Ty(getGlobalContext()), argsRef, true);
    		Constant* func = this->module->getOrInsertFunction(name, fType);
   			exp_ret = Builder.CreateCall(func, ArgsV);
		}
		virtual void visit(Ret *e)
		{

			if(e->getRet() !=NULL){
				e->getRet()->accept(*this);
                return;
            }
            exp_ret = ConstantInt::get(getGlobalContext(), APInt(32,0));
            return ;
		}


};