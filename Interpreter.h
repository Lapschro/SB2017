#include <stack>
#include <unordered_map>
#include "Frame.h"
#include "Class_Structures.h"
#include <string>

class Interpreter{
	private:
		static Interpreter* instance;
		Interpreter();
		std::stack<Frame*> executionStack;
		std::unordered_map<std::string, ClassInfo*> loadedClasses;
		std::unordered_map<std::string, ClassInstance*> staticInstances;

	public:
		static Interpreter* GetInstance();
		void Run(ClassInfo* mainClass);
		void PushFrame(Frame*);
		void PopFrame();
		void AddClass(ClassInfo*);
		ClassInfo* GetClass(std::string key);
		ClassInfo* GetClass(const char* key);
		Types* GetStaticField(char* className, char* fieldName);
		Frame* GetTopFrame();
		void PushException(char* exception);
		ClassInstance* GetStaticInstance(const char* className);
};
