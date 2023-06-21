#pragma once
#include <map>
#include <string>
#include <list>
#include <vector>
class VEVM_Instruction {
public:
	enum class InsType {
		C_CLASS, //CLASS [name]
		C_EXTEND, //EXTEND [name]
		C_FUNC, //FUNC [name]
		C_PERMISSON, //PERMISSON [public/private/protected]
		C_MODIFIER, //MODIFIER [static/virtual
		C_RETURN_TYPE, //RETURN_TYPE [type]
		C_DEFSTART, //DEFSTART (No para)
		C_DEFEND, //DEFEND (No para)
		PUSH_PARA, //PUSH_PARA [name]
		PUSH_CONST_PARA, //PUSH_CONST_PARA [name]
		PUSH_RETURN, //PUSH_RETURN [name]
		PUSH_CONST_RETURN, //PUSH_CONST_RETURN [name]
		NEW_LOCAL_TYPE_NAME, //NEW_LOCAL_NAME [type] [name]
		NEW_THIS_TYPE_NAME, //NEW_THIS_NAME [type] [name]
		MOVE_RETURN_PARA, //MOVE_RETURN_PARA		(No para)
		LOAD_CONST_STR, //LOAD_CONST_STR [name] [value]
		LOAD_CONST_NUM, //LOAD_CONST_NUM [name] [value]
		RETURN, //RETURN (No para)
		LOAD_LOCAL_RETURN, //LOAD_LOCAL_RETURN [name]
		CALL, //CALL [name]
		ASSIGN, //ASSIGN [name1] [name2] 
		TEST_GOTO, //TEST_GOTO [line_num]
		GOTO, //GOTO [line_num]
		DEL_LOCAL_NAME, //DEL_LOCAL_NAME [name]
		DEL_THIS_NAME, //DEL_THIS_NAME [name]
		REG_EXCEP_GOTO, //REG_EXCEP_GOTO [line_num]
		UNREG_EXCEP_GOTO, //UNREG_EXCEP_GOTO [line_num]
	};
	class Instruction {
	public:
		InsType type;
		std::string para1;
		std::string para2;
		Instruction(InsType type, std::string para1, std::string para2) {
			this->type = type;
			this->para1 = para1;
			this->para2 = para2;
		}
	};
	typedef std::vector<Instruction> List;
};
typedef VEVM_Instruction::InsType VEVMInsType;