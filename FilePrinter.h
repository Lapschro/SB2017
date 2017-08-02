#ifndef FILEPRINTER_H_INCLUDED
#define FILEPRINTER_H_INCLUDED

void Print_Javap_Format(ClassInfo *, char *);
void Print_Access_Flag_Class(uint16_t, std::ofstream& writerFile);
void Print_Access_Flag_Method(uint16_t flag, std::ofstream& writerFile);
void Print_Constant_Type(ClassInfo, uint16_t, std::ofstream& writerFile);
void Print_Utf8_Ref(ClassInfo, uint16_t, std::ofstream& writerFile);
void Initialize_Print_Functions(std::ofstream& writerFile);

#endif // FILEPRINTER_H_INCLUDED
