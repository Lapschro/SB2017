#ifndef CLASS_STRUCTURES_H_
#define CLASS_STRUCTURES_H_
#include <stdint.h>
#include <cstring>

typedef struct ExceptionTable ExceptionTable;
typedef struct ConstantValue_Attribute ConstantValue_Attribute;
typedef struct AttributeInfo AttributeInfo;

struct ConstantValue_Attribute {
	uint16_t constantValue_index;
};

struct ExceptionTable {
	uint16_t start_pc;
	uint16_t end_pc;
	uint16_t handler_pc;
	uint16_t catch_type;
};

typedef struct Code_Attribute {
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	uint8_t* code;
	uint16_t exception_table_length;
	ExceptionTable* exception_table;
	uint16_t attributes_count;
	AttributeInfo* attributes;
} Code_Attribute;

typedef struct Exceptions_Attribute{
	uint16_t numberof_exceptions;
	uint16_t* exception_index_table;
}Exceptions_Attribute;

typedef struct classes{
	uint16_t inner_class_info_index;
    uint16_t outer_class_info_index;
    uint16_t inner_name_index;
    uint16_t inner_class_access_flags;
}Classes;

typedef struct{
	uint16_t number_of_classes;
	Classes *classes;
}InnerClasses_Attribute;

typedef struct SourceFile_Attribute{
    uint16_t sourcefile_index;
}SourceFile_Attribute;

typedef struct line_number_table{
    uint16_t start_pc;
    uint16_t line_number;
} Line_number_table;

typedef struct LineNumberTable_Attribute{
    uint16_t line_number_table_length;
    Line_number_table* line_number_table;
}LineNumberTable_Attribute;

typedef struct Local_Variable_Table {
	uint16_t start_pc;
	uint16_t length;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t index;
}Local_Variable_Table;

typedef struct LocalVariableTable_Attribute{
	uint16_t local_variable_table_length;
	Local_Variable_Table* local_variable_table;
}LocalVariableTable_Attribute;

struct AttributeInfo {
	uint16_t name_index;
	uint32_t length;
	union {
		ConstantValue_Attribute*		constvalueAttribute;
		Code_Attribute*					codeAttribute;
		Exceptions_Attribute*			exceptionsAttribute;
		InnerClasses_Attribute*			innerClassesAttribute;
		SourceFile_Attribute*			sourceFileAttribute;
		LineNumberTable_Attribute*		lineNumberTableAttribute;
		LocalVariableTable_Attribute*	localVariableAttribute;
		uint8_t*						info;
	};
};

typedef struct{
	uint16_t size;
	unsigned char* stringU;
}UTF8String;

typedef struct{
	uint8_t type_descriptor;
	uint16_t cpIndex;
}MethodHandle;

typedef struct{
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	AttributeInfo* attributes;
}MethodInfo;

typedef struct{
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	AttributeInfo* attributes;
}FieldInfo;

typedef struct{
	uint8_t tag;
	union{
		UTF8String 		typeUTF8String;
		uint32_t 		typeInt;
		uint32_t 		typeFloat;
		uint64_t		typeLong;
		uint64_t 		typeDouble;
		uint16_t		typeClassInfo;
		uint16_t		typeStringRef;

		//[32-16]bits as index and [15-0] as name and type
		uint32_t		typeFieldRef;

		//[32-16]bits as index and [15-0] as name and type
		uint32_t		typeMethodRef;
		
		//[32-16]bits as index and [15-0] as name and type
		uint32_t		typeInterfaceRef;

		//Name index is in [31..16]
		//Type in [15..0]
		uint32_t		typeNameAndType;
		MethodHandle	typeMethodHandle;
		uint16_t		typeMethodType;
		uint32_t		typeInvokeDynamic;
	};
}Cp_Info;

typedef struct{
	uint32_t 	magic_number;
	uint16_t 	minor_version;
	uint16_t 	major_version;
	uint16_t 	cp_size;
	Cp_Info* 	constant_pool;
	uint16_t 	access_flags;
	uint16_t	this_class;
	uint16_t	super_class;
	uint16_t	interface_count;
	uint16_t*	interface_table;
	uint16_t	field_count;
	FieldInfo* 	fields;
	uint16_t	methods_count;
	MethodInfo*	methods;
	uint16_t	attributes_count;
	AttributeInfo* attributes;
}ClassInfo;


#endif //CLASS_STRUCTURES_H_
