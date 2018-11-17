#include "Frame.h"
#include "Interpreter.h"
#include "Types.h"
#include <iostream>
#include <string>
#include "ScreenPrinter.h"
#include <sstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

/*
uint8_t* code is a reference to the code of a method
uint32_t* pc is the current program counter of a frame
std::stack<Types*>* operandStack is the current frame's operandStack
std::vector<Types*>* locals a reference to the current local variables in the frame
Cp_Info* constant_pool a reference to the Frame's ClassInfo's constant pool, to fetch items in it
ClassInstance* thisClass a reference to the class instance of the caller to modify it's fields, etc
*/
void (*operations[256])(uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass );

//Funcao para auxilio na criacao de arrays multidimensionais
void CreateMultiArray(ArrayType* array, std::string type, std::stack<int> counter);

void Frame::SetUp(){

	operations[0x00] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// NOP
		(*pc)++;
	};
	operations[0x01] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ACONST_NULL
		(*pc)++;
		operandStack->push(0);
	};
	operations[0x02] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ICONST_M1
		(*pc)++;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = -1;
		operandStack->push(tipo);
	};
	operations[0x03] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ICONST_0
		(*pc)++;
		Types* tipo = new Types((char*)"I");
		operandStack->push(tipo);
	};
	operations[0x04] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ICONST_1
		(*pc)++;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = 1;
		operandStack->push(tipo);
	};
	operations[0x05] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ICONST_2
		(*pc)++;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = 2;
		operandStack->push(tipo);
	};
	operations[0x06] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ICONST_3
		(*pc)++;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = 3;
		operandStack->push(tipo);
	};
	operations[0x07] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ICONST_4
		(*pc)++;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = 4;
		operandStack->push(tipo);
	};
	operations[0x08] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ICONST_5
		(*pc)++;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = 5;
		operandStack->push(tipo);
	};
	operations[0x09] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LCONST_0
		(*pc)++;
		Types* tipo = new Types((char*)"J");
		operandStack->push(tipo);
	};
	operations[0x0a] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LCONST_1
		(*pc)++;
		Types* tipo = new Types((char*)"J");
		*tipo->basicRef->type_int = 1;
		operandStack->push(tipo);
	};
	operations[0x0b] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FCONST_0
		(*pc)++;
		Types* tipo = new Types((char*)"F");
		operandStack->push(tipo);
	};
	operations[0x0c] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FCONST_1
		(*pc)++;
		float pFlut = 1.0;
		uint32_t aux;
		memcpy(&aux, &pFlut, sizeof(uint32_t));
		Types* tipo = new Types((char*)"F");
		*tipo->basicRef->type_float = aux;
		operandStack->push(tipo);
	};
	operations[0x0d] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FCONST_2
		(*pc)++;
		float pFlut = 2.0;
		uint32_t aux;
		memcpy(&aux, &pFlut, sizeof(uint32_t));
		Types* tipo = new Types((char*)"F");
		*tipo->basicRef->type_float = aux;
		operandStack->push(tipo);
	};
	operations[0x0e] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DCONST_0
		(*pc)++;
		Types* tipo = new Types((char*)"D");
		operandStack->push(tipo);
	};
	operations[0x0f] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DCONST_1
		(*pc)++;
		double grandao = 1.0;
		uint64_t aux;
		memcpy(&aux, &grandao, sizeof(uint64_t));
		Types* tipo = new Types((char*)"D");
		*tipo->basicRef->type_double = aux;
		operandStack->push(tipo);
	};
	operations[0x10] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// BI_PUSH
		(*pc)++;
		uint8_t byte = *(code + (*pc));
		(*pc)++;
		uint32_t aux = ((byte & 0x80) == 0) ? byte : 0x00 | byte;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = aux;
		operandStack->push(tipo);
	};
	operations[0x11] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// SI_PUSH
		(*pc)++;
		uint8_t byte1 = *(code + (*pc));
		(*pc)++;
		uint8_t byte2 = *(code + (*pc));
		(*pc)++;
		uint16_t aux = 0;
		aux += byte1;
		aux = (aux << 8) + byte2;
		uint32_t aux1 = ((aux & 0x8000) == 0) ? aux : 0xFFFF0000 + aux;
		Types* tipo = new Types((char*)"I");
		*tipo->basicRef->type_int = aux1;
		operandStack->push(tipo);
	};
	operations[0x12] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LDC
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;

		Cp_Info* cpool = (constant_pool + index - 1);
		Types* tipo = NULL;

		switch (cpool->tag) {
		case 3: //int
			tipo = new Types((char*)"I");
			*tipo->basicRef->type_int = cpool->typeInt;
			break;
		case 4: //float
			tipo = new Types((char*)"F");
			*tipo->basicRef->type_float = cpool->typeFloat;
			break;
		case 7: //classRef
		{
			std::string aux = "L";
			cpool = constant_pool + cpool->typeClassInfo - 1;
			char* aux2 = (char*)cpool->typeUTF8String.stringU;
			aux += std::string(aux2);
			tipo = new Types((char*)aux.c_str());
		}
		break;
		case 8: //stringRef
			tipo = new Types((char*)"STRING");
			cpool = constant_pool + cpool->typeStringRef - 1;
			*tipo->stringRef = std::string((char*)cpool->typeUTF8String.stringU);
			break;
		default:break; //methodRef e methodHandle não implementados
		}

		operandStack->push(tipo);
	};
	operations[0x13] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LDC_W
		(*pc)++;
		uint8_t index1 = *(code + (*pc));
		(*pc)++;
		uint8_t index2 = *(code + (*pc));
		(*pc)++;
		uint16_t index = index1;
		index = (index1 << 8) + index2;
		Cp_Info* cpool = (constant_pool + index - 1);
		Types* tipo;
		switch (cpool->tag) {
		case 3: //int
			tipo = new Types((char*)"I");
			*tipo->basicRef->type_int = cpool->typeInt;
			break;
		case 4: //float
			tipo = new Types((char*)"F");
			*tipo->basicRef->type_float = cpool->typeFloat;
			break;
		case 7: //classRef
		{
			std::string aux = "L";
			cpool = constant_pool + cpool->typeClassInfo - 1;
			char* aux2 = (char*)cpool->typeUTF8String.stringU;
			aux += std::string(aux2);
			tipo = new Types((char*)aux.c_str());
		}
		break;
		case 8: //stringRef
			tipo = new Types((char*)"STRING");
			cpool = constant_pool + cpool->typeStringRef - 1;
			*tipo->stringRef = std::string((char*)cpool->typeUTF8String.stringU);
			break;
		default:break; //methodRef e methodHandle não implementados
		}
		operandStack->push(tipo);
	};
	operations[0x14] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LDC2_W
		(*pc)++;
		uint8_t index1 = *(code + (*pc));
		(*pc)++;
		uint8_t index2 = *(code + (*pc));
		(*pc)++;
		uint16_t index = index1;
		index = (index << 8) + index2;
		Cp_Info* cpool = (constant_pool + index - 1);
		Types* tipo;

		if (cpool->tag == 6) { // double
			tipo = new Types((char*)"D");
			*tipo->basicRef->type_double = cpool->typeDouble;
		}
		else {
			tipo = new Types((char*)"J");
			*tipo->basicRef->type_long = cpool->typeLong;
		}
		operandStack->push(tipo);
	};
	operations[0x15] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ILOAD
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		operandStack->push(locals->at(index));
	};
	operations[0x16] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LLOAD
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		operandStack->push(locals->at(index));
	};
	operations[0x17] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FLOAD
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		operandStack->push(locals->at(index));
	};
	operations[0x18] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DLOAD
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		operandStack->push(locals->at(index));
	};
	operations[0x19] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ALOAD
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		operandStack->push(locals->at(index));

	};
	operations[0x1A] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ILOAD_0
		(*pc)++;
		Types *toAdd = copyTypes(locals->at(0));
		operandStack->push(toAdd);
	};
	operations[0x1B] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ILOAD_1
		(*pc)++;
		Types *toAdd = copyTypes(locals->at(1));
		operandStack->push(toAdd);
	};
	operations[0x1C] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ILOAD_2
		(*pc)++;
		Types *toAdd = copyTypes(locals->at(2));
		operandStack->push(toAdd);
	};
	operations[0x1D] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ILOAD_3
		(*pc)++;
		Types *toAdd = copyTypes(locals->at(3));
		operandStack->push(toAdd);
	};
	operations[0x1E] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LLOAD_0
		(*pc)++;
		operandStack->push(locals->at(0));
	};
	operations[0x1F] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LLOAD_1
		(*pc)++;
		operandStack->push(locals->at(1));
	};
	operations[0x20] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LLOAD_2
		(*pc)++;
		operandStack->push(locals->at(2));
	};
	operations[0x21] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LLOAD_3
		(*pc)++;
		operandStack->push(locals->at(3));
	};
	operations[0x22] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FLOAD_0
		(*pc)++;
		operandStack->push(locals->at(0));
	};
	operations[0x23] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FLOAD_1
		(*pc)++;
		operandStack->push(locals->at(1));
	};
	operations[0x24] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FLOAD_2
		(*pc)++;
		operandStack->push(locals->at(2));
	};
	operations[0x25] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FLOAD_3
		(*pc)++;
		operandStack->push(locals->at(3));
	};
	operations[0x26] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DLOAD_0
		(*pc)++;
		operandStack->push(locals->at(0));
	};
	operations[0x27] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DLOAD_1
		(*pc)++;
		operandStack->push(locals->at(1));
	};
	operations[0x28] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DLOAD_2
		(*pc)++;
		operandStack->push(locals->at(2));
	};
	operations[0x29] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DLOAD_3
		(*pc)++;
		operandStack->push(locals->at(3));
	};
	operations[0x2A] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ALOAD_0
		(*pc)++;
		operandStack->push(locals->at(0));
	};
	operations[0x2B] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ALOAD_1
		(*pc)++;
		operandStack->push(locals->at(1));
	};
	operations[0x2C] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ALOAD_2
		(*pc)++;
		operandStack->push(locals->at(2));
	};
	operations[0x2D] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ALOAD_3
		(*pc)++;
		operandStack->push(locals->at(3));
	};
	operations[0x2E] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// IALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		//std::cout << *arrayR->arrayRef->array->at(*index->basicRef->type_int)->basicRef->type_int << std::endl;
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));

	};
	operations[0x2F] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));
	};
	operations[0x30] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));
	};
	operations[0x31] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));
	};
	operations[0x32] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// AALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));
	};
	operations[0x33] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// BALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));
	};
	operations[0x34] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// CALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));
	};
	operations[0x35] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// SALOAD
		(*pc)++;
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		operandStack->push(arrayR->arrayRef->array->at(*index->basicRef->type_int));
	};
	operations[0x36] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ISTORE
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		Types* value = new Types((char*)"I");
		*value->basicRef->type_int = *operandStack->top()->basicRef->type_int;
		operandStack->pop();
		locals->at(index)= value;
	};
	operations[0x37] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LSTORE
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(index) = value;
	};
	operations[0x38] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FSTORE
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(index) = value;
	};
	operations[0x39] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DSTORE
		(*pc)++;
		uint8_t index = *(code + (*pc));;
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(index) = value;
	};
	operations[0x3A] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ASTORE
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(index) = value;
	};
	operations[0x3B] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ISTORE_0
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(0) = value;
	};
	operations[0x3C] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ISTORE_1
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(1) = value;
	};
	operations[0x3D] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ISTORE_2
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(2) = value;
	};
	operations[0x3E] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ISTORE_3
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(3) = value;
	};
	operations[0x3F] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LSTORE_0
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(0) = value;
	};
	operations[0x40] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LSTORE_1
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(1) = value;
	};
	operations[0x41] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LSTORE_2
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(2) = value;
	};
	operations[0x42] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LSTORE_3
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(3) = value;
	};
	operations[0x43] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FSTORE_0
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(0) = value;
	};
	operations[0x44] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FSTORE_1
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(1) = value;
	};
	operations[0x45] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FSTORE_2
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(2) = value;
	};
	operations[0x46] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FSTORE_3
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(3) = value;
	};
	operations[0x47] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DSTORE_0
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(0) = value;
	};
	operations[0x48] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DSTORE_1
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(1) = value;
	};
	operations[0x49] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DSTORE_2
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(2) = value;
	};
	operations[0x4A] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DSTORE_3
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(3) = value;
	};
	operations[0x4B] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ASTORE_0
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(0) = value;
	};
	operations[0x4C] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ASTORE_1
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(1) = value;
	};
	operations[0x4D] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ASTORE_2
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(2) = value;
	};
	operations[0x4E] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// ASTORE_3
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		locals->at(3) = value;
	};
	operations[0x4F] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// IASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		Types* asuha = new Types((char*)"I");
		*asuha->basicRef->type_int = *value->basicRef->type_int;

		arrayR->arrayRef->array->at(*index->basicRef->type_int) = asuha;
		int a = 0;
		return;
	};
	operations[0x50] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		*arrayR->arrayRef->array->at(*index->basicRef->type_int)->basicRef->type_long = *value->basicRef->type_long;
		int a = 0;
	};
	operations[0x51] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		*arrayR->arrayRef->array->at(*index->basicRef->type_int)->basicRef->type_float = *value->basicRef->type_float;
		int a = 0;
	};
	operations[0x52] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		*arrayR->arrayRef->array->at(*index->basicRef->type_int)->basicRef->type_double = *value->basicRef->type_double;
		int a = 0;
	};
	operations[0x53] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// AASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		arrayR->arrayRef->array->at(*index->basicRef->type_int)->arrayRef->array = value->arrayRef->array;
	};
	operations[0x54] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// BASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		*arrayR->arrayRef->array->at(*index->basicRef->type_int)->basicRef->type_boolean = *value->basicRef->type_boolean;
	};
	operations[0x55] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// CASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		*arrayR->arrayRef->array->at(*index->basicRef->type_int)->basicRef->type_char = *value->basicRef->type_char;
	};
	operations[0x56] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// SASTORE
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* index = operandStack->top();
		operandStack->pop();
		Types* arrayR = operandStack->top();
		operandStack->pop();
		Types* pequeno = new Types((char*)"S");
		*pequeno->basicRef->type_short = (uint16_t)*value->basicRef->type_int;
		*arrayR->arrayRef->array->at(*index->basicRef->type_int)->basicRef->type_short = *pequeno->basicRef->type_short;
	};
	operations[0x57] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// POP
		(*pc)++;
		operandStack->pop();
	};
	operations[0x58] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// POP2
		(*pc)++;
		Types* tipo = operandStack->top();
		operandStack->pop();
		if (tipo->tag != Types::LONG && tipo->tag != Types::DOUBLE) {
			operandStack->pop();
		}
	};
	operations[0x59] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DUP
		(*pc)++;

		Types* value = operandStack->top();

		operandStack->pop();
		operandStack->push(value);
		operandStack->push(value);
		/*
		if (value->tag == Types::DOUBLE || value->tag == Types::LONG) {
			operandStack->push(value);
		}
		else {
			Types* tipo = copyTypes(value);
			operandStack->push(tipo);
			operandStack->push(value);
		}*/
	};
	operations[0x5A] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DUP_X1
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();
		if (value->tag == Types::DOUBLE || value->tag == Types::LONG || value2->tag == Types::DOUBLE || value2->tag == Types::LONG) {
			operandStack->push(value2);
			operandStack->push(value);
		}
		else {
			Types* tipo = copyTypes(value);
			operandStack->push(tipo);
			operandStack->push(value2);
			operandStack->push(value);
		}
	};
	operations[0x5B] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DUP_X2
		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();

		if (value->tag != Types::DOUBLE && value->tag != Types::LONG) {
			if (value2->tag == Types::DOUBLE || value2->tag == Types::LONG) {
				Types* tipo = copyTypes(value);
				operandStack->push(tipo);
				operandStack->push(value2);
				operandStack->push(value);

			}
			else {
				Types* value3 = operandStack->top();
				operandStack->pop();
				if (value3->tag != Types::DOUBLE && value3->tag != Types::LONG) {
					Types* tipo = copyTypes(value);
					operandStack->push(tipo);
					operandStack->push(value3);
					operandStack->push(value2);
					operandStack->push(value);
				}
			}
		}
	};
	operations[0x5C] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DUP2
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		if (value1->tag != Types::DOUBLE && value1->tag != Types::LONG) {
			Types* value2 = operandStack->top();
			operandStack->pop();

			Types* tipo1 = copyTypes(value1);
			Types* tipo2 = copyTypes(value2);

			operandStack->push(tipo2);
			operandStack->push(tipo1);

			operandStack->push(value2);
			operandStack->push(value1);

		}
		else {
			Types* tipo = copyTypes(value1);
			operandStack->push(tipo);
			operandStack->push(value1);
		}
	};
	operations[0x5D] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DUP2_X1
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();

		if (value1->tag != Types::DOUBLE && value1->tag != Types::LONG) {
			Types* value3 = operandStack->top();
			operandStack->pop();

			Types* tipo1 = copyTypes(value1);
			Types* tipo2 = copyTypes(value2);

			operandStack->push(tipo2);
			operandStack->push(tipo1);

			operandStack->push(value3);

			operandStack->push(value2);
			operandStack->push(value1);
		}
		else {
			Types* tipo1 = copyTypes(value1);

			operandStack->push(tipo1);
			operandStack->push(value2);
			operandStack->push(value1);
		}

	};
	operations[0x5E] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DUP2_X2
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();

		Types* tipo1 = copyTypes(value1);
		if (value1->tag != Types::DOUBLE && value1->tag != Types::LONG && value2->tag != Types::DOUBLE && value2->tag != Types::LONG) {
			Types* value3 = operandStack->top();
			operandStack->pop();

			Types* tipo2 = copyTypes(value2);

			if (value3->tag != Types::DOUBLE && value3->tag != Types::LONG) {
				Types* value4 = operandStack->top();
				operandStack->pop();


				operandStack->push(tipo2);
				operandStack->push(tipo1);

				operandStack->push(value4);
				operandStack->push(value3);

				operandStack->push(value2);
				operandStack->push(value1);
			}
			else {

				operandStack->push(tipo2);
				operandStack->push(tipo1);

				operandStack->push(value3);
				operandStack->push(value2);
				operandStack->push(value1);
			}
		}
		else {

			if (value2->tag == Types::DOUBLE || value2->tag == Types::LONG) {
				operandStack->push(tipo1);
				operandStack->push(value2);
				operandStack->push(value1);
			}
			else {
				Types* value3 = operandStack->top();
				operandStack->pop();

				operandStack->push(tipo1);
				operandStack->push(value3);
				operandStack->push(value2);
				operandStack->push(value1);
			}

		}

	};
	operations[0x5F] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// SWAP
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();
		operandStack->push(value1);
		operandStack->push(value2);
	};
	operations[0x60] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// IADD
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value = new Types((char*)"I");
		*value->basicRef->type_int = *value1->basicRef->type_int + *value2->basicRef->type_int;
		operandStack->push(value);
	};
	operations[0x61] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// LADD
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value = new Types((char*)"J");
		*value->basicRef->type_long = *value1->basicRef->type_long + *value2->basicRef->type_long;
		operandStack->push(value);
	};
	operations[0x62] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// FADD
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();
		float float1, float2;
		memcpy(&float1, value1->basicRef->type_float, sizeof(float));
		memcpy(&float2, value2->basicRef->type_float, sizeof(float));
		float1 += float2;
		Types* value = new Types((char*)"F");
		memcpy(value->basicRef->type_float, &float1, sizeof(uint32_t));
		operandStack->push(value);
	};
	operations[0x63] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		// DADD
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();
		Types* value2 = operandStack->top();
		operandStack->pop();
		double double1, double2;
		memcpy(&double1, value1->basicRef->type_double, sizeof(double));
		memcpy(&double2, value2->basicRef->type_double, sizeof(double));
		double1 += double2;
		Types* value = new Types((char*)"D");
		memcpy(value->basicRef->type_double, &double1, sizeof(uint64_t));
		operandStack->push(value);
	};


	/*
	MID POINT
	*/
	//isub
	operations[100] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		Types* result = new Types((char*)"I");

		*result->basicRef->type_int = (*value1->basicRef->type_int - *value2->basicRef->type_int);

		operandStack->push(result);
	};
	//lsub
	operations[101] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = *value1->basicRef->type_long - *value2->basicRef->type_long;

		operandStack->push(result);

	};

	//fsub
	operations[102] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		float fvalue1, fvalue2, fresult;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&fvalue2, value2->basicRef->type_float, sizeof(float));
		memcpy(&fvalue1, value1->basicRef->type_float, sizeof(float));

		fresult = fvalue1 - fvalue2;
		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);
	};

	//dsub
	operations[103] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue1, dvalue2, dresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&dvalue2, value2->basicRef->type_double, sizeof(double));
		memcpy(&dvalue1, value1->basicRef->type_double, sizeof(double));



		dresult = dvalue1 - dvalue2;
		Types* result = new Types((char*)"D");
		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);


	};

	//imul
	operations[104] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		Types* result = new Types((char*)"I");

		*result->basicRef->type_int = (*value1->basicRef->type_int * *value2->basicRef->type_int);

		operandStack->push(result);
	};

	//lmul
	operations[105] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = *value1->basicRef->type_long * *value2->basicRef->type_long;

		operandStack->push(result);

	};
	//fmul
	operations[106] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		float fvalue1, fvalue2, fresult;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&fvalue2, value2->basicRef->type_float, sizeof(float));
		memcpy(&fvalue1, value1->basicRef->type_float, sizeof(float));

		fresult = fvalue1 * fvalue2;
		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);
	};

	//dmul
	operations[107] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue1, dvalue2, dresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&dvalue2, value2->basicRef->type_double, sizeof(double));
		memcpy(&dvalue1, value1->basicRef->type_double, sizeof(double));



		dresult = dvalue1 * dvalue2;
		Types* result = new Types((char*)"D");
		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);

	};

	//idiv
	operations[108] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		Types* result = new Types((char*)"I");

		*result->basicRef->type_int = (*value1->basicRef->type_int / *value2->basicRef->type_int);

		operandStack->push(result);
	};

	//ldiv
	operations[109] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = *value1->basicRef->type_long / *value2->basicRef->type_long;

		operandStack->push(result);

	};

	//fdiv
	operations[110] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		float fvalue1, fvalue2, fresult;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&fvalue2, value2->basicRef->type_float, sizeof(float));
		memcpy(&fvalue1, value1->basicRef->type_float, sizeof(float));

		fresult = fvalue1 / fvalue2;
		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);
	};
	//ddiv
	operations[111] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue1, dvalue2, dresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&dvalue2, value2->basicRef->type_double, sizeof(double));
		memcpy(&dvalue1, value1->basicRef->type_double, sizeof(double));



		dresult = dvalue1 / dvalue2;
		Types* result = new Types((char*)"D");
		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);

	};
	//irem
	operations[112] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		uint32_t ivalue1, ivalue2, iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		iresult = (int32_t)ivalue1 - (ivalue1 / ivalue2) * ivalue2;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;

		operandStack->push(result);
	};
	//lrem
	operations[113] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lvalue2, lresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_long;
		lvalue1 = *value1->basicRef->type_long;

		lresult = lvalue1 - (lvalue1 / lvalue2) * lvalue2;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//frem
	operations[114] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {

		(*pc)++;
		float fvalue1, fvalue2, fresult;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&fvalue2, value2->basicRef->type_float, sizeof(float));
		memcpy(&fvalue1, value1->basicRef->type_float, sizeof(float));
		fresult = fmod(fvalue1, fvalue2);

		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);
	};
	//drem
	operations[115] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue1, dvalue2, dresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&dvalue2, value2->basicRef->type_double, sizeof(double));
		memcpy(&dvalue1, value1->basicRef->type_double, sizeof(double));

		dresult = fmod(dvalue1, dvalue2);

		Types* result = new Types((char*)"D");
		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);

	};
	//ineg
	operations[116] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {


		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();

		Types * result = new Types((char*)"I");
		*result->basicRef->type_int = -(int32_t)*value1->basicRef->type_int;

		operandStack->push(result);
	};
	//lneg
	operations[117] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lresult;
		(*pc)++;
		Types* value1 = operandStack->top();
		operandStack->pop();


		lvalue1 = *value1->basicRef->type_long;

		lresult = -lvalue1;

		Types * result = new Types((char*)"D");
		*result->basicRef->type_long = lresult;
		operandStack->push(result);


	};
	//fneg
	operations[118] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		float fvalue1, fresult;

		Types* value1 = operandStack->top();
		operandStack->pop();


		memcpy(&fvalue1, value1->basicRef->type_float, sizeof(float));

		fresult = -fvalue1;

		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);
	};


	//dneg
	operations[119] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue1, dresult;


		(*pc)++;

		Types* value1 = operandStack->top();
		operandStack->pop();


		memcpy(&dvalue1, value1->basicRef->type_double, sizeof(double));

		dresult = -dvalue1;

		Types* result = new Types((char*)"D");
		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);

	};
	//ishl
	operations[120] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		uint32_t ivalue1, ivalue2, iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		ivalue2 &= 0x0000001f;

		iresult = ivalue1 << ivalue2;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;

		operandStack->push(result);
	};
	//lshl
	operations[121] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lresult;
		uint64_t lvalue2;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_int;
		lvalue1 = *value1->basicRef->type_long;


		lvalue2 &= 0x0000003f;
		lresult = lvalue1 << lvalue2;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//ishr
	operations[122] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		uint32_t ivalue1, ivalue2, iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;



		iresult = (int32_t)(ivalue1 / pow(2, ivalue2));

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;

		operandStack->push(result);
	};
	//lshr
	operations[123] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lresult;
		uint64_t lvalue2;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_int;
		lvalue1 = *value1->basicRef->type_long;

		lresult = (int64_t)(lvalue1 / pow(2, lvalue2 & 0x3f));

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//iushr
	operations[124] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		uint32_t ivalue1, ivalue2, iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;


		ivalue2 &= 0x0000001f;

		iresult = ivalue1 >> ivalue2;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;

		operandStack->push(result);
	};
	//lushr
	operations[125] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lresult;
		uint64_t lvalue2;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_int;
		lvalue1 = *value1->basicRef->type_long;

		lvalue2 &= 0x0000003f;
		lresult = lvalue1 >> lvalue2;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//iand
	operations[126] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2, iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		iresult = ivalue1 & ivalue2;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;

		operandStack->push(result);
	};
	//land
	operations[127] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lvalue2, lresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_long;
		lvalue1 = *value1->basicRef->type_long;

		lresult = lvalue1 & lvalue2;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//ior
	operations[128] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {

		uint32_t ivalue1, ivalue2, iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		iresult = ivalue1 | ivalue2;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;

		operandStack->push(result);
	};
	//lor
	operations[129] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lvalue2, lresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_long;
		lvalue1 = *value1->basicRef->type_long;

		lresult = lvalue1 | lvalue2;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//ixor
	operations[130] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2, iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		iresult = ivalue1 ^ ivalue2;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;

		operandStack->push(result);
	};
	//lxor
	operations[131] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lvalue2, lresult;


		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_long;
		lvalue1 = *value1->basicRef->type_long;

		lresult = lvalue1 ^ lvalue2;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//iinc
	operations[132] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		uint8_t index = *(code + (*pc));
		(*pc)++;
		int8_t consti = *(code + (*pc));
		(*pc)++;
		int32_t inte = ((consti & 0x80) == 0) ? consti : 0x00 | consti;
		//if(consti)
		int base = (int)*(locals->at(index)->basicRef->type_int);
		
		base += inte;
		*locals->at(index)->basicRef->type_int = base;
		
	};
	//i2l
	operations[133] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int64_t lresult;

		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		lresult = (long int)ivalue;



		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);


	};
	//i2f
	operations[134] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		float fresult;

		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		fresult = (float)ivalue;

		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);

	};
	//i2d
	operations[135] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		double dresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;
		dresult = (double)ivalue;

		Types* result = new Types((char*)"D");

		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);

	};
	//l2i
	operations[136] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue;

		int32_t iresult;

		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		lvalue = *value->basicRef->type_long;


		iresult = (int32_t)lvalue;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);
	};

	//l2f
	operations[137] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue;
		float fresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		lvalue = *value->basicRef->type_long;

		fresult = (float)lvalue;

		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);

	};

	//l2d
	operations[138] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue;

		double dresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		lvalue = *value->basicRef->type_long;

		dresult = (double)lvalue;

		Types* result = new Types((char*)"D");
		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);

	};
	//f2i
	operations[139] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		float fvalue;
		uint32_t iresult;

		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		memcpy(&fvalue, value->basicRef->type_float, sizeof(float));

		iresult = (int32_t)fvalue;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);
	};
	//f2l
	operations[140] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		float fvalue;
		uint64_t lresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		memcpy(&fvalue, value->basicRef->type_float, sizeof(float));

		lresult = (int64_t)fvalue;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);

	};
	//f2d
	operations[141] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		float fvalue;
		double dresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		memcpy(&fvalue, value->basicRef->type_float, sizeof(float));

		dresult = (double)fvalue;

		Types* result = new Types((char*)"D");
		memcpy(result->basicRef->type_double, &dresult, sizeof(uint64_t));
		operandStack->push(result);
	};
	//d2i
	operations[142] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue;
		uint32_t iresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		memcpy(&dvalue, value->basicRef->type_double, sizeof(double));


		iresult = (int32_t)dvalue;

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);

	};
	//d2l
	operations[143] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue;
		uint64_t lresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		memcpy(&dvalue, value->basicRef->type_double, sizeof(double));

		lresult = (int64_t)dvalue;

		Types* result = new Types((char*)"J");
		*result->basicRef->type_long = lresult;

		operandStack->push(result);
	};
	//d2f
	operations[144] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue;
		float fresult;


		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		memcpy(&dvalue, value->basicRef->type_double, sizeof(double));

		fresult = (float)dvalue;

		Types* result = new Types((char*)"F");
		memcpy(result->basicRef->type_float, &fresult, sizeof(uint32_t));
		operandStack->push(result);

	};
	//i2b
	operations[145] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int8_t byte;

		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		byte = (int8_t)ivalue;

		Types* result = new Types((char*)"B");
		*result->basicRef->type_byte = (int32_t)byte;
		operandStack->push(result);
	};
	//i2c
	operations[146] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		char chaar;

		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		chaar = (char)ivalue;
		Types* result = new Types((char*)"C");
		*result->basicRef->type_byte = (uint32_t)chaar;
		operandStack->push(result);
	};
	//i2s
	operations[147] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int16_t shorti;

		(*pc)++;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		shorti = (int16_t)ivalue;
		Types* result = new Types((char*)"S");
		*result->basicRef->type_short = (int32_t)shorti;
		operandStack->push(result);
	};
	//lcmp
	operations[148] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int64_t lvalue1, lvalue2;
		int32_t iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();
		lvalue2 = *value2->basicRef->type_long;
		lvalue1 = *value1->basicRef->type_long;

		if (lvalue1>lvalue2) {
			iresult = 1;

		}
		if (lvalue1<lvalue2) {
			iresult = -1;

		}
		if (lvalue1 == lvalue2) {
			iresult = 0;

		}

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);
	};
	//fcmpl
	operations[149] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		float fvalue1, fvalue2;
		uint32_t iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&fvalue2, value2->basicRef->type_float, sizeof(float));
		memcpy(&fvalue1, value1->basicRef->type_float, sizeof(float));

		if (fvalue1>fvalue2) {
			iresult = 1;
		}
		else if (fvalue1 == fvalue2) {
			iresult = 0;
		}
		else if (fvalue1 < fvalue2) {
			iresult = -1;
		}
		else {
			iresult = -1;
		}

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);
	};
	//fcmpg
	operations[150] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		float fvalue1, fvalue2;
		uint32_t iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&fvalue2, value2->basicRef->type_float, sizeof(float));
		memcpy(&fvalue1, value1->basicRef->type_float, sizeof(float));

		if (fvalue1>fvalue2) {
			iresult = 1;
		}
		else if (fvalue1 == fvalue2) {
			iresult = 0;
		}
		else if (fvalue1 < fvalue2) {
			iresult = -1;
		}
		else {
			iresult = 1;
		}

		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);
	};
	//dcmpl
	operations[151] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue1, dvalue2;
		uint32_t iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&dvalue2, value2->basicRef->type_double, sizeof(double));
		memcpy(&dvalue1, value1->basicRef->type_double, sizeof(double));

		if (dvalue1>dvalue2) {
			iresult = 1;
		}
		else if (dvalue1 == dvalue2) {
			iresult = 0;
		}
		else if (dvalue1 < dvalue2) {
			iresult = -1;
		}
		else {
			iresult = -1;
		}
		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);
	};
	//dcmpg
	operations[152] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		double dvalue1, dvalue2;
		uint32_t iresult;

		(*pc)++;
		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		memcpy(&dvalue2, value2->basicRef->type_double, sizeof(double));
		memcpy(&dvalue1, value1->basicRef->type_double, sizeof(double));

		if (dvalue1>dvalue2) {
			iresult = 1;
		}
		else if (dvalue1 == dvalue2) {
			iresult = 0;
		}
		else if (dvalue1 < dvalue2) {
			iresult = -1;
		}
		else {
			iresult = 1;
		}
		Types* result = new Types((char*)"I");
		*result->basicRef->type_int = iresult;
		operandStack->push(result);
	};
	//ifeq
	operations[153] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int16_t  offset = 0;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		if (ivalue == 0) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//ifne
	operations[154] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int16_t  offset = 0;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		if (ivalue != 0) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//iflt
	operations[155] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int16_t  offset = 0;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		if (ivalue < 0) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//ifle
	operations[158] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int16_t  offset = 0;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;



		if (ivalue <= 0) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//ifgt
	operations[157] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int16_t  offset = 0;
		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		if (ivalue > 0) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//ifge
	operations[156] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue;
		int16_t  offset = 0;

		Types* value = operandStack->top();
		operandStack->pop();
		ivalue = *value->basicRef->type_int;

		if (ivalue >= 0) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//if_icmpeq
	operations[159] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2;
		int16_t  offset = 0;

		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		if (ivalue1 == ivalue2) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//if_icmpne
	operations[160] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2;
		int16_t  offset = 0;

		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		if (ivalue1 != ivalue2) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//if_icmplt
	operations[161] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2;
		int16_t  offset = 0;

		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		if (ivalue1 < ivalue2) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//if_icmple
	operations[164] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2;
		int16_t  offset = 0;

		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		if (ivalue1 <= ivalue2) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//if_icmpgt
	operations[163] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2;
		int16_t  offset = 0;

		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		if (ivalue1 > ivalue2) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//if_icmpge
	operations[162] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int32_t ivalue1, ivalue2;
		int16_t  offset = 0;

		Types* value2 = operandStack->top();
		operandStack->pop();
		Types* value1 = operandStack->top();
		operandStack->pop();

		ivalue2 = *value2->basicRef->type_int;
		ivalue1 = *value1->basicRef->type_int;

		if (ivalue1 >= ivalue2) {

			offset = *(code + (*pc + 1));
			offset <<= 8;
			offset |= *(code + (*pc + 2));

			(*pc) += offset;

		}
		else {
			(*pc) += 3;
		}
	};
	//if_acmpeq
	operations[165] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		Types* value2, *value1;
		int16_t branch = (int16_t)(((*(pc + 1)) << 8) + (*(pc + 2)));

		value2 = operandStack->top();
		operandStack->pop();
		value1 = operandStack->top();
		operandStack->pop();

		if (value2->classInstance == value1->classInstance) {
			*pc += (int32_t)branch;
		}
	};
	//if_acmpne
	operations[166] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		Types* value2, *value1;
		int16_t branch = (int16_t)(((*(pc + 1)) << 8) + (*(pc + 2)));

		value2 = operandStack->top();
		operandStack->pop();
		value1 = operandStack->top();
		operandStack->pop();

		if (value2->classInstance != value1->classInstance) {
			*pc += (int32_t)branch;
		}
		else {
			*pc += 3;
		}
	};
	//goto
	operations[167] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int16_t  offset = 0;

		offset = *(code + (*pc + 1));
		offset <<= 8;
		offset |= *(code + (*pc + 2));

		(*pc) += offset;
	};
	//jsr
	operations[168] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		int16_t offset = 0;
		Types* address = new Types((char*)"RA");
		*address->returnAddress = (*pc) + 3;
		operandStack->push(address);

		offset = *(code + (*pc + 1));
		offset <<= 8;
		offset |= *(code + (*pc + 2));

		(*pc) += offset;
	};
	//ret
	operations[169] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		uint16_t index = (uint8_t)*(code + (*pc + 1));

		(*pc) = *(locals->at(index)->returnAddress);// type int usado como type  returnAddress
	};
	//tableswitch
	operations[170] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		uint32_t defaultbyte = 0;
		uint32_t lowbyte = 0;
		uint32_t highbyte = 0;
		uint32_t *jump_offsets;
		uint32_t index;
		Types* value1 = operandStack->top();
		operandStack->pop();
		index = *value1->basicRef->type_int;
		uint32_t start = *(pc);
		(*pc)++;

		while ((*pc) % 4 != 0) {
			(*pc)++;
		}

		defaultbyte = code[(*pc)++];
		defaultbyte = (defaultbyte << 8) + code[(*pc)++];
		defaultbyte = (defaultbyte << 8) + code[(*pc)++];
		defaultbyte = (defaultbyte << 8) + code[(*pc)++];

		lowbyte = code[(*pc)++];
		lowbyte = (lowbyte << 8) + code[(*pc)++];
		lowbyte = (lowbyte << 8) + code[(*pc)++];
		lowbyte = (lowbyte << 8) + code[(*pc)++];

		highbyte = code[(*pc)++];
		highbyte = (highbyte << 8) + code[(*pc)++];
		highbyte = (highbyte << 8) + code[(*pc)++];
		highbyte = (highbyte << 8) + code[(*pc)++];

		jump_offsets = (uint32_t*)malloc((highbyte - lowbyte + 1) * sizeof(uint32_t));

		for (int i = 0; i < (int)(highbyte - lowbyte + 1); i++) {
			jump_offsets[i] = code[(*pc)++];
			jump_offsets[i] = (jump_offsets[i] << 8) + code[(*pc)++];
			jump_offsets[i] = (jump_offsets[i] << 8) + code[(*pc)++];
			jump_offsets[i] = (jump_offsets[i] << 8) + code[(*pc)++];
		}

		if ((int32_t)index < (int32_t)lowbyte || (int32_t)index >(int32_t)highbyte) {
			(*pc) = start + (int32_t)defaultbyte;
		}
		else {
			(*pc) = start + (int32_t)jump_offsets[index - lowbyte];
		}
	};

	operations[171] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//LOOKUPSWITCH ACESS JUMP TABLE BY KEY AND JUMP
		uint32_t defaultbyte = 0;
		uint32_t npairs = 0;
		uint32_t *jump_keys;
		uint32_t *jump_offsets;
		uint32_t key;
		uint32_t start = *pc;

		Types* value1 = operandStack->top();
		operandStack->pop();
		key = *value1->basicRef->type_int;
		(*pc)++;

		while ((*pc) % 4 != 0) {
			(*pc)++;
		}

		defaultbyte = code[(*pc)++];
		defaultbyte = (defaultbyte << 8) + code[(*pc)++];
		defaultbyte = (defaultbyte << 8) + code[(*pc)++];
		defaultbyte = (defaultbyte << 8) + code[(*pc)++];

		npairs = code[(*pc)++];
		npairs = (npairs << 8) + code[(*pc)++];
		npairs = (npairs << 8) + code[(*pc)++];
		npairs = (npairs << 8) + code[(*pc)++];

		jump_keys = (uint32_t*)malloc(npairs * sizeof(uint32_t));
		jump_offsets = (uint32_t*)malloc(npairs * sizeof(uint32_t));
		for (int i = 0; i < (int)npairs; i++) {
			jump_keys[i] = code[(*pc)++];
			jump_keys[i] = (jump_keys[i] << 8) + code[(*pc)++];
			jump_keys[i] = (jump_keys[i] << 8) + code[(*pc)++];
			jump_keys[i] = (jump_keys[i] << 8) + code[(*pc)++];

			jump_offsets[i] = code[(*pc)++];
			jump_offsets[i] = (jump_offsets[i] << 8) + code[(*pc)++];
			jump_offsets[i] = (jump_offsets[i] << 8) + code[(*pc)++];
			jump_offsets[i] = (jump_offsets[i] << 8) + code[(*pc)++];
		}

		int i;
		for (i = 0; i < (int)npairs; ++i) {
			if (jump_keys[i] == key) {
				*(pc) = start + jump_offsets[i];
				break;
			}
		}
		if (i == npairs)
			*(pc) = start + defaultbyte;
	};

	operations[172] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//IRETURN
		(*pc)++;
		Types* returnValue;

		returnValue = operandStack->top();
		Interpreter::GetInstance()->PopFrame();
		Interpreter::GetInstance()->GetTopFrame()->PushOperandStack(returnValue);
	};

	operations[173] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//LRETURN
		(*pc)++;
		Types* returnValue;

		returnValue = operandStack->top();
		operandStack->pop();
		Interpreter::GetInstance()->PopFrame();
		Interpreter::GetInstance()->GetTopFrame()->PushOperandStack(returnValue);
	};

	operations[174] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//FRETURN
		(*pc)++;
		Types* returnValue;

		returnValue = operandStack->top();
		Interpreter::GetInstance()->PopFrame();
		Interpreter::GetInstance()->GetTopFrame()->PushOperandStack(returnValue);
	};

	operations[175] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//DRETURN
		(*pc)++;
		Types* returnValue;

		returnValue = operandStack->top();
		operandStack->pop();

		Interpreter::GetInstance()->PopFrame();

		Interpreter::GetInstance()->GetTopFrame()->PushOperandStack(returnValue);
	};

	operations[176] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//ARETURN
		(*pc)++;
		Types* returnValue;

		returnValue = operandStack->top();

		Interpreter::GetInstance()->PopFrame();
		Interpreter::GetInstance()->GetTopFrame()->PushOperandStack(returnValue);
	};

	operations[177] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//RET
		(*pc)++;
		Interpreter::GetInstance()->PopFrame();
	};

	operations[178] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//GETSTATIC
		(*pc)++;
		uint16_t index = code[(*pc)++];
		index = (index << 8) + code[(*pc)++];

		uint16_t className = constant_pool[index - 1].typeFieldRef >> 16;
		className = constant_pool[className - 1].typeClassInfo;

		uint16_t fieldName = constant_pool[index - 1].typeFieldRef;
		fieldName = constant_pool[fieldName - 1].typeNameAndType >> 16;

		uint16_t fieldType = constant_pool[index - 1].typeFieldRef;
		fieldType = constant_pool[fieldType - 1].typeNameAndType;

		Types* fieldVar;

		if (!strcmp((char*)constant_pool[className - 1].typeUTF8String.stringU, "java/lang/System"))
			return;

		ClassInfo *classInfo = Interpreter::GetInstance()->GetClass((char*)constant_pool[className - 1].typeUTF8String.stringU);
		fieldVar = Interpreter::GetInstance()->GetStaticField((char*)constant_pool[className - 1].typeUTF8String.stringU,
			(char*)constant_pool[fieldName - 1].typeUTF8String.stringU);

		operandStack->push(fieldVar);
	};

	operations[179] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//PUTSTATIC
		(*pc)++;
		Types* var;
		uint16_t index = code[(*pc)++];
		index = (index << 8) + code[(*pc)++];

		uint16_t className = constant_pool[index - 1].typeFieldRef >> 16;
		className = constant_pool[className - 1].typeClassInfo;

		uint16_t fieldName = constant_pool[index - 1].typeFieldRef;
		fieldName = constant_pool[fieldName - 1].typeNameAndType >> 16;

		uint16_t fieldType = constant_pool[index - 1].typeFieldRef;
		fieldType = constant_pool[fieldType - 1].typeNameAndType;

		Types* fieldVar;

		ClassInfo *classInfo = Interpreter::GetInstance()->GetClass((char*)constant_pool[className - 1].typeUTF8String.stringU);
		fieldVar = Interpreter::GetInstance()->GetStaticField((char*)constant_pool[className - 1].typeUTF8String.stringU,
			(char*)constant_pool[fieldName - 1].typeUTF8String.stringU);

		switch (fieldVar->tag) {
		case Types::INT:
			var = operandStack->top();
			operandStack->pop();
			*fieldVar->basicRef->type_int = *var->basicRef->type_int;
			break;
		case Types::FLOAT:
			var = operandStack->top();
			operandStack->pop();
			*fieldVar->basicRef->type_float = *var->basicRef->type_float;
			break;
		case Types::SHORT:
			var = operandStack->top();
			operandStack->pop();
			(*fieldVar->basicRef->type_short) = *var->basicRef->type_short;
			break;
		case Types::BOOL:
			var = operandStack->top();
			operandStack->pop();
			(*fieldVar->basicRef->type_boolean) = *var->basicRef->type_boolean;
			break;
		case Types::CHAR:
			var = operandStack->top();
			(*fieldVar->basicRef->type_char) = *var->basicRef->type_char;
			operandStack->pop();
			break;
		case Types::CLASSINSTANCE:
			var = operandStack->top();
			operandStack->pop();
			(fieldVar->classInstance) = var->classInstance;
			break;
		case Types::ARRAY:
			var = operandStack->top();
			operandStack->pop();
			(fieldVar->arrayRef) = var->arrayRef;
			break;
		case Types::DOUBLE:
			var = operandStack->top();
			*fieldVar->basicRef->type_double = *var->basicRef->type_double;
			break;
		case Types::LONG:
		{
			var = operandStack->top();
			operandStack->pop();
			*fieldVar->basicRef->type_long = *var->basicRef->type_long;
		}
		break;
		}
	};

	operations[180] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//GETFIELD
		(*pc)++;
		uint16_t index = code[(*pc)++];
		index = (index << 8) + code[(*pc)++];

		uint16_t className = constant_pool[index - 1].typeFieldRef >> 16;
		className = constant_pool[className - 1].typeClassInfo;

		uint16_t fieldName = constant_pool[index - 1].typeFieldRef;
		fieldName = constant_pool[fieldName - 1].typeNameAndType >> 16;

		uint16_t fieldType = constant_pool[index - 1].typeFieldRef;
		fieldType = constant_pool[fieldType - 1].typeNameAndType;

		Types* fieldVar;
		Types* var = (Types*)operandStack->top();

		//Interpreter::GetInstance()->GetClass((char*)constant_pool[className - 1].typeUTF8String.stringU);
		std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);

		fieldVar = thisClass->fieldVars->at(key);

		operandStack->push(fieldVar);
	};

	operations[181] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//PUTFIELD
		(*pc)++;
		Types* var;
		uint16_t index = code[(*pc)++];
		index = (index << 8) + code[(*pc)++];

		uint16_t className = constant_pool[index - 1].typeFieldRef >> 16;
		className = constant_pool[className - 1].typeClassInfo;

		uint16_t fieldName = constant_pool[index - 1].typeFieldRef;
		fieldName = constant_pool[fieldName - 1].typeNameAndType >> 16;

		uint16_t fieldType = constant_pool[index - 1].typeFieldRef;
		fieldType = constant_pool[fieldType - 1].typeNameAndType;

		Types* fieldVar = new Types((char*)constant_pool[fieldType - 1].typeUTF8String.stringU);

		Types::TAGTYPE type = fieldVar->tag;

		//ClassInfo *classInfo = Interpreter::GetInstance()->GetClass((char*)constant_pool[className - 1].typeUTF8String.stringU);

		switch (type) {
		case Types::INT:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			//fieldVar = /*(*objectref->classInstance->fieldVars)*/[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			*fieldVar->basicRef->type_int = *var->basicRef->type_int;
		}
		break;
		case Types::FLOAT:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			*fieldVar->basicRef->type_float = *var->basicRef->type_float;
		}
		break;
		case Types::SHORT:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			(*fieldVar->basicRef->type_short) = *var->basicRef->type_short;
		}
		break;
		case Types::BOOL:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			(*fieldVar->basicRef->type_boolean) = *var->basicRef->type_boolean;
		}
		break;
		case Types::CHAR:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			(*fieldVar->basicRef->type_char) = *var->basicRef->type_char;

		}
		break;
		case Types::CLASSINSTANCE:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			(fieldVar->classInstance) = (ClassInstance*)var->classInstance;
		}
		break;
		case Types::ARRAY:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			(fieldVar->arrayRef) = (ArrayType*)var->arrayRef;
		}
		break;
		case Types::DOUBLE:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			*fieldVar->basicRef->type_double = *var->basicRef->type_double;
		}
		break;
		case Types::LONG:
		{
			var = operandStack->top();
			operandStack->pop();
			Types* objectref = (Types*)operandStack->top();
			operandStack->pop();
			std::string key((char*)constant_pool[fieldName - 1].typeUTF8String.stringU);
			fieldVar = thisClass->fieldVars->at(key);
			//fieldVar = (*objectref->classInstance->fieldVars)[(char*)constant_pool[className - 1].typeUTF8String.stringU];
			*fieldVar->basicRef->type_long = *var->basicRef->type_long;
		}
		break;
		}
	};

	operations[182] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//INVOKEVIRTUAL BOYS

		uint16_t methodIndex = code[++(*pc)];
		methodIndex = (methodIndex << 8) | code[++(*pc)];
		(*pc)++;

		Cp_Info* methodRef = &constant_pool[methodIndex - 1];

		uint16_t classNameIndex = constant_pool[(uint16_t)((methodRef->typeMethodRef) >> 16) - 1].typeClassInfo;
		std::string className((char*)constant_pool[classNameIndex - 1].typeUTF8String.stringU);

		uint16_t nameAndTypeIndex = (uint16_t)methodRef->typeMethodRef;
		Cp_Info* nameAndType = &constant_pool[nameAndTypeIndex - 1];

		std::string methodName = (char*)constant_pool[(uint16_t)((nameAndType->typeNameAndType) >> 16) - 1].typeUTF8String.stringU;
		std::string methodDescriptor = (char*)constant_pool[(uint16_t)(nameAndType->typeNameAndType) - 1].typeUTF8String.stringU;

		
		if (strstr(className.c_str(), "java/")) {
			// Call of print or println
			if (className == "java/io/PrintStream" && (methodName == "print" || methodName == "println")) {
				if (methodDescriptor != "()V") {
					Types* streamRef = operandStack->top();
					operandStack->pop();
					float a = 2;
					switch (streamRef->tag) {
					case(Types::STRING):
						std::cout << *streamRef->stringRef;
						break;
					case(Types::ARRAY):
						std::cout << streamRef->arrayRef;
						break;
					case(Types::BOOL):
						std::cout << (bool)*streamRef->basicRef->type_boolean;
						break;
					case(Types::BYTE):
						std::cout << *streamRef->basicRef->type_byte;
						break;
					case (Types::CHAR):
						std::cout << (char)*streamRef->basicRef->type_char;
						break;
					case(Types::CLASSINSTANCE):
						std::cout << streamRef->classInstance;
						break;
					case(Types::DOUBLE):
					{
						double aux;
						memcpy(&aux, streamRef->basicRef->type_double, sizeof(double));
						printf("%.15lf", (double)aux);
					}
					break;
					case (Types::FLOAT):
					{
						float aux;
						memcpy(&aux, streamRef->basicRef->type_float, sizeof(float));
						printf("%f",(float)aux);
					}
					break;
					case (Types::INT):
						std::cout << (int32_t)*streamRef->basicRef->type_int;
						break;
					case(Types::LONG):
						std::cout << (int64_t)*streamRef->basicRef->type_long;
						break;
					case(Types::SHORT):
						std::cout << *streamRef->basicRef->type_short;
						break;
					}
				}
				if (methodName == "println") {
					std::cout << std::endl;
				}
			}
			else if (className == "java/lang/String" && methodName == "equals") {
				Types* ref1, *ref2;
				ref2 = operandStack->top();
				operandStack->pop();
				ref1 = operandStack->top();
				operandStack->pop();

				if (!strcmp(ref1->stringRef->c_str(), ref2->stringRef->c_str())) {
					Types* toReturn = new Types((char*)"Z");
					*toReturn->basicRef->type_boolean = 1;
					operandStack->push(toReturn);
				}
				else {
					Types* toReturn = new Types((char*)"Z");
					*toReturn->basicRef->type_boolean = 0;
					operandStack->push(toReturn);
				}
			}
			else if (className == "java/lang/String" && methodName == "length") {
				Types* ref1 = operandStack->top();

				Types* toAdd = new Types((char*)"I");
				*toAdd->basicRef->type_int = ref1->stringRef->size();
				operandStack->pop();
				operandStack->push(toAdd);
			}
			else if (className == "java/lang/StringBuilder" && methodName == "append") {
				Types* reftoAppend = operandStack->top();
				operandStack->pop();
				Types* refToString = operandStack->top();
				operandStack->pop();
				std::stringstream toAppend;
				switch (reftoAppend->tag) {
				case(Types::STRING):
					toAppend << *reftoAppend->stringRef;
					break;
				case(Types::ARRAY):
					toAppend << reftoAppend->arrayRef;
					break;
				case(Types::BOOL):
					toAppend << *reftoAppend->basicRef->type_boolean;
					break;
				case(Types::BYTE):
					toAppend << *reftoAppend->basicRef->type_byte;
					break;
				case (Types::CHAR):
					toAppend << *reftoAppend->basicRef->type_char;
					break;
				case(Types::CLASSINSTANCE):
					toAppend << reftoAppend->classInstance;
					break;
				case(Types::DOUBLE):
				{
					double aux;
					memcpy(&aux, reftoAppend->basicRef->type_double, sizeof(double));
					toAppend << aux;
				}
				break;
				case (Types::FLOAT):
				{
					float aux;
					memcpy(&aux, reftoAppend->basicRef->type_float, sizeof(float));
					toAppend << aux;
				}
				break;
				case (Types::INT):
					toAppend << (int32_t)*reftoAppend->basicRef->type_int;
					break;
				case(Types::LONG):
					toAppend << (int64_t)*reftoAppend->basicRef->type_long;
					break;
				case(Types::SHORT):
					toAppend << *reftoAppend->basicRef->type_short;
					break;
				}

				refToString->stringRef->append(toAppend.str());
				operandStack->push(refToString);
			}
			else if (className == "java/lang/StringBuilder") {
				return;
			}
			else {
				std::cout<< methodName << "Nao implementado nesta JVM"<< std::endl;
				exit(1);
			}
		}
		else {
			uint16_t nargs = 0; 
			uint16_t i = 1;
			while (methodDescriptor[i] != ')') {
				char baseType = methodDescriptor[i];
				if (baseType == 'L') {
					nargs++;
					while (methodDescriptor[++i] != ';');
				}
				else if (baseType == '[') {
					nargs++;
					while (methodDescriptor[++i] == '[');
					if (methodDescriptor[i] == 'L') 
						while (methodDescriptor[++i] != ';');
				}
				else {
					nargs++;
				}
				i++;
			}

			std::vector<Types*> arguments;
			for (int i = 0; i < nargs; i++) {
				Types* value = operandStack->top();
				operandStack->pop();
				arguments.insert(arguments.begin(), value);
				if (value->tag == Types::DOUBLE || value->tag == Types::LONG)
					arguments.insert(arguments.begin() + 1, new Types());
			}

			Types* objectValue = operandStack->top();
			arguments.insert(arguments.begin(), objectValue);

			operandStack->pop();

			//Receives cInfo from Classes' map, constantPool from the current class, method index from code attribute, cInstance as current class instance and a vector of method's arguments
			Frame* nextFrame = new Frame(objectValue->classInstance->classDescription, constant_pool, nameAndTypeIndex, objectValue->classInstance, &arguments);


				// se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
				Interpreter::GetInstance()->PushFrame(nextFrame);
			}
	};

	operations[183] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//InvokeSpecial

		uint16_t methodIndex = code[++(*pc)];
		methodIndex = (methodIndex<<8) | code[++(*pc)];
		(*pc)++;

		Cp_Info* methodRef = &constant_pool[methodIndex - 1];
		
		uint16_t classNameIndex = constant_pool[(uint16_t)((methodRef->typeMethodRef) >> 16) - 1].typeClassInfo;
		std::string className((char*)constant_pool[classNameIndex - 1].typeUTF8String.stringU);

		uint16_t nameAndTypeIndex = (uint16_t)methodRef->typeMethodRef;
		Cp_Info* nameAndType = &constant_pool[nameAndTypeIndex - 1];

		std::string methodName = (char*)constant_pool[(uint16_t)((nameAndType->typeNameAndType)>>16) - 1].typeUTF8String.stringU;
		std::string methodDescriptor = (char*)constant_pool[(uint16_t)(nameAndType->typeNameAndType) - 1].typeUTF8String.stringU;

		// Caso de Object<init>, String<init>, StringBuilder<init>
		if ((className == "java/lang/Object" || className == "java/lang/String") && methodName == "<init>" ||
			(className == "java/lang/StringBuilder" && methodName == "<init>")) {
			if (className == "java/lang/String" || className == "java/lang/StringBuilder") {
				operandStack->pop();
			}
			else if(methodName == "<init>"){
				CreateFieldVars(locals->at(0)->classInstance);
			}
			return;
		}
		//Caso forem outras classes do java nao implementadas aqui
		if (strstr(className.c_str(), (char*)"java/") != NULL){
			std::cout << className << " Nao implementada!\n";
			exit(1);
		}
		else {
			uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
			uint16_t index = 1;
			while (methodDescriptor[index] != ')') {
				char baseType = methodDescriptor[index];
				//Argumento do tipo objeto
				if (baseType == 'L') {
					nargs++;
					while (methodDescriptor[++index] != ';');
				}
				//Argumento do tipo array
				else if (baseType == '[') {
					nargs++;
					while (methodDescriptor[++index] == '[');
					if (methodDescriptor[index] == 'L')
						while (methodDescriptor[++index] != ';');
				}
				else {
					nargs++;
				}
				index++;
			}

			std::vector<Types*> args;
			for (int i = 0; i < nargs; i++) {
				Types* value = operandStack->top();
				operandStack->pop();
				args.insert(args.begin(), value);
				if (value->tag == Types::DOUBLE || value->tag == Types::LONG)
					args.insert(args.begin() +1, new Types());
			}

			//Adicionar objectref pro inicio dos argumentos
			Types* objectValue = operandStack->top();
			operandStack->pop();
			args.insert(args.begin(), objectValue);

			ClassInstance *object = objectValue->classInstance;
			Frame* nextFrame = new Frame(objectValue->classInstance->classDescription, constant_pool,nameAndTypeIndex, object, &args);
			Interpreter::GetInstance()->PushFrame(nextFrame);
		}
	}; 
	operations[184] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		//INVOKE STATIC
		uint16_t methodIndex = code[++(*pc)];
		methodIndex = (methodIndex << 8) | code[++(*pc)];
		(*pc)++;

		Cp_Info* methodRef = &constant_pool[methodIndex - 1];

		uint16_t classNameIndex = constant_pool[(uint16_t)((methodRef->typeMethodRef) >> 16) - 1].typeClassInfo;
		std::string className((char*)constant_pool[classNameIndex - 1].typeUTF8String.stringU);

		uint16_t nameAndTypeIndex = (uint16_t)methodRef->typeMethodRef;
		Cp_Info* nameAndType = &constant_pool[nameAndTypeIndex - 1];

		std::string methodName = (char*)constant_pool[(uint16_t)((nameAndType->typeNameAndType) >> 16) - 1].typeUTF8String.stringU;
		std::string methodDescriptor = (char*)constant_pool[(uint16_t)(nameAndType->typeNameAndType) - 1].typeUTF8String.stringU;

		if (className == "java/lang/Object" && methodName == "registerNatives") {
			//nao trabalhar com codigo nativo
			return;
		}

		if (className.find("java/") != std::string::npos) {
			//se for alguma classe do java nao implementada aqui
			exit(1);
		}
		else {
			uint16_t nargs = 0; 
			uint16_t i = 1;
			while (methodDescriptor[i] != ')') {
				char baseType = methodDescriptor[i];
				if (baseType == 'L') {
					nargs++;
					while (methodDescriptor[++i] != ';');
				}
				else if (baseType == '[') {
					nargs++;
					while (methodDescriptor[++i] == '[');
					if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
				}
				else {
					nargs++;
				}
				i++;
			}

			std::vector<Types*> args;
			for (int i = 0; i < nargs; i++) {
				Types* value = operandStack->top();
				operandStack->pop();
				args.insert(args.begin(), value);
				if (value->tag == Types::DOUBLE || value->tag == Types::LONG)
					args.insert(args.begin()+1, new Types());
			}

			ClassInstance* staticInstance = Interpreter::GetInstance()->GetStaticInstance(className.c_str());

			Frame* nextFrame = new Frame(staticInstance->classDescription, constant_pool, nameAndTypeIndex, staticInstance, &args);
			Interpreter::GetInstance()->PushFrame(nextFrame);
		}
	};

	//new
	operations[187] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {

		uint16_t indexByte1 = code[(*pc) + 1];
		uint16_t indexByte2 = code[(*pc) + 2];
		uint16_t index = (indexByte1 << 8) | indexByte2;

		uint16_t classRef = constant_pool[index - 1].typeClassInfo;
		char* className = (char*)constant_pool[classRef - 1].typeUTF8String.stringU;
		std::string loko("L");
		loko += className;


		if (!strcmp(className, "java/lang/StringBuilder")) {
			Types* toAdd = new Types((char*)"STRING");
			operandStack->push(toAdd);
			(*pc) += 3;
			return;
		}

		loko += ";";

		Types* tipo = new Types((char*)loko.c_str());
		if (tipo->classInstance->classDescription == NULL)
			Interpreter::GetInstance()->PushException((char*)"Link Error!");

		operandStack->push(tipo);
		(*pc) += 3;
		return;
	};
	//newarray
	operations[188] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		Types* value = operandStack->top();
		uint32_t counter = *value->basicRef->type_int;
		operandStack->pop();
		(*pc)++;
		std::string loko = "[";
		Types* tipo = new Types((char*)loko.c_str());
		Types* toAdd;
		uint8_t atype = code[(*pc)++];
		switch (atype) {
		case 4: //T_BOOLEAN
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)"B"));
			}
			break;

		case 5: //T_CHAR
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)"C"));
			}
			break;

		case 6: //T_FLOAT
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)"F"));
			}
			break;

		case 7: //T_DOUBLE
			for (int i = 0; i<(int)counter; i++) {
				toAdd = new Types((char*)"D");
				tipo->arrayRef->array->emplace_back(toAdd);
			}
			break;

		case 8: //T_BYTE
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)"Z"));
			}
			break;

		case 9: // T_SHORT
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)"S"));
			}
			break;

		case 10: // T_INT
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)"I"));
			}
			break;

		case 11: // T_LONG
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)"J"));
			}
			break;

		}

		operandStack->push(tipo);
	
	};
	//anewarray
	operations[189] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		Types* value = operandStack->top();
		uint32_t counter = *value->basicRef->type_int;
		operandStack->pop();
		(*pc)++;

		Types* tipo = 0;

		uint16_t indexByte1 = code[(*pc)++];
		uint16_t indexByte2 = code[(*pc)++];
		uint16_t index = (indexByte1 << 8) | indexByte2;

		uint8_t tag = constant_pool[index - 1].tag;

		uint16_t classRef;
		char* className;
		std::string loko;

		classRef = constant_pool[index - 1].typeClassInfo;
		className = (char*)constant_pool[classRef - 1].typeUTF8String.stringU;
		loko = "L";
		loko += className;
		loko += ";";
		tipo = new Types((char*)loko.c_str());

		switch (tag) {
		case 7: //class
				//nao e tratado string diferentemente pois nao existe tipo basico.
			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)loko.c_str()));
			}

			break;
		case 11: //intarface

			for (int i = 0; i<(int)counter; i++) {
				tipo->arrayRef->array->emplace_back(new Types((char*)loko.c_str()));
			}
			break;
		}
		operandStack->push(tipo);
	};


	//multianewarray
	operations[197] = [](uint8_t* code, uint32_t* pc, std::stack<Types*>* operandStack, std::vector<Types*>* locals, Cp_Info* constant_pool, ClassInstance* thisClass) {
		(*pc)++;
		Types* tipo = 0;

		uint16_t indexByte1 = code[(*pc)++];
		uint16_t indexByte2 = code[(*pc)++];
		uint16_t index = (indexByte1 << 8) | indexByte2;

		uint8_t tag = constant_pool[index - 1].tag;
		uint8_t dimension = code[(*pc)++];
		uint16_t classRef;

		std::stack<int> counter;

		for (uint8_t i = 0; i<dimension; i++) {
			Types* value = operandStack->top();
			counter.push(*value->basicRef->type_int);
			operandStack->pop();
		}

		classRef = constant_pool[index - 1].typeClassInfo;
		std::string loko((char*)constant_pool[classRef - 1].typeUTF8String.stringU + dimension);

		Types* aux = new Types((char*)"[");

		CreateMultiArray(aux->arrayRef, loko, counter);

		operandStack->push(aux);
	};

}

