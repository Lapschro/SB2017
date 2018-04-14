#include "FileReader.h"
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <cstring>
#include "Class_Structures.h"
#include <iostream>

void ReadAttribute(AttributeInfo* attr, FILE *fp, Cp_Info* cpool);
void ReadAttributeConstantValue(AttributeInfo* attr, FILE *fp);
void ReadAttributeCode(AttributeInfo* attr, FILE *fp, Cp_Info* cpool);
void ReadAttributeExceptions(AttributeInfo* attr, FILE *fp);
void ReadAttributeConstantValue(AttributeInfo* attr, FILE *fp);
void ReadAttributeInnerClasses(AttributeInfo* attr, FILE *fp);
void ReadAttributeSourceFile(AttributeInfo* attr, FILE *fp);
void ReadAttributeLineNumberTable(AttributeInfo* attr, FILE *fp);
void ReadAttributeLocalVariableTable(AttributeInfo* attr, FILE *fp);

char* FILEPATHBOYS = NULL;

uint32_t freadU32(uint32_t* ptr,int count, FILE * stream){
	uint32_t aux = 0;
	for(int j= 0; j < count; j++){
		aux = 0;
		for(int i = 0; i < 4; i++){
			uint8_t temp;
			fread(&temp, sizeof(uint8_t), 1, stream);
			aux<<=8;
			aux|=temp;
		}
		*(ptr+j) = aux;
	}
	return aux;
}

uint64_t freadU64(uint64_t* ptr,int count, FILE * stream){
	uint64_t aux = 0;
	for(int j= 0; j < count; j++){
		aux = 0;
		for(int i = 0; i < 8; i++){
			uint8_t temp;
			fread(&temp, sizeof(uint8_t), 1, stream);
			aux<<=8;
			aux|=temp;
		}
		*(ptr+j) = aux;
	}
	return aux;
}

uint8_t freadU8(uint8_t* ptr,int count, FILE * stream){
	return (uint8_t)fread(ptr, sizeof(uint8_t), count, stream);
}

uint16_t freadU16(uint16_t* ptr,int count, FILE * stream){
	uint16_t aux = 0;
	for(int j= 0; j < count; j++){
		aux = 0;
		for(int i = 0; i < 2; i++){
			uint8_t temp;
			fread(&temp, sizeof(uint8_t), 1, stream);
			aux<<=8;
			aux|=temp;
		}
		*(ptr+j) = aux;
	}
	return aux;
}

