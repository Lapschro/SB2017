#ifndef SCREENPRINTER_H_INCLUDED
#define SCREENPRINTER_H_INCLUDED

void Screen_Print_Javap_Format(ClassInfo *);
void Screen_Print_Access_Flag_Class(uint16_t);
void Screen_Print_Access_Flag_Method(uint16_t flag);
void Screen_Print_Constant_Type(ClassInfo, uint16_t);
void Screen_Print_Utf8_Ref(ClassInfo, uint16_t);
void Screen_Initialize_Print_Functions();

#endif // SCREENPRINTER_H_INCLUDED
