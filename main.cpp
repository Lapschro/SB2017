#include <iostream>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "FileReader.h"
#include "Class_Structures.h"
#include "FilePrinter.h"
#include "ScreenPrinter.h"
#include "Frame.h"
#include "Interpreter.h"

#if defined(_WIN32) || defined (_WIN64)
#define SHOWFILES "DIR"
#define CLEAR "CLS"
#else
#define SHOWFILES "ls"
#define CLEAR "clear"
#endif

int main(int argc, char** argv){
    char filename[256];
	char filepath[256];
	char outputfile[256];

	//FILE* fileP;
	//uint32_t test = 0;
	//uint8_t aux = 0;
	ClassInfo* kappa;

	strcpy(filename, "");
	strcpy(filepath, "");

	//Se o usuario nao deu um arquivo de entrada na linha de comando
	//E pedido um arquivo ao usuario.

	if(argc < 2){
		system(SHOWFILES);
		printf("File to load: ");
	    scanf("%[^\n]", filename);
		std::cout<<"Name of output file: ";
		std::cin>>outputfile;
		//strcpy(filename, argv[1]);
		int j = 0;
		for(j = strlen(filename) - 1; j >= 0; j--){
			if(filename[j] == '/')
				break;
			}
		strcpy(filepath, filename);
		filepath[++j] = 0;

	}else{
		if(argc == 2){
			strcpy(filename, argv[1]);
			int j = 0;
			for(j = strlen(filename) - 1; j >= 0; j--){
				if(filename[j] == '/')
					break;
				}
			strcpy(filepath, filename);
			filepath[++j] = 0;
			std::cout<<"Nome do arquivo de saida nao passado!\n";
			std::cout<<"O arquivo de saida padrao sera utilizado: Output.txt\n";
            strcpy(outputfile, "Output.txt");
		}else {
			for(int i = 1; i < argc; i++){
				if(!strcmp(argv[i], "-o")){
					i++;
					if(i < argc)
						strcpy(outputfile, argv[i]);
					else{
						std::cout<<"Nome do arquivo de saida nao passado!\n";
						std::cout<<"O arquivo de saida padrao sera utilizado: Output.txt\n";
						strcpy(outputfile, "Output.txt");
					}
				}else{
					strcpy(filename, argv[i]);

					int j = 0;
					for(j = strlen(filename) - 1; j >= 0; j--){
						if(filename[j] == '/')
							break;
					}
					strcpy(filepath, filename);
					filepath[++j] = 0;
				}
			}
	    }
	}

	/**********************
	**READING FILE        *
	***********************/

	kappa = ReadClass(filename);
	if (kappa == NULL)
		return -1;
	Interpreter::GetInstance()->AddClass(kappa);

	int choice;
	do{
		std::cout<<"-----------------------------------------\n";
		std::cout<<"| JAVA CLASS READER                     |\n";
		std::cout<<"-----------------------------------------\n";
		std::cout<<"| 1 : Ler arquivo e mostrar na tela     |\n";
		std::cout<<"| 2 : Ler arquivo e escrever no arquivo |\n";
		std::cout<<"|     de saida com o nome escolhido     |\n";
		std::cout<<"| 3 : Interpretar                       |\n";
		std::cout<<"| 4 : Limpar terminal                   |\n";
		std::cout<<"|-1 : Sair                              |\n";
		std::cout<<"-----------------------------------------\n";
		std::cout<<">> ";
		std::cin>>choice;

		switch(choice){
			case(1):
				Screen_Print_Javap_Format(kappa);
				break;
			case(2):
				Print_Javap_Format(kappa, outputfile);
				break;
			case(3):
				Frame::SetUp();
				Interpreter::GetInstance()->Run(kappa);
				break;
			case(4):
				system(CLEAR);
				break;
		}

	}while(choice != -1);
	//Frame* xiba = new Frame(kappa, kappa->constant_pool, 145, NULL, NULL);
	//std::cout<<kappa->constant_pool[kappa->methods[0].name_index - 1].typeUTF8String.stringU<<std::endl;
	//system("PAUSE");
	return 0;
}