ClassInfo* ReadClass(char* filename){
	
    FILE* fileP = 0;
	//char* filenameaux = NULL;
	char* newfilename;
	if (FILEPATHBOYS == NULL) {
		FILEPATHBOYS = (char*)malloc(300 * sizeof(char));

		int k;
		for (k = strlen(filename) - 1; k >= 0; --k) {
			if (filename[k] == '\\' || filename[k] == '/')
				break;
		}
		
		strcpy(FILEPATHBOYS, filename);
		FILEPATHBOYS[k + 1] = 0;
		strcpy(filename, filename);
	}
	else {
		int k;
		for (k = strlen(filename) - 1; k >= 0; --k) {
			if (filename[k] == '\\' || filename[k] == '/')
				break;
		}

		char* pathto = (char*)malloc(32*sizeof(char));
		strncpy(pathto, filename, strlen(filename) - k);
		if (strstr(FILEPATHBOYS, filename) == 0 && strstr((char*)"java/", filename) == 0) {
			strcpy(filename, filename + k + 1);
			std::string aux(filename + k + 1);

			strcpy(filename, FILEPATHBOYS);
			strcat(filename, aux.c_str());
		}
	}

	if (!strstr(filename, ".class")) {
		newfilename = (char*)malloc(/*(strlen(filename)+8)*/256*sizeof(char));
		strcpy(newfilename, filename);
		strcat(newfilename, (char*)".class");
		filename = newfilename;
	}

	//std::cout << filename << std::endl;

    if((fileP = fopen(filename, "rb")) == NULL){
		printf("%s\n", filename);
		printf("File not found!\n");
		return NULL;
	}
    //Alocando espaço para struct ClassInfo
    ClassInfo* classInfo = (ClassInfo*)malloc(sizeof(ClassInfo));

    //Lendo magic number
	freadU32(&classInfo->magic_number, 1, fileP);

    //Checando se magic number == "cafebabe"
	if((uint32_t)classInfo->magic_number != 0xcafebabe){
		printf("Invalid Magic Number!\n");
		fclose(fileP);
		return NULL;
	}

    //Lendo minor version
	freadU16(&classInfo->minor_version, 1, fileP);

    //Lendo major version
	freadU16(&classInfo->major_version, 1, fileP);

    //Lendo tamanho da constant pool
	freadU16(&classInfo->cp_size, 1, fileP);
	//printf("%d\n", classInfo->cp_size);

    //Alocando espaço para constant pool
	classInfo->constant_pool = (Cp_Info*)malloc((classInfo->cp_size - 1)*sizeof(Cp_Info));

	//Leitura da constant pool
    for(int i = 0; i < classInfo->cp_size - 1; i++){
        freadU8(&(classInfo->constant_pool + i)->tag, 1, fileP);
        switch((classInfo->constant_pool + i)->tag){

        case 7:
            freadU16(&(classInfo->constant_pool + i)->typeClassInfo, 1, fileP);
            break;
        case 9:
            freadU32(&(classInfo->constant_pool + i)->typeFieldRef, 1, fileP);
            break;
        case 10:
            freadU32(&(classInfo->constant_pool + i)->typeMethodRef, 1, fileP);
            break;
        case 11:
            freadU32(&(classInfo->constant_pool + i)->typeInterfaceRef, 1, fileP);
            break;
        case 8:
            freadU16(&(classInfo->constant_pool + i)->typeStringRef, 1, fileP);
            break;
        case 3:
            freadU32(&(classInfo->constant_pool + i)->typeInt, 1, fileP);
            break;
        case 4:
            freadU32(&(classInfo->constant_pool + i)->typeFloat, 1, fileP);
            break;
        case 5:
            freadU64(&(classInfo->constant_pool + i++)->typeLong, 1, fileP);
            break;
        case 6:
            freadU64(&(classInfo->constant_pool + i++)->typeDouble, 1, fileP);
            break;
        case 12:
            freadU32(&(classInfo->constant_pool + i)->typeNameAndType, 1, fileP);
            break;
        case 1:
            //utf8
            freadU16(&(classInfo->constant_pool + i)->typeUTF8String.size, 1, fileP);
            (classInfo->constant_pool + i)->typeUTF8String.stringU = (unsigned char*) malloc(((classInfo->constant_pool + i)->typeUTF8String.size + 1) *sizeof(unsigned char));
            (classInfo->constant_pool + i)->typeUTF8String.stringU[(classInfo->constant_pool + i)->typeUTF8String.size] = '\0';
            //freadU8((classInfo->constant_pool + i)->typeUTF8String.string, (classInfo->constant_pool + i)->typeUTF8String.size, fileP);
            for(int bom = 0; bom < (classInfo->constant_pool + i)->typeUTF8String.size ; bom++){
                freadU8(((classInfo->constant_pool + i)->typeUTF8String.stringU + bom), 1, fileP);
            }
            break;
        case 15:

            freadU8(&(classInfo->constant_pool + i)->typeMethodHandle.type_descriptor, 1, fileP);
            freadU16(&(classInfo->constant_pool + i)->typeMethodHandle.cpIndex, 1, fileP);
            break;
        case 16:
            freadU32(&(classInfo->constant_pool + i)->typeMethodRef, 1, fileP);
            break;
        case 18:
            freadU32(&(classInfo->constant_pool + i)->typeInvokeDynamic, 1, fileP);
            break;
        }//End Switch-case
    } //Endfor

    //Lendo flags de acesso
    freadU16(&(classInfo->access_flags), 1, fileP);
    //printf("Access Flags: %04x\n", classInfo->access_flags);

    //Lendo nome da classe
    freadU16(&(classInfo->this_class), 1, fileP);
    //printf("This ClassInfo: %04x\n", classInfo->this_class);

    //Lendo nome da super classe
    freadU16(&(classInfo->super_class), 1, fileP);
    //printf("Super ClassInfo: %04x\n", classInfo->super_class);

    //Lendo numero de itens da interface
    freadU16(&(classInfo->interface_count), 1, fileP);
    //printf("Interface Count: %04x\n", classInfo->interface_count);

    //Alocando espaço para interface table
    classInfo->interface_table = (uint16_t*)malloc(classInfo->interface_count*sizeof(uint16_t));
    //Lendo itens da interface table
    freadU16(classInfo->interface_table, classInfo->interface_count, fileP);

    /*for(int i = 0; i < classInfo->interface_count; i++){
        printf("Interface %d: %04x\n",i, *(classInfo->interface_table + i));
    }*/

    /********
    *   FIELDINFO
    */
    freadU16(&(classInfo->field_count), 1, fileP);
    //printf("Field Count: %04x\n",(classInfo->field_count));

    classInfo->fields = (FieldInfo*)malloc(classInfo->field_count*sizeof(FieldInfo));

    for(int i = 0; i < classInfo->field_count; i++){
       // printf("Field %d\n", i);
        freadU16(&((classInfo->fields+i)->access_flags), 1, fileP);
       // printf("%04x\n", (classInfo->fields+i)->access_flags);

        freadU16(&((classInfo->fields+i)->name_index), 1, fileP);
        //printf("%04x\n", (classInfo->fields+i)->name_index);

        freadU16(&((classInfo->fields+i)->descriptor_index), 1, fileP);
       // printf("%04x\n", (classInfo->fields+i)->descriptor_index);

        freadU16(&((classInfo->fields+i)->attributes_count), 1, fileP);
       // printf("%04x\n", (classInfo->fields+i)->attributes_count);

        (classInfo->fields+i)->attributes = (AttributeInfo*)malloc((classInfo->fields+i)->attributes_count*sizeof(AttributeInfo));
        for(int j = 0; j < (classInfo->fields+i)->attributes_count; j++){
			ReadAttribute((classInfo->fields + i)->attributes + j, fileP, classInfo->constant_pool);
        }
    }

    /********
    *   METHODINFO
    */
    freadU16(&(classInfo->methods_count), 1, fileP);
    //printf("%04x\n",(classInfo->methods_count));
    classInfo->methods = (MethodInfo*)malloc(classInfo->methods_count*sizeof(MethodInfo));

    for(int i = 0; i < classInfo->methods_count;i++){
       // printf("method %d:\n", i);
        freadU16(&((classInfo->methods+i)->access_flags), 1, fileP);
       // printf("%04x\n", (classInfo->methods+i)->access_flags);

        freadU16(&((classInfo->methods+i)->name_index), 1, fileP);
        //printf("%04x\n", (classInfo->methods+i)->name_index);

        freadU16(&((classInfo->methods+i)->descriptor_index), 1, fileP);
        //printf("%04x\n", (classInfo->methods+i)->descriptor_index);

        freadU16(&((classInfo->methods+i)->attributes_count), 1, fileP);
        //printf("%04x\n", (classInfo->methods+i)->attributes_count);

        (classInfo->methods+i)->attributes = (AttributeInfo*)malloc((classInfo->methods+i)->attributes_count*sizeof(AttributeInfo));
        for(int j = 0; j < (classInfo->methods+i)->attributes_count; j++){
			ReadAttribute((classInfo->methods + i)->attributes + j, fileP, classInfo->constant_pool);
        }
    }

    /********
    *   ATTRIBUTEINFO
    */
    freadU16(&(classInfo->attributes_count), 1, fileP);
    classInfo->attributes = (AttributeInfo*)malloc(classInfo->attributes_count*sizeof(AttributeInfo));

    for(int j = 0; j < classInfo->attributes_count; j++){
		ReadAttribute(classInfo->attributes + j, fileP, classInfo->constant_pool);
    }

	fclose(fileP);
	return classInfo;
}

