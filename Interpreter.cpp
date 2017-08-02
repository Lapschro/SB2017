#include "Interpreter.h"
#include "FileReader.h"
#include "ScreenPrinter.h"
#include <iostream>
#include <cstdlib>


Interpreter* Interpreter::instance = NULL;

Interpreter::Interpreter(){
}

Interpreter* Interpreter::GetInstance(){
	if (instance == NULL)
		instance = new Interpreter();
	return instance;
}


void Interpreter::Run(ClassInfo* mainClass){
	ClassInstance* mainInstance = new ClassInstance();
	mainInstance->classDescription = mainClass;

	int mainIndex = 0;

	for (mainIndex = 0; mainIndex < (int)mainClass->methods_count; mainIndex++) {
		char* mname = (char*)mainClass->constant_pool[mainClass->methods[mainIndex].name_index - 1].typeUTF8String.stringU;
		if (!strcmp(mname, "main"))
			break;
	}

	if (mainIndex == (int)mainClass->methods_count) {
		std::cout << "Main not found!!" << std::endl;
		return;
	}

	int i;

	char* className = (char*)mainClass->constant_pool[mainClass->constant_pool[mainClass->this_class - 1].typeClassInfo - 1].typeUTF8String.stringU;
	for (i = strlen(className) - 1; i >= 0; i--) {
		if (className[i] == '/')
			break;
	}

	std::string keystring(className);
	keystring += ".class";

	staticInstances[keystring] = mainInstance;
	CreateFieldVars(mainInstance);

	Frame* mainFrame = new Frame(mainClass, mainClass->constant_pool, mainInstance, mainIndex);

	executionStack.push(mainFrame);

	while(!executionStack.empty()){
		executionStack.top()->Execute();
	}
}

void Interpreter::PushFrame(Frame* frame){
	executionStack.push(frame);
}

void Interpreter::PopFrame(){
	executionStack.pop();
}

void Interpreter::AddClass(ClassInfo* cinfo){
	if (cinfo == NULL) {
		return;
	}
	int i;
	i = cinfo->constant_pool[cinfo->this_class - 1].typeClassInfo;
	char* aux;
	aux = (char*)malloc((cinfo->constant_pool[i - 1].typeUTF8String.size) * sizeof(char) * 2);
	int j;
	for (j = strlen(((char*)cinfo->constant_pool[i - 1].typeUTF8String.stringU)) - 1; j >= 0; j--) {
		if (cinfo->constant_pool[i - 1].typeUTF8String.stringU[j] == '/')
			break;
	}

	strcpy(aux, (char*)(cinfo->constant_pool[i - 1].typeUTF8String.stringU + j + 1));

	std::string key(aux);
	key += ".class";

	//std::cout << key << std::endl;
	loadedClasses[key] = cinfo;
	ClassInstance* staticInstance;
	//std::cout << key << std::endl;
	for (i = 0; i < cinfo->field_count; i++) {
		if ((cinfo->fields[i].access_flags & 0x8) != 0) {
			staticInstance = (ClassInstance*)malloc(sizeof(ClassInstance));
			staticInstance->classDescription = cinfo;
			CreateFieldVars(staticInstance);
			staticInstances[key] = staticInstance;
			break;
		}
	}
}

ClassInfo* Interpreter::GetClass(std::string key){

	int aux;

	for (aux = key.size() - 1; aux >= 0; aux--) {
		if (key[aux] == '/')
			break;
	}

	std::string subkey = key.substr(aux + 1);
	subkey += ".class";

	ClassInfo* aux2 = loadedClasses[subkey];
	//If not loaded load class
	if(aux == 0){
		aux2 = ReadClass((char*)key.c_str());
		AddClass(aux2);
		//loadedClasses[subkey] = aux2;
	}
	//std::cout << subkey << std::endl;
	return aux2;
}

ClassInfo* Interpreter::GetClass(const char* key){
	int i;

	for (i = strlen(key) - 1; i >= 0; i--) {
		if (key[i] == '/')
			break;
	}

	std::string keystring(key + i + 1);
	keystring += ".class";

	ClassInfo* aux = loadedClasses[keystring];

	if(aux == NULL){
		aux = ReadClass((char*)key);
		AddClass(aux);
		//loadedClasses[keystring] = aux;
	}

	//std::cout << keystring << std::endl;
	return aux;
}

Types* Interpreter::GetStaticField(char* className, char* fieldName) {
	int i;

	for (i = strlen(className) - 1; i >= 0; i--) {
		if (className[i] == '/')
			break;
	}

	std::string keystring(className + i + 1);
	keystring += ".class";
	
	ClassInstance* aux = staticInstances[keystring];
	std::string field(fieldName);

	return (*aux->fieldVars)[field];
}

ClassInstance* Interpreter::GetStaticInstance(const char* className) {
	int i;

	for (i = strlen(className) - 1; i >= 0; i--) {
		if (className[i] == '/')
			break;
	}

	std::string keystring(className + i + 1);
	keystring += ".class";

	return staticInstances[keystring];
}

Frame* Interpreter::GetTopFrame() {
	return executionStack.top();
}

void Interpreter::PushException(char* exception) {
	bool handled = false;
	while (!executionStack.empty() || !handled) {
		executionStack.pop();
		if (executionStack.empty()) {
			std::cout << "Exception: " << exception<<std::endl;
			break;
		}
		for (int i = 0; i < executionStack.top()->GetCodeAttribute()->exception_table_length && !handled; i++) {
			char* catchType;
			if ((executionStack.top()->GetCodeAttribute()->exception_table[i].catch_type) != 0) {
				catchType = (char*)executionStack.top()->GetClassInfo()->constant_pool[executionStack.top()->GetClassInfo()->constant_pool[executionStack.top()->GetCodeAttribute()->exception_table[i].catch_type - 1].typeClassInfo - 1].typeUTF8String.stringU;
				if (!strcmp(exception, catchType)) {
					handled = (executionStack.top()->HandleException(i));
				}
			}
			else {
				catchType = NULL;
				handled = (executionStack.top()->HandleException(i));
			}
		}
	}
}
