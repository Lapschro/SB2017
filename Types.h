#ifndef TYPES_H_
#define TYPES_H_

#include <vector>
#include <cstdint>
#include <string>
#include "Class_Structures.h"
#include <unordered_map>

typedef struct BasicTypes BasicTypes;
typedef struct ArrayType ArrayTypes;
typedef struct ClassInstance ClassInstance;

void CreateFieldVars(ClassInstance* cinstance);

class Types{
public:
	enum TAGTYPE {UNDEF, BYTE, BOOL, CHAR, SHORT, INT, FLOAT, LONG, DOUBLE, CLASSINSTANCE, ARRAY, STRING, RETURNADDRESS};
	TAGTYPE tag;
	union{
		BasicTypes* basicRef;
		ArrayType* arrayRef;
		ClassInstance* classInstance;
		std::string* stringRef;
		uint32_t* returnAddress;
	};
	Types(char*);
	Types();
};

typedef struct BasicTypes{
	union{
		uint32_t *type_boolean;
        uint32_t *type_byte;
        uint32_t *type_char;
        uint32_t *type_short;
        uint32_t *type_int;
        uint32_t *type_float;
        uint64_t *type_long;
        uint64_t *type_double;
	};
} BasicTypes;

typedef struct ArrayType{
	std::vector<Types*>* array;
} ArrayType;

typedef struct ClassInstance{
	ClassInfo* classDescription;
	std::unordered_map<std::string, Types*>* fieldVars;
} ClassInstance;

Types* copyTypes(Types* type);
#endif