void ReadAttribute(AttributeInfo* attr, FILE *fp, Cp_Info* cpool) {
	freadU16(&attr->name_index, 1, fp);
	freadU32(&attr->length, 1, fp);

	if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "ConstantValue")) {
		attr->constvalueAttribute = (ConstantValue_Attribute*)malloc(sizeof(ConstantValue_Attribute));
		ReadAttributeConstantValue(attr, fp);
	}
	else if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "Code")) {
		attr->codeAttribute = (Code_Attribute*)malloc(sizeof(Code_Attribute));
		ReadAttributeCode(attr, fp, cpool);
	}
	else if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "Exceptions")) {
		attr->exceptionsAttribute = (Exceptions_Attribute*)malloc(sizeof(Exceptions_Attribute));
		ReadAttributeExceptions(attr, fp);
	}
	else if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "InnerClasses")) {
		attr->innerClassesAttribute = (InnerClasses_Attribute*)malloc(sizeof(InnerClasses_Attribute));
		ReadAttributeInnerClasses(attr, fp);
	}
	else if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "SourceFile")) {
		attr->sourceFileAttribute = (SourceFile_Attribute*)malloc(sizeof(SourceFile_Attribute));
		ReadAttributeSourceFile(attr, fp);
	}
	else if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "LineNumberTable")) {
		attr->lineNumberTableAttribute = (LineNumberTable_Attribute*)malloc(sizeof(LineNumberTable_Attribute));
		ReadAttributeLineNumberTable(attr, fp);
	}
	else if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "LocalVariableTable")) {
		attr->localVariableAttribute = (LocalVariableTable_Attribute*)malloc(sizeof(LocalVariableTable_Attribute));
		ReadAttributeLocalVariableTable(attr, fp);
	}
	else if (!strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "Synthetic")
		|| !strcmp((char*)(cpool + attr->name_index - 1)->typeUTF8String.stringU, "Deprecated")){}
	else {
		attr->info = (uint8_t*)malloc(attr->length * sizeof(uint8_t));
		freadU8(attr->info, attr->length, fp);
	}
}

void ReadAttributeConstantValue(AttributeInfo* attr, FILE *fp) {
	freadU16(&attr->constvalueAttribute->constantValue_index, 1, fp);
}

