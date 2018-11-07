#include "Types.h"
#include "Interpreter.h"
#include <cstring>
#include <string>
#include <iostream>

void CreateBasicType(Types* type, char descr);
void CreateFieldVars(ClassInstance* cinstance);

Types::Types(char* descr){
	std::string description(descr);

	//create type string
	if (description == "STRING") {
		tag = STRING;
		stringRef = new std::string();
	}
	//create type return address
	else if (description == "RA") {
		tag = RETURNADDRESS;
		returnAddress = new (uint32_t);
		returnAddress = 0;
	}
	//create a basic type
	else if(descr[0] == 'B' ||  descr[0] == 'C' || descr[0] == 'D' || descr[0] == 'F' || 
		descr[0] == 'I' || descr[0] == 'J' || descr[0] == 'S' || descr[0] == 'Z')
		CreateBasicType(this, descr[0]);
	//create a array type
	else if (descr[0] == '[') {
		tag = ARRAY;
		arrayRef = (ArrayType*)malloc(sizeof(ArrayType));
		arrayRef->array = new std::vector<Types*>();
	}
	//create a instance type
	else if (descr[0] == 'L') {
		tag = CLASSINSTANCE;
		descr[strlen(descr) - 1] = 0;
		classInstance = (ClassInstance*)malloc(sizeof(ClassInstance));
		classInstance->classDescription = Interpreter::GetInstance()->GetClass(descr + 1);
	}

}

Types::Types() {
	tag = UNDEF;
}

void CreateFieldVars(ClassInstance* cinstance) {
	cinstance->fieldVars = new std::unordered_map<std::string, Types*>();
	ClassInfo* fieldToAdd = cinstance->classDescription;
	char* superName = (char*)fieldToAdd->constant_pool[fieldToAdd->constant_pool[fieldToAdd->super_class - 1].typeClassInfo - 1].typeUTF8String.stringU;
	
	do {
		for (int i = 0; i < fieldToAdd->field_count; i++) {
			int desc = fieldToAdd->fields[i].descriptor_index;
			int name_desc = fieldToAdd->fields[i].name_index;
			std::string key((char*)fieldToAdd->constant_pool[name_desc - 1].typeUTF8String.stringU);
			(*cinstance->fieldVars)[key] = new Types((char*)fieldToAdd->constant_pool[desc - 1].typeUTF8String.stringU);
		}
		if(strcmp(superName, "java/lang/Object") != 0)
			fieldToAdd = Interpreter::GetInstance()->GetClass(superName);
	} while (strcmp(superName, "java/lang/Object"));
}

void CreateBasicType(Types* type, char descr){
	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
	switch (descr) {
	case 'B':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->BYTE;
		type->basicRef->type_byte = (uint32_t*)malloc(sizeof(uint32_t));
		*type->basicRef->type_byte = 0;
		break;
	case 'C':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->CHAR;
		type->basicRef->type_char = (uint32_t*)malloc(sizeof(uint32_t));
		*type->basicRef->type_char = 0;
		break;
	case 'D':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->DOUBLE;
		type->basicRef->type_double = (uint64_t*)malloc(sizeof(uint64_t));
		*type->basicRef->type_double = 0;
		break;
	case 'F':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->FLOAT;
		type->basicRef->type_float = (uint32_t*)malloc(sizeof(uint32_t));
		*type->basicRef->type_float = 0;
		break;
	case 'I':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->INT;
		type->basicRef->type_int = (uint32_t*)malloc(sizeof(uint32_t));
		*type->basicRef->type_int = 0;
		break;
	case 'J':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->LONG;
		type->basicRef->type_long = (uint64_t*)malloc(sizeof(uint64_t));
		*type->basicRef->type_long = 0;
		break;
	case 'S':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->SHORT;
		type->basicRef->type_short = (uint32_t*)malloc(sizeof(uint32_t));
		*type->basicRef->type_short = 0;
		break;
	case 'Z':	type->basicRef = (BasicTypes*)malloc(sizeof(BasicTypes));
		type->tag = type->BOOL;
		type->basicRef->type_boolean = (uint32_t*)malloc(sizeof(uint32_t));
		*type->basicRef->type_boolean = 0;
		break;
	}
}


Types* copyTypes(Types* type) {
	Types* tipo = NULL;

	switch (type->tag) {
	case (Types::STRING):
		tipo = new Types((char*)"STRING");
		*tipo->stringRef = *type->stringRef;
		break;
	case (Types::BOOL):
		tipo = new Types((char*) "Z");
		*tipo->basicRef->type_boolean = *type->basicRef->type_boolean;
		break;
	case (Types::BYTE):
		tipo = new Types((char*) "B");
		*tipo->basicRef->type_byte = *type->basicRef->type_byte;
		break;
	case (Types::FLOAT):
		tipo = new Types((char*) "F");

		*tipo->basicRef->type_float = *type->basicRef->type_float;
		break;
	case (Types::LONG):
		tipo = new Types((char*) "J");
		*tipo->basicRef->type_long = *type->basicRef->type_long;
		break;
	case (Types::INT):
		tipo = new Types((char*) "I");
		*tipo->basicRef->type_int = *type->basicRef->type_int;
		break;
	case (Types::CHAR):
		tipo = new Types((char*) "C");
		*tipo->basicRef->type_char = *type->basicRef->type_char;
		break;
	case (Types::SHORT):
		tipo = new Types((char*) "S");
		*tipo->basicRef->type_short = *type->basicRef->type_short;
		break;
	case (Types::DOUBLE):
		tipo = new Types((char*) "D");
		*tipo->basicRef->type_double = *type->basicRef->type_double;
		break;
	case (Types::CLASSINSTANCE):
	{
		std::string aux = "L";
		Cp_Info* cpool = type->classInstance->classDescription->constant_pool + type->classInstance->classDescription->this_class - 1;
		while (cpool->tag != 1) {
			cpool = type->classInstance->classDescription->constant_pool + cpool->typeClassInfo - 1;
		}
		aux += std::string((char*)cpool->typeUTF8String.stringU);
		tipo = new Types((char*)aux.c_str());
	}
		break;
	case (Types::ARRAY):
		tipo = new Types((char*)"[");
		for (unsigned int i = 0; i < type->arrayRef->array->size(); i++) {
			Types* tipoAux = copyTypes(type->arrayRef->array->at(i));
			tipo->arrayRef->array->push_back(tipoAux);
		}
		break;
	case (Types::RETURNADDRESS):
		tipo = new Types((char*)"RA");
		*tipo->returnAddress = *type->returnAddress;
		break;
	case (Types::UNDEF):
		tipo = new Types();
		break;
	}

	return tipo;
}