void CreateMultiArray(ArrayType* array, std::string type, std::stack<int> counter) {
	int c = counter.top();
	counter.pop();

	if (counter.size() == 0) {
		for (int i = 0; i < c; i++) {
			Types* toAdd = new Types((char*)type.c_str());
			array->array->emplace_back(toAdd);
		}
	}
	else {
		for (int i = 0; i < c; i++) {
			Types* toAdd = new Types((char*)"[");
			CreateMultiArray(toAdd->arrayRef, type, counter);
			array->array->emplace_back(toAdd);
		}
	}
}

void Frame::Execute(){
	//std::cout<<current_pc<<" "<<(int)codeAttribute->code[current_pc]<<std::endl;
	operations[*(codeAttribute->code + current_pc)](codeAttribute->code, &current_pc, &operandStack, &locals, classInfo->constant_pool, thisClass);
}

//Receives cInfo from Classes' map, constantPool from the current class, method index from code attribute, cInstance as current class instance and a vector of method's arguments
Frame::Frame(ClassInfo* cInfo, Cp_Info* constantPool, uint16_t methodIndex, ClassInstance* cInstance, std::vector<Types*>* args){
	//methodNaT is a reference to the method's name and type
	Cp_Info* methodNaT = (constantPool + methodIndex - 1);
	
	exceptionsAttribute = NULL;
	current_pc = 0;
	
	//Get method's name and return type char* ref1
	char* methodName = (char*)(constantPool[(methodNaT->typeNameAndType>>16) - 1].typeUTF8String.stringU);
	char* methodType = (char*)(constantPool[((methodNaT->typeNameAndType<<16)>>16) - 1].typeUTF8String.stringU);
	
	//Set up classes vars
	classInfo = cInfo;

	/* TESTE CIRACAO DE FIELDS
	FIELDS SAO CRIADOS NO OBJECT<INIT>
	this->thisClass = (ClassInstance*)malloc(sizeof(ClassInstance));
	this->thisClass->classDescription = cInfo;
	CreateFieldVars(thisClass);*/


	//Find method in class
	for(method_index = 0; method_index < cInfo->methods_count; ++method_index){
		auto aux = cInfo->constant_pool[cInfo->methods[method_index].name_index - 1].typeUTF8String.stringU;
		auto aux2 = cInfo->constant_pool[cInfo->methods[method_index].descriptor_index - 1].typeUTF8String.stringU;

		if(!strcmp((char*)aux,(char*)methodName) && !strcmp((char*)aux2, methodType))
			break;
	}
	//if method not found
	if(method_index == cInfo->methods_count)
		return;
	
	//Find and assign code attribute
	for(int i = 0; i < cInfo->methods[method_index].attributes_count; i++){
		int strref = (cInfo->methods[method_index].attributes[i].name_index) - 1;
		if(!strcmp((char*)cInfo->constant_pool[strref].typeUTF8String.stringU, "Code")){
			codeAttribute = (cInfo->methods[method_index].attributes + i)->codeAttribute;
		}
		if(!strcmp((char*)cInfo->constant_pool[strref].typeUTF8String.stringU, "Exceptions")){
			exceptionsAttribute = (cInfo->methods[method_index].attributes + i)->exceptionsAttribute;
		}
	}

	this->locals.resize(codeAttribute->max_locals);

	thisClass = cInstance;


	for (int i = 0; i < args->size(); i++) {
		this->locals[i] = args->at(i);
	}

	//load local variables
	/*for(int i = 0; i < codeAttribute->attributes_count; ++i){
		int strref = codeAttribute->attributes[i].name_index;
		if (!strcmp((char*)cInfo->constant_pool[strref - 1].typeUTF8String.stringU, "LocalVariableTable")) {
			for (int j = 0; j < codeAttribute->attributes[i].localVariableAttribute->local_variable_table_length; j++) {
				int typeRefIndex = codeAttribute->attributes[i].localVariableAttribute->local_variable_table[j].descriptor_index;
				locals.emplace_back(new Types((char*)(cInfo->constant_pool[typeRefIndex - 1].typeUTF8String.stringU)));
			}
		}
	}*/
}