void ReadAttributeCode(AttributeInfo* attr, FILE *fp, Cp_Info* cpool) {
	freadU16(&attr->codeAttribute->max_stack, 1, fp);
	freadU16(&attr->codeAttribute->max_locals, 1, fp);
	freadU32(&attr->codeAttribute->code_length, 1, fp);

	attr->codeAttribute->code = (uint8_t*)malloc(attr->codeAttribute->code_length * sizeof(uint8_t));
	freadU8(attr->codeAttribute->code, attr->codeAttribute->code_length, fp);

	freadU16(&attr->codeAttribute->exception_table_length, 1, fp);
	attr->codeAttribute->exception_table = (ExceptionTable*)malloc(attr->codeAttribute->exception_table_length * sizeof(ExceptionTable));

	for (int i = 0; i < attr->codeAttribute->exception_table_length; i++) {
		freadU16(&(attr->codeAttribute->exception_table + i)->start_pc, 1, fp);
		freadU16(&(attr->codeAttribute->exception_table + i)->end_pc, 1, fp);
		freadU16(&(attr->codeAttribute->exception_table + i)->handler_pc, 1, fp);
		freadU16(&(attr->codeAttribute->exception_table + i)->catch_type, 1, fp);
	}

	freadU16(&attr->codeAttribute->attributes_count, 1, fp);
	attr->codeAttribute->attributes = (AttributeInfo*)malloc(attr->codeAttribute->attributes_count * sizeof(AttributeInfo));
	for (int i = 0; i < attr->codeAttribute->attributes_count; i++) {
		ReadAttribute((attr->codeAttribute->attributes + i), fp, cpool);
	}
}

void ReadAttributeExceptions(AttributeInfo* attr, FILE *fp) {
	freadU16(&attr->exceptionsAttribute->numberof_exceptions, 1, fp);
	attr->exceptionsAttribute->exception_index_table = (uint16_t*)malloc(attr->exceptionsAttribute->numberof_exceptions * sizeof(uint16_t));
	freadU16(attr->exceptionsAttribute->exception_index_table, attr->exceptionsAttribute->numberof_exceptions, fp);
}

void ReadAttributeInnerClasses(AttributeInfo* attr, FILE *fp) {
	freadU16(&attr->innerClassesAttribute->number_of_classes, 1, fp);
	attr->innerClassesAttribute->classes = (Classes*)malloc(attr->innerClassesAttribute->number_of_classes * sizeof(Classes));
	for (int i = 0; i < attr->innerClassesAttribute->number_of_classes; i++) {
		freadU16(&attr->innerClassesAttribute->classes->inner_class_info_index, 1, fp);
		freadU16(&attr->innerClassesAttribute->classes->outer_class_info_index, 1, fp);
		freadU16(&attr->innerClassesAttribute->classes->inner_name_index, 1, fp);
		freadU16(&attr->innerClassesAttribute->classes->inner_class_access_flags, 1, fp);
	}
}

void ReadAttributeSourceFile(AttributeInfo* attr, FILE *fp) {
	freadU16(&(attr->sourceFileAttribute->sourcefile_index), 1, fp);
}

void ReadAttributeLineNumberTable(AttributeInfo* attr, FILE *fp) {
	freadU16(&attr->lineNumberTableAttribute->line_number_table_length, 1, fp);
	attr->lineNumberTableAttribute->line_number_table = (line_number_table*)malloc(attr->lineNumberTableAttribute->line_number_table_length * sizeof(line_number_table));
	for (int i = 0; i < attr->lineNumberTableAttribute->line_number_table_length; i++) {
		freadU16(&(attr->lineNumberTableAttribute->line_number_table + i)->start_pc, 1, fp);
		freadU16(&(attr->lineNumberTableAttribute->line_number_table + i)->line_number, 1, fp);
	}
}

void ReadAttributeLocalVariableTable(AttributeInfo* attr, FILE *fp) {
	freadU16(&attr->localVariableAttribute->local_variable_table_length, 1, fp);
	attr->localVariableAttribute->local_variable_table = (Local_Variable_Table*)malloc(attr->localVariableAttribute->local_variable_table_length * sizeof(Local_Variable_Table));
	for (int i = 0; i < attr->localVariableAttribute->local_variable_table_length; i++) {
		freadU16(&(attr->localVariableAttribute->local_variable_table + i)->start_pc, 1, fp);
		freadU16(&(attr->localVariableAttribute->local_variable_table + i)->length, 1, fp);
		freadU16(&(attr->localVariableAttribute->local_variable_table + i)->name_index, 1, fp);
		freadU16(&(attr->localVariableAttribute->local_variable_table + i)->descriptor_index, 1, fp);
		freadU16(&(attr->localVariableAttribute->local_variable_table + i)->index, 1, fp);
	}
}
