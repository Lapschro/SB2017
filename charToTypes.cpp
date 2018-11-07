Types* charToTypes(char* tag){
	Types *type = new Types();
	type->setTag(tag[0]);

	switch(tag[0]){
		case 'B':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_byte = (uint32_t*) malloc(sizeof(uint32_t));
					break;
		case 'C':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_char = (uint32_t*) malloc(sizeof(uint32_t));
					break;
		case 'D':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_double = (uint64_t*) malloc(sizeof(uint64_t));
					break;
		case 'F':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_float = (uint32_t*) malloc(sizeof(uint32_t));
					break;
		case 'I':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_int = (uint32_t*) malloc(sizeof(uint32_t));
					break;
		case 'J':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_long = (uint64_t*) malloc(sizeof(uint64_t));
					break;
		case 'L':	type->classInstance = (ClassInstance*) malloc(sizeof(ClassInstance));
					// Procurar ClassInfo* referente à classe associada ou procurar arquivo .class e carregar informações
					char* aux = tag;
					// Retirando o ; ao final da tag
					aux = strtok(aux, ";");
					// Quebrando char* nos espaços
					aux = strtok(aux, " ");
					// Pegando a segunda parte que contém ClassName
					aux = strtok(NULL, " ");
					// Procurando a classe entre as classes carregadas/carregando caso necessário
					std::unordered_map<std::string,ClassInfo*> loadedClasses = Interpreter::GetInstance()->GetClass(aux);
					break;
		case 'S':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_short = (uint32_t*) malloc(sizeof(uint32_t));
					break;
		case 'Z':	type->basicRef = (BasicTypes*) malloc(sizeof(BasicTypes));
					type->basicRef->type_boolean = (uint32_t*) malloc(sizeof(uint32_t));
					break;
		case '[':	type->arrayRef = (ArrayType*) malloc(sizeof(ArrayType));
					break;
	}

	return type;
}