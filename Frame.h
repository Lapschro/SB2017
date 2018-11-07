#ifndef FRAME_H_
#define FRAME_H_

#include "Types.h"
#include <stack>
#include <vector>
#include "Class_Structures.h"

class Frame{
private:
	uint16_t method_index;
	uint16_t code_index;
	uint32_t current_pc;
	ClassInfo* classInfo;
	ClassInstance* thisClass;
	std::stack<Types*> operandStack;
	std::vector<Types*> locals;
	Code_Attribute *codeAttribute;
	Exceptions_Attribute *exceptionsAttribute;
	
public:
	static void (**interpreter_operations)(uint8_t* code, uint32_t* pc);
	Frame(ClassInfo* cInfo, Cp_Info* constantPool, uint16_t methodIndex, ClassInstance* cInstance, std::vector<Types*>* args);
	Frame(ClassInfo* cInfo, Cp_Info* constantPool, ClassInstance* cInstance, uint16_t methodIndex);
	~Frame();
	void Execute();
	Types* GetField(char* key);
	static void SetUp();
	void PushOperandStack(Types* value);
	Code_Attribute* GetCodeAttribute();
	ClassInfo* GetClassInfo();
	bool HandleException(int index);
};
#endif
