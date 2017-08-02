#ifndef FILEREADER_H_
#define FILEREADER_H_
#include <stdint.h>
#include <stdio.h>
#include "Class_Structures.h"
#include <fstream>
/*! \file FileReader.h
	\brief Arquivo que contem definicoes para a leitura de um .class.
	
	Define funcoes freadUx que leem x bits de um arquivo.
*/

/*! \fn uint32_t freadU32(uint32_t* ptr,int count, FILE * stream)
	\brief Uma funcao que le 32bits de um arquivo.
	\param ptr Um ponteiro para uma variavel tipo uint32_t.
	\param count A quantidade de uint32_t a ser lido.
	\param stream O ponteiro do arquivo a ser lido.
*/
uint32_t freadU32(uint32_t* ptr,int count, FILE * stream);


/*! \fn uint64_t freadU64(uint64_t* ptr,int count, FILE * stream)
	\brief Uma funcao que le 64bits de um arquivo.
	\param ptr Um ponteiro para uma variavel tipo uint64_t.
	\param count A quantidade de uint64_t a ser lido.
	\param stream O ponteiro do arquivo a ser lido.
*/
uint64_t freadU64(uint64_t* ptr,int count, FILE * stream);

/*! \fn uint8_t freadU8(uint8_t* ptr,int count, FILE * stream)
	\brief Uma funcao que le 8bits de um arquivo.
	\param ptr Um ponteiro para uma variavel tipo uint16_t.
	\param count A quantidade de uint8_t a ser lido.
	\param stream O ponteiro do arquivo a ser lido.
*/
uint8_t freadU8(uint8_t* ptr,int count, FILE * stream);
/*! \fn uint8_t freadU16(uint16_t* ptr,int count, FILE * stream)
	\brief Uma funcao que le 16bits de um arquivo.
	\param ptr Um ponteiro para uma variavel tipo uint16_t.
	\param count A quantidade de uint16_t a ser lido.
	\param stream O ponteiro do arquivo a ser lido.
*/
uint16_t freadU16(uint16_t* ptr,int count, FILE * stream);
/*! \fn ClassInfo* ReadClass(char* filename)
	\brief Funcao que le um .class e traduz o arquivo para um ClassInfo.
	\param filename Uma referencia ao nome do arquivo.
*/
ClassInfo* ReadClass(char* filename);


#endif //FILEREADER_H_