Frame::Frame(ClassInfo* cInfo, Cp_Info* constantPool, ClassInstance* cInstance, uint16_t method_Index) {
	//methodNaT is a reference to the method's name and type
	exceptionsAttribute = NULL;

	//Set up classes vars
	classInfo = cInfo;
	method_index = method_Index;
	//Find and assign code attribute
	for (int i = 0; i < cInfo->methods[method_index].attributes_count; i++) {
		int strref = (cInfo->methods[method_index].attributes[i].name_index) - 1;
		if (!strcmp((char*)cInfo->constant_pool[strref].typeUTF8String.stringU, "Code")) {
			codeAttribute = (cInfo->methods[method_index].attributes + i)->codeAttribute;
		}
		if (!strcmp((char*)cInfo->constant_pool[strref].typeUTF8String.stringU, "Exceptions")) {
			exceptionsAttribute = (cInfo->methods[method_index].attributes + i)->exceptionsAttribute;
		}
	}

	locals.resize(codeAttribute->max_locals);
	for (int i = 0; i < cInfo->field_count; i++) {
		locals[i] = new Types((char*)cInfo->constant_pool[cInfo->fields[i].descriptor_index - 1].typeUTF8String.stringU);
	}

	this->thisClass = cInstance;
	current_pc = 0;
}

Types* Frame::GetField(char* key) {
	std::string strkey(key);
	return (*thisClass->fieldVars)[strkey];
}

void Frame::PushOperandStack(Types* value) {
	operandStack.push(value);
}

Code_Attribute * Frame::GetCodeAttribute(){
	return codeAttribute;
}

ClassInfo * Frame::GetClassInfo(){
	return classInfo;
}

bool Frame::HandleException(int index){
	if (current_pc >= (codeAttribute->exception_table + index)->start_pc &&
		current_pc < (codeAttribute->exception_table + index)->end_pc) {
		current_pc = (codeAttribute->exception_table + index)->handler_pc;
		return true;
	}
	return false;
}

