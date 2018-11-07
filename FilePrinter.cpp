#include "FileReader.h"
#include <stdio.h>
#include <stdbool.h>
#include <cinttypes>
#include <cstdint>
#include <string.h>
#include <iostream>

#define LIST_INSTRUCTIONS(o) \
    o((char*)"aaload",			0,  0x32, 0) \
    o((char*)"aastore" ,		0,  0x53, 0) \
	o((char*)"aconst_null",		0,  0x01, 0) \
	o((char*)"aload",			1,  0x19, 0) \
	o((char*)"aload_0",			0,  0x2a,0) \
	o((char*)"aload_1",			0,  0x2b,0) \
	o((char*)"aload_2",			0,  0x2c,0) \
	o((char*)"aload_3",			0,  0x2d,0) \
	o((char*)"anewarray",		2,  0xbd,0) \
	o((char*)"areturn",			0,  0xb0, 0) \
	o((char*)"arraylength",		0, 0xbe,0 ) \
	o((char*)"astor",			1, 0x3a, 0) \
	o((char*)"astore_0",		0,  0x4b,0) \
	o((char*)"astore_1",		0, 0x4c,0) \
	o((char*)"astore_2",		0, 0x4d,0) \
	o((char*)"astore_3",		0, 0x4e,0) \
	o((char*)"athrow",			0,  0xbf, 0) \
	o((char*)"baload",			0,  0x33, 0) \
	o((char*)"bastore",			0,  0x54, 0) \
	o((char*)"bipush",			1,  0x10,0) \
	o((char*)"caload",			0,  0x34,0) \
	o((char*)"castore",			0,  0x55,0) \
	o((char*)"checkcast",		2,  0xc0,0) \
	o((char*)"d2f",				0, 0x90, 0) \
	o((char*)"d2i",				0, 0x8e, 0) \
	o((char*)"d2l",				0,  0x8f, 0) \
	o((char*)"dadd",			0, 0x63,  0) \
	o((char*)"daload",			0,  0x31,0) \
	o((char*)"dastore",			0, 0x52, 0) \
	o((char*)"dcmpg",			0, 0x98, 0) \
	o((char*)"dcmpl",			0, 0x97, 0) \
	o((char*)"dconst_0",		0,  0x0e,0 ) \
	o((char*)"dconst_1",		0,  0x0f, 0) \
	o((char*)"ddiv",			0,  0x6f, 0) \
	o((char*)"dload",			1,  0x18, 0) \
	o((char*)"dload_0",			0,  0x26 ,0) \
	o((char*)"dload_1",			0,  0x27 ,0) \
	o((char*)"dload_2",			0,  0x28 ,0) \
	o((char*)"dload_3",			0,  0x29 ,0) \
	o((char*)"dmul",			0,  0x6b, 0) \
	o((char*)"dneg",			0,  0x77, 0) \
	o((char*)"drem",			0,  0x73,0 ) \
	o((char*)"dreturn",			0,  0xaf,0 ) \
	o((char*)"dstore",			1,  0x39, 0) \
	o((char*)"dstore_0",		0, 0x47, 0) \
	o((char*)"dstore_1",		0, 0x48, 0) \
	o((char*)"dstore_2",		0, 0x49, 0) \
	o((char*)"dstore_3",		0, 0x4a, 0) \
	o((char*)"dsub",			0,  0x67, 0) \
	o((char*)"dup",				0,  0x59, 0) \
	o((char*)"dup_x1",			0,  0x5a, 0) \
	o((char*)"dup_x2",			0, 0x5b, 0) \
	o((char*)"dup2",			0,  0x5c, 0) \
	o((char*)"dup2_x1",			0,  0x5d,0) \
    o((char*)"dup2_x2",			0,  0x5e,0) \
    o((char*)"f2d",				0,  0x8d,0) \
    o((char*)"f2i",				0,  0x8b,0) \
	o((char*)"f2l",				0,  0x8c,0) \
	o((char*)"fadd",			0,  0x62,0) \
	o((char*)"faload",			0,  0x30,0) \
	o((char*)"fastore",			0,  0x51,0) \
	o((char*)"fcmpg",			0,  0x96,  0) \
	o((char*)"fcmpl>",			0,  0x96, 0) \
	o((char*)"fconst_0",		0,  0x0b,0) \
	o((char*)"fconst_1",		0,  0x0c,0) \
	o((char*)"fconst_2",		0,  0x0d,0) \
	o((char*)"fdiv",			0,  0x6e,0) \
	o((char*)"fload",			1,  0x17,0) \
	o((char*)"fload_0",			0,  0x22,0) \
	o((char*)"fload_1",			0,  0x23,0) \
	o((char*)"fload_2",			0,  0x24, 0) \
	o((char*)"fload_3",			0,  0x25, 0) \
	o((char*)"fmul",			0,  0x6a,0) \
	o((char*)"fneg",			0,  0x76,0) \
	o((char*)"frem",			0,  0x72,0) \
	o((char*)"freturn",			0,  0xae,0) \
	o((char*)"fstore",			1,  0x38,0) \
	o((char*)"fstore_0",		0,  0x43,0) \
	o((char*)"fstore_1",		0,  0x44,0) \
	o((char*)"fstore_2",		0,  0x45,0) \
	o((char*)"fstore_3",		0,  0x46,0) \
	o((char*)"fsub",			0,  0x66, 0) \
	o((char*)"getfield",		2,  0xb4, 0) \
	o((char*)"getstatic",		2,  0xb2, 0) \
	o((char*)"goto",			2,  0xa7, 0) \
    o((char*)"goto_w",			4,  0xc8, 0) \
    o((char*)"i2b",				0, 0x91,0) \
	o((char*)"i2c",				0, 0x92,0) \
	o((char*)"i2d",				0, 0x87,0) \
	o((char*)"i2f",				0, 0x86,0) \
	o((char*)"i2l",				0, 0x85,0) \
	o((char*)"i2s",				0, 0x93,0) \
	o((char*)"iadd",			0, 0x60,0) \
	o((char*)"iaload",			0, 0x2e,0) \
	o((char*)"iand",			0, 0x7e,0) \
	o((char*)"iastore",			0, 0x4f,0) \
	o((char*)"iconst_m1",		0, 0x02,0) \
	o((char*)"iconst_0",		0, 0x03,0) \
	o((char*)"iconst_1",		0, 0x04,0) \
	o((char*)"iconst_2",		0, 0x05,0) \
	o((char*)"iconst_3",		0, 0x06,0) \
	o((char*)"iconst_4",		0, 0x07,0) \
	o((char*)"iconst_5",		0, 0x08,0) \
	o((char*)"idiv",			0, 0x6c,0) \
	o((char*)"if_acmpeq",		2, 0xa5,0) \
	o((char*)"if_acmpne",		2, 0xa6,0) \
	o((char*)"if_icmpeq",		2, 0x9f,0) \
	o((char*)"if_icmpge",		2, 0xa2,0) \
	o((char*)"if_icmpgt",		2, 0xa3,0) \
	o((char*)"if_icmple",		2, 0xa4,0) \
	o((char*)"if_icmplt",		2, 0xa1,0) \
	o((char*)"if_icmpne",		2, 0xa0,0) \
	o((char*)"ifeq",			2, 0x99,0) \
	o((char*)"ifge",			2, 0x9c,0) \
	o((char*)"ifgt",			2, 0x9d,0) \
	o((char*)"ifle",			2, 0x9e,0) \
	o((char*)"iflt",			2, 0x9b,0) \
	o((char*)"ifne",			2, 0x9a,0) \
	o((char*)"ifnonnull",		2, 0xc7,0) \
	o((char*)"ifnull",			2, 0xc7,0) \
	o((char*)"iload",			1, 0x15,0) \
	o((char*)"iload_0",			0, 0x1a,0) \
	o((char*)"iload_1",			0, 0x1b,0) \
	o((char*)"iload_2",			0, 0x1c,0) \
	o((char*)"iload_3",			0, 0x1d,0) \
	o((char*)"imul",			0, 0x68,0) \
	o((char*)"ineg",			0, 0x74,0) \
	o((char*)"instanceof",		2, 0xc1,0) \
	o((char*)"invokedynamic",	4, 0xba,0) \
	o((char*)"invokespecial",	2, 0xb7,0) \
	o((char*)"invokestatic",	2, 0xb8,0) \
	o((char*)"invokevirtual",	2, 0xb6,0) \
	o((char*)"ior",				0, 0x80,0) \
	o((char*)"irem",			0, 0x70,0) \
	o((char*)"ireturn",			0, 0xac,0) \
	o((char*)"ishl",			0, 0x78,0) \
	o((char*)"ishr",			0, 0x7a,0) \
	o((char*)"istore",			1, 0x36,0) \
	o((char*)"istore_0",		0, 0x3b,0) \
	o((char*)"istore_1",		0, 0x3c,0) \
	o((char*)"istore_2",		0, 0x3d,0) \
	o((char*)"istore_3",		0, 0x3e,0) \
	o((char*)"isub",			0, 0x64,0) \
	o((char*)"iushr",			0, 0x7c,0) \
	o((char*)"ixor",			0, 0x82,0) \
	o((char*)"jsr",				2, 0xa8,0) \
	o((char*)"jsr_w",			4, 0xc9,0) \
	o((char*)"l2d",				0, 0x8a,0) \
	o((char*)"l2f",				0, 0x89,0) \
	o((char*)"l2i",				0, 0x88,0) \
	o((char*)"ladd",			0, 0x61,0) \
	o((char*)"laload",			0, 0x2f,0) \
	o((char*)"land",			0, 0x7f,0) \
	o((char*)"lastore",			0, 0x50,0) \
	o((char*)"lcmp",			0, 0x94,0) \
	o((char*)"lconst_0",		0, 0x09,0) \
	o((char*)"lconst_1",		0, 0x0a,0) \
	o((char*)"ldc",				1, 0x12,0) \
	o((char*)"ldc_w",			2, 0x13,0) \
	o((char*)"ldc2_w",			2, 0x14,0) \
	o((char*)"ldiv",			0, 0x6d,0) \
	o((char*)"lload",			1, 0x16,0) \
	o((char*)"lload_0",			0, 0x1e,0) \
	o((char*)"lload_1",			0, 0x1f,0) \
	o((char*)"lload_2",			0, 0x20,0) \
	o((char*)"lload_3",			0, 0x21,0) \
	o((char*)"lmul",			0, 0x69,0) \
	o((char*)"lneg",			0, 0x75,0) \
	o((char*)"new",				2, 0xbb,0) \
	o((char*)"nop",				0, 0x00,0) \
	o((char*)"pop",				0, 0x57,0) \
	o((char*)"lor",				0, 0x81,0) \
	o((char*)"lrem",			0, 0x71,0) \
	o((char*)"lreturn",			0, 0xad,0) \
	o((char*)"lshl",			0, 0x79,0) \
	o((char*)"lshr",			0, 0x7b,0) \
	o("lstore",					1, 0x37,0) \
	o("lstore_0",				0, 0x3f,0) \
	o("lstore_1",				0, 0x40,0) \
	o("lstore_2",				0, 0x41,0) \
	o("lstore_3",				0, 0x42,0) \
	o("lsub",					0, 0x65,0) \
	o("lushr",					0, 0x7d,0) \
	o("lxor",					0, 0x83,0) \
	o("monitorenter",			0, 0xc2,0) \
	o("monitorexit",			0, 0xc3,0) \
	o("putfield",				2, 0xb5,0) \
	o("putstatic",				2, 0xb3,0) \
	o("pop2",					0, 0x58,0) \
	o("ret",					1, 0xa9,0) \
	o("return",					0, 0xb1,0) \
	o("saload",					0, 0x35,0) \
	o("sastore",				0, 0x56,0) \
	o("sipush",					2, 0x11,0) \
	o("swap",					0, 0x5f,0)


void (*print_function[256])(uint8_t*, int*, std::ofstream& writerFile);

void PrintAttributes(AttributeInfo* ai, Cp_Info *cp, std::ofstream& writerFile);
void PrintCodeAttribute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile);
void PrintConstantAttribute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile);
void PrintExceptionsAttibute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile);

void Print_Access_Flag_Class(uint16_t flag, std::ofstream& writerFile){
    bool imprimiu = false;


    if(flag&0x0001){
        writerFile << "ACC_PUBLIC";
        imprimiu = true;
    }

    if((flag>>1)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_PRIVATE";
        imprimiu = true;
    }

    if((flag>>4)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_FINAL";
        imprimiu = true;
    }

    if((flag>>5)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_SUPER";
        imprimiu = true;
    }

    if((flag>>9)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_INTERFACE";
        imprimiu = true;
    }

    if((flag>>10)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_ABSTRACT";
        imprimiu = true;
    }

    if((flag>>12)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_SYNTHETIC";
        imprimiu = true;
    }

    if((flag>>13)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_ANNOTATION";
        imprimiu = true;
    }

    if((flag>>14)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_ENUM";
        imprimiu = true;
    }
}

void Print_Access_Flag_Method1(uint16_t flag, std::ofstream& writerFile){
    bool imprimiu = false;


    if(flag&1){
        writerFile << "ACC_PUBLIC";
        imprimiu = true;
    }

    if((flag>>1)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_PRIVATE";
        imprimiu = true;
    }

    if((flag>>2)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_PROTECTED";
        imprimiu = true;
    }

    if((flag>>3)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_STATIC";
        imprimiu = true;
    }

    if((flag>>4)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_FINAL";
        imprimiu = true;
    }

    if((flag>>5)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_SYNCHRONIZED";
        imprimiu = true;
    }

    if((flag>>6)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_BRIDGE";
        imprimiu = true;
    }

    if((flag>>7)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_VARARGS";
        imprimiu = true;
    }

    if((flag>>8)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_NATIVE";
        imprimiu = true;
    }

    if((flag>>9)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_ABSTRACT";
        imprimiu = true;
    }

    if((flag>>10)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_STRICT";
        imprimiu = true;
    }

    if((flag>>11)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_SYNTHETIC";
        imprimiu = true;
    }
}

void Print_Access_Flag_Method2(uint16_t flag, std::ofstream& writerFile){

    if(flag&1){
        writerFile << "public ";
    }

    if((flag>>1)&0x0001){
        writerFile << "private ";
    }

    if((flag>>2)&0x0001){
        writerFile << "protected ";
    }

    if((flag>>3)&0x0001){
        writerFile << "static ";
    }

    if((flag>>4)&0x0001){
        writerFile << "final ";
    }

    if((flag>>5)&0x0001){
        writerFile << "synchronized ";
    }

    if((flag>>6)&0x0001){
        writerFile << "bridge ";
    }

    if((flag>>7)&0x0001){
        writerFile << "varargs ";
    }

    if((flag>>8)&0x0001){
        writerFile << "native ";
    }

    if((flag>>9)&0x0001){
        writerFile << "abstract ";
    }

    if((flag>>10)&0x0001){
        writerFile << "strict ";
    }

    if((flag>>11)&0x0001){
        writerFile << "synthetic ";
    }
}

void Print_Access_Flag_Field1(uint16_t flag, std::ofstream& writerFile){

    if(flag&1){
        writerFile << "public ";
    }

    if((flag>>1)&0x0001){
        writerFile << "private ";
    }

    if((flag>>2)&0x0001){
        writerFile << "protected ";
    }

    if((flag>>3)&0x0001){
        writerFile << "static ";
    }

    if((flag>>4)&0x0001){
        writerFile << "final ";
    }

    if((flag>>6)&0x0001){
        writerFile << "volatile ";
    }

    if((flag>>7)&0x0001){
        writerFile << "transient ";
    }

    if((flag>>13)&0x0001){
        writerFile << "synthetic ";
    }

    if((flag>>14)&0x0001){
        writerFile << "enum ";
    }
}

void Print_Access_Flag_Field2(uint16_t flag, std::ofstream& writerFile){
    bool imprimiu = false;


    if(flag&1){
        writerFile << "ACC_PUBLIC";
        imprimiu = true;
    }

    if((flag>>1)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_PRIVATE";
        imprimiu = true;
    }

    if((flag>>2)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_PROTECTED";
        imprimiu = true;
    }

    if((flag>>3)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_STATIC";
        imprimiu = true;
    }

    if((flag>>4)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_FINAL";
        imprimiu = true;
    }

    if((flag>>6)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_VOLATILE";
        imprimiu = true;
    }

    if((flag>>7)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_TRANSIENT";
        imprimiu = true;
    }

    if((flag>>13)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_sYNTHETIC";
        imprimiu = true;
    }

    if((flag>>14)&0x0001){
        if(imprimiu){
            writerFile << ", ";
        }
        writerFile << "ACC_ENUM";
        imprimiu = true;
    }
}

void Print_Utf8_Ref(Cp_Info *constant_pool, uint16_t index, std::ofstream& writerFile){
    Cp_Info *cp = constant_pool+index-1;
    float aux = 0;

    if(cp->tag == 1){
        writerFile << cp->typeUTF8String.stringU;
    }else{
        switch(cp->tag){
        case(4):
            memcpy(&aux, &(cp->typeFloat), sizeof(float));
            writerFile << aux;
            break;
        case (7):
            Print_Utf8_Ref(constant_pool, cp->typeClassInfo, writerFile);
            break;
        case(9):
            Print_Utf8_Ref(constant_pool, cp->typeFieldRef>>16, writerFile);
            writerFile << ".";
            Print_Utf8_Ref(constant_pool, (cp->typeFieldRef<<16)>>16, writerFile);
            break;
        case(10):
            Print_Utf8_Ref(constant_pool, cp->typeMethodRef>>16, writerFile);
            writerFile << ".";
            Print_Utf8_Ref(constant_pool, (cp->typeMethodRef<<16)>>16, writerFile);
            break;
        case(12):
            Print_Utf8_Ref(constant_pool, cp->typeNameAndType>>16, writerFile);
            writerFile << ".";
            Print_Utf8_Ref(constant_pool, (cp->typeNameAndType<<16)>>16, writerFile);
            break;
        case(8):
            Print_Utf8_Ref(constant_pool, (uint16_t) cp->typeStringRef, writerFile);
            break;
        case(11):
            Print_Utf8_Ref(constant_pool, cp->typeInterfaceRef>>16, writerFile);
            writerFile << ".";
            Print_Utf8_Ref(constant_pool, (cp->typeInterfaceRef<<16)>>16, writerFile);
            break;
        default:
            break;
        }
    }

}

void Print_Constant_Type(Cp_Info *constant_pool, uint16_t index, std::ofstream& writerFile, bool cem = false){
    Cp_Info *cp = constant_pool+index-1;

    switch(cp->tag){
    case(7):
        writerFile << "Class\t\t\t#" << cp->typeClassInfo << "\t\t\t// ";
        Print_Utf8_Ref(constant_pool, index, writerFile);
        writerFile << std::endl;
        break;
    case(9):{
        uint16_t low = ((cp->typeFieldRef<<16)>>16);
        uint16_t high = cp->typeFieldRef>>16;
        writerFile << "Fieldref\t\t#" << high << ".#" << low << "\t\t\t// ";
        Print_Utf8_Ref(constant_pool, index, writerFile);
        writerFile << std::endl;
        }
        break;
    case(10):
        {
        uint16_t high = cp->typeMethodRef>>16;
        uint16_t low = ((cp->typeMethodRef<<16)>>16);
        if(cem){
            writerFile << "Methodref\t\t#" << high << ".#" << low << "\t\t// ";
        }else{
            writerFile << "Methodref\t\t#" << high << ".#" << low << "\t\t\t// ";
        }
        Print_Utf8_Ref(constant_pool, index, writerFile);
        writerFile << std::endl;
        }
        break;
    case(11):
        {
        uint16_t high = cp->typeInterfaceRef>>16;
        uint16_t low = (cp->typeInterfaceRef<<16)>>16;
        writerFile << "InterfaceMethodref\t#" << high << ".#"<< low << "\t\t\t// ";
        Print_Utf8_Ref(constant_pool, index, writerFile);
        writerFile << std::endl;
        }
        break;
    case(8):
        writerFile << "String\t\t\t#" << cp->typeStringRef << "\t\t\t// ";
        Print_Utf8_Ref(constant_pool, index, writerFile);
        writerFile << std::endl;
        break;
    case(3):
        writerFile << "Integer\t\t\t" << cp->typeInt << std::endl;
        break;
    case(4):{
        float aux;
        memcpy(&aux, &(cp->typeFloat), sizeof(float));
        writerFile << "Float\t\t\t" << aux << std::endl;
        }
        break;
    case(5):{
        long auxl;
        memcpy(&auxl, &(cp->typeLong), sizeof(long));
        writerFile << "Long\t\t\t" << auxl << std::endl;
        }
        break;
    case(6):{
        double auxd;
        memcpy(&auxd, &(cp->typeDouble), sizeof(double));
        writerFile << "Double\t\t\t" << auxd << std::endl;
    }
        break;
    case(12):
        {
        uint16_t high = cp->typeNameAndType>>16;
        uint16_t low = (cp->typeNameAndType<<16)>>16;
        if(cem){
            writerFile <<"NameAndType\t\t#" << high << ".#" << low << "\t\t// ";
        }else{
            writerFile <<"NameAndType\t\t#" << high << ".#" << low << "\t\t\t// ";
        }

        Print_Utf8_Ref(constant_pool, index, writerFile);
        writerFile << std::endl;
        }
        break;
    case(1):
        writerFile << "Utf8\t\t\t" << cp->typeUTF8String.stringU << std::endl;
        break;
    case(15):
        writerFile << "MethodHandle\t\t" << cp->typeMethodHandle.type_descriptor << std::endl;
        break;
    case(16):
        writerFile << "MethodType\t\t" << cp->typeMethodType << std::endl;
        break;
    case(18):
        writerFile << "InvokeDynamic\t\t" << cp->typeInvokeDynamic << std::endl;
        break;
    default:
        writerFile << std::endl;
        break;
    }

}

void Initialize_Print_Functions(std::ofstream& writerFile){
	#define o(mnemonic,operands,opcode, todo) \
		print_function[opcode] = [](uint8_t* code, int* index, std::ofstream& writerFile){ \
			int64_t kappa = 0; \
			int line_number = *index; \
			for(int j = 0; j < operands; j++){ \
				kappa = (kappa<<8) | code[++(*index)]; \
			} \
			switch(operands){ \
			case (1): \
				if((kappa&0x80)>>7 == 1) kappa|=0xffffffffffffff00; \
				break; \
			case (2): \
				if((kappa&0x8000)>>15 == 1) kappa|=0xffffffffffff0000; \
				break; \
			case (4): \
				if((kappa&0x80000000)>>15 == 1) kappa|=0xffffffff00000000; \
				break; \
			case (8): \
				break; \
			} \
			writerFile << line_number << ":   " << mnemonic << ", " << kappa << std::endl; \
		};
		LIST_INSTRUCTIONS(o)
#undef o
	print_function[0x84] = [](uint8_t* code, int* index, std::ofstream& writerFile){
                    uint16_t codeI = 0;
                    writerFile << *index << ":   iinc, ";
					(*index)++;
					codeI = code[(*index)];
					writerFile << codeI << ", " ;
					(*index)++;
					codeI = code[(*index)];
					writerFile << codeI << " " << std::endl;
				};

	print_function[0xb9] = [](uint8_t* code, int* index, std::ofstream& writerFile){
                    writerFile << *index << ":   invokeinterface, ";
					//printf("%d:   invokeinterface, ", *index);
					int16_t indexa = 0;

					(*index)++;
					indexa = code[(*index)]<<8;
					(*index)++;
					indexa += code[(*index)];
					(*index)++;
					uint16_t codeI = code[(*index)];
					writerFile << indexa << ", " << codeI << std::endl;
                    //printf("%d, %d\n", indexa, code[(*index)]);
                    (*index)++;
				};
	print_function[0xab] = [](uint8_t* code, int* index, std::ofstream& writerFile){
                int line_number = *index;
				while ((*index) % 4 != 0)
					++(*index);
				uint32_t default_byte = 0;
				(*index)++;
				default_byte = ((code[(*index)]) << 24);
				(*index)++;
                default_byte += ((code[(*index)]) << 16);
                (*index)++;
                default_byte += ((code[(*index)]) << 8);
                (*index)++;
                default_byte += (code[(*index)]);
                (*index)++;

				uint32_t npairs = 0;
				(*index)++;
				npairs = ((code[(*index)]) << 24);
				(*index)++;
				npairs += ((code[(*index)]) << 16);
				(*index)++;
				npairs += ((code[(*index)]) << 8);
				(*index)++;
				npairs+= (code[(*index)]);

				writerFile <<  line_number << ": lookupswitch, " << default_byte << ", " << npairs << std::endl;
				//printf("%d: lookupswitch, %d, %d\n", line_number, default_byte, npairs);

				for (uint32_t k = 0; k < npairs; k++) {
					uint32_t key = 0;
					(*index)++;
					key = ((code[(*index)]) << 24);
					(*index)++;
					key += ((code[(*index)]) << 16);
					(*index)++;
					key += ((code[(*index)]) << 8);
					(*index)++;
					key += (code[(*index)]);

					uint32_t value = 0;
					(*index)++;
					value = ((code[(*index)]) << 24);
					(*index)++;
					value += ((code[(*index)]) << 16);
					(*index)++;
					value += ((code[(*index)]) << 8);
					(*index)++;
					value += (code[(*index)]);

                    writerFile << "(key: " << key << ", value: " << value << ")" << std::endl;
					//printf("(key : %d, value: %d)\n", key, value);
				}
			};
    print_function[0xc5] = [](uint8_t* code, int* index, std::ofstream& writerFile){
                writerFile << *index << ":   multinewarray ";
				//printf("%d:   multianewarray ",*index);
				uint16_t indexa = 0;
				uint16_t codeI = 0;
				(*index)++;
				indexa = ((code[(*index)])<<8);
				(*index)++;
				indexa += (code[(*index)]);
				(*index)++;

				codeI = (code[(*index)]);
				writerFile << indexa << " , " << codeI << std::endl;
				//printf("%d , %d\n", indexa, codeI);
	};
	print_function[0xbc] = [](uint8_t* code, int* index, std::ofstream& writerFile){
                writerFile << *index << ":	newarray ";
				//printf("%d:	newarray ",*index);
				(*index)++;
				int8_t type = (code[(*index)]);
				switch (type){
				case 4:
				    writerFile << "T_BOOLEAN" << std::endl;
					//printf("T_BOOLEAN\n");
					break;
				case 5:
				    writerFile << "T_CHAR" << std::endl;
					//printf("T_CHAR\n");
					break;
				case 6:
				    writerFile << "T_FLOAT" << std::endl;
					//printf("T_FLOAT\n");
					break;
				case 7:
					writerFile << "T_DOUBLE" << std::endl;
					//printf("T_DOUBLE\n");
					break;
				case 8:
				    writerFile << "T_BYTE" << std::endl;
					//printf("T_BYTE\n");
					break;
				case 9:
				    writerFile << "T_SHORT" << std::endl;
					//printf("T_SHORT\n");
					break;
				case 10:
				    writerFile << "T_INT" << std::endl;
					//printf("T_INT\n");
					break;
				case 11:
				    writerFile << "T_LONG" << std::endl;
					//printf("T_LONG\n");
					break;
				}
	};

	print_function [0xaa] = [](uint8_t* code, int* index, std::ofstream& writerFile) {
                int line_number = *index;
				while (*index % 4 != 0)
					++(*index);
				uint32_t default_byte = 0;
				(*index)++;
				default_byte = ((code[(*index)]) << 24);
				(*index)++;
				default_byte += ((code[(*index)]) << 16);
				(*index)++;
				default_byte +=((code[(*index)]) << 8);
				(*index)++;
				default_byte +=(code[(*index)]);

                (*index)++;
				int32_t high = ((code[++(*index)]) << 24);
				(*index)++;
				high += ((code[++(*index)]) << 16);
				(*index)++;
				high += ((code[++(*index)]) << 8);
				(*index)++;
				high += (code[++(*index)]);

                (*index)++;
				int32_t low = ((code[(*index)])<< 24);
				(*index)++;
				low += ((code[(*index)]) << 16);
				(*index)++;
				low += ((code[(*index)]) << 8);
				(*index)++;
				low += (code[(*index)]);

				writerFile << line_number << ":	tableswitch " << default_byte << ", " << high << ", " << low << std::endl;
				//printf("%d:	tableswitch %d, %d, %d\n",line_number, default_byte, high, low);

				for (int k = 0; k < high-low+1; k++) {
                    (*index)++;
					uint32_t offset = ((code[(*index)])<< 24);
					(*index)++;
					offset += ((code[(*index)]) << 16);
					(*index)++;
					offset += ((code[(*index)]) << 8);
					(*index)++;
					offset += (code[(*index)]);

					writerFile << "offset: " << offset << std::endl;
					//printf("offset : %d\n", offset);
				}
			};

			print_function[0xc4] = [](uint8_t* code, int* index, std::ofstream& writerFile){
			    writerFile << *index << ": wide ";
				//printf("%d:	wide ", *index);
				(*index)++;
				uint8_t op = (code[(*index)]);
				if (op == 0x84) {
                    uint16_t arg1 = 0, arg2 = 0;
                    (*index)++;
                    arg1 = ((code[(*index)])<< 8);
                    (*index)++;
                    arg1 += ((code[(*index)]));

                    (*index)++;
					arg2 = ((code[(*index)]) << 8);
					(*index)++;
					arg2 += (code[(*index)]);
					writerFile << "iinc " << arg1 << ", " << arg2 << std::endl;
					//printf("iinc %d, %d\n", arg1, arg2);
				}
				else {
				    (*index)++;
				    uint16_t arg1 = ((code[(*index)]) << 8);
				    (*index)++;
                    arg1 += (code[++(*index)])  ;
					writerFile << "opcode " << std::hex << op << std::dec << ", " << arg1 << std::endl;
					//printf("opcode %x, %d\n", op, arg1);
				}
			};

}

void Print_Javap_Format(ClassInfo * classInfo, char* filename){
    std::ofstream writerFile;
    writerFile.open(filename);
    Initialize_Print_Functions(writerFile);
    writerFile << "class: ";
    //printf("class: ");
    Print_Utf8_Ref(classInfo->constant_pool, classInfo->this_class, writerFile);
    writerFile << std::endl;
    writerFile << "super class: ";
    //printf("super class: ");
    Print_Utf8_Ref(classInfo->constant_pool, classInfo->super_class, writerFile);
    writerFile << std::endl;
    //printf("\n");

    writerFile << "  magic number: " << std::hex << classInfo->magic_number << std::dec <<std::endl;
    //printf("  magic number: %x\n", classInfo->magic_number);

    writerFile << "  minor version: " << classInfo->minor_version << std::endl;
    //printf("  minor version: %d\n", classInfo->minor_version);

    writerFile << "  major version: " << classInfo->major_version << std::endl;
    //printf("  major version: %d\n", classInfo->major_version);

    writerFile << "  flags: ";
    //printf("  flags: ");
    Print_Access_Flag_Class(classInfo->access_flags, writerFile);
    writerFile << std::endl;
    //printf("\n");

    writerFile << "Constant pool:" << std::endl;
    //printf("Constant pool:\n");

    //Loop para printar toda a constant pool
    for(uint16_t i = 1; i <= classInfo->cp_size -1; i++){
        if (i <= 9){
            writerFile << "   #" << i << " = ";
            //printf("   #%d = ", i);
            Print_Constant_Type(classInfo->constant_pool, i, writerFile);
        }else if(i <= 99){
            writerFile << "  #" << i << " = ";
            //printf("  #%d = ", i);
            Print_Constant_Type(classInfo->constant_pool, i, writerFile);
        }else{
            writerFile << " #" << i << " = ";
            //printf(" #%d = ", i);
            Print_Constant_Type(classInfo->constant_pool, i, writerFile, true);
        }
    }
    writerFile << std::endl;
    //printf("\n");

    for(int i = 0; i < classInfo->interface_count ; i++){
        writerFile << "interface " << i << ": ";
        //printf("interface %d: ", i);
        Print_Utf8_Ref(classInfo->constant_pool, *(classInfo->interface_table+i), writerFile);
        writerFile << std::endl;
        //printf("\n");
    }

    writerFile << std::endl << "{" << std::endl;
    //printf("\n{\n");
    /******************************************************************************************
    *	PRINT FIELDS                                                                          *
    *	AQUI 																				  *
    *																						  *
    ******************************************************************************************/
    for(int i=0; i<classInfo->field_count; i++){
        FieldInfo *field = (classInfo->fields+i);

        Print_Access_Flag_Field1(field->access_flags, writerFile);
        Print_Utf8_Ref(classInfo->constant_pool, field->name_index, writerFile);
        writerFile << std::endl;
        //printf("\n");

        writerFile << "     descriptor: ";
        //printf("     descriptor: ");
        Print_Utf8_Ref(classInfo->constant_pool, field->descriptor_index, writerFile);
        writerFile << std::endl;
        //printf("\n");

        writerFile << "     flags: ";
        //printf("     flags: ");
        Print_Access_Flag_Field2(field->access_flags, writerFile);
        writerFile << std::endl;
        //printf("\n");

        for (int i = 0; i < field->attributes_count; i++) {
            writerFile << "Attribute " << i+1 << std::endl;
            //printf("Attribute %d\n",i+1);
			PrintAttributes(field->attributes+ i, classInfo->constant_pool, writerFile);
		}
		writerFile << std::endl;
		//printf("\n");
    }

    /******************************************************************************************
    *	PRINT MÉTODOS                                                                         *
    *	AQUI 																				  *
    *																						  *
    ******************************************************************************************/
    //Loop para printar os m�todos
    for(uint16_t i = 0; i < classInfo->methods_count; i++){
        MethodInfo *method = (classInfo->methods+i);

        Print_Access_Flag_Method2(method->access_flags, writerFile);
        Print_Utf8_Ref(classInfo->constant_pool, method->name_index, writerFile);
        writerFile << std::endl;
        //printf("\n");

        writerFile << "     descriptor: ";
        //printf("     descriptor: ");
        Print_Utf8_Ref(classInfo->constant_pool, method->descriptor_index, writerFile);
        writerFile << std::endl;
        //printf("\n");

        writerFile << "     flags: ";
        //printf("     flags: ");
        Print_Access_Flag_Method1(method->access_flags, writerFile);
        writerFile << std::endl;
        //printf("\n");

		for (int i = 0; i < method->attributes_count; i++) {
			PrintAttributes(method->attributes+ i, classInfo->constant_pool, writerFile);
		}
    }

    writerFile << "}" << std::endl << std::endl;
    //printf("}\n\n");

    /******************************************************************************************
    *	PRINTAR ATTRIBUTES                                                                    *
    *	AQUI 																				  *
    *																						  *
    ******************************************************************************************/
    for(int i = 0; i < classInfo->attributes_count; i++){
        writerFile << "Atributo " << i+1;
        //printf("Atributo %d",i+1);
        PrintAttributes(classInfo->attributes+i, classInfo->constant_pool, writerFile);
        writerFile << std::endl;
        //printf("\n");
    }
    writerFile.close();
}

void PrintCodeAttribute(AttributeInfo * ai, Cp_Info * cp, std::ofstream& writerFile){
    writerFile << "stack=" << ai->codeAttribute->max_stack << ", locals=" << ai->codeAttribute->max_locals
        << "\t// Code length: " << ai->codeAttribute->code_length << std::endl;
	//printf("stack=%d, locals=%d\t// Code length: %d\n",
        //ai->codeAttribute->max_stack,ai->codeAttribute->max_locals, ai->codeAttribute->code_length);

	for (int i = 0; (uint32_t) i < ai->codeAttribute->code_length; i++) {
		print_function[ai->codeAttribute->code[i]](ai->codeAttribute->code, &i, writerFile);
	}

	writerFile << std::endl << std::endl << "Exception table length: " << ai->codeAttribute->exception_table_length << std::endl;
	//printf("\n\nException table lenght: %d\n", ai->codeAttribute->exception_table_length);
	for (int i = 0; i < ai->codeAttribute->exception_table_length; i++) {
        writerFile << "	start_pc: " << (ai->codeAttribute->exception_table + i)->start_pc << std::endl;
		//printf("	start_pc: %d\n", (ai->codeAttribute->exception_table + i)->start_pc);
        writerFile << "	end_pc: " << (ai->codeAttribute->exception_table + i)->end_pc << std::endl;
		//printf("	end_pc: %d\n", (ai->codeAttribute->exception_table + i)->end_pc);
		writerFile << "	handler_pc: " << (ai->codeAttribute->exception_table + i)->handler_pc << std::endl;
		//printf("	handler_pc: %d\n", (ai->codeAttribute->exception_table + i)->handler_pc);
		writerFile << "	catch_type: " << (ai->codeAttribute->exception_table + i)->catch_type << std::endl;
		//printf("	catch_type: %d\n", (ai->codeAttribute->exception_table + i)->catch_type);
	}

    writerFile << "Attributes count " << ai->codeAttribute->attributes_count << std::endl;
	//printf("Attributes count %d\n", ai->codeAttribute->attributes_count);
	for (int i = 0; i < ai->codeAttribute->attributes_count; i++) {
		PrintAttributes(ai->codeAttribute->attributes + i, cp, writerFile);
	}
}

void PrintConstantAttribute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile) {
	writerFile << "Constant Value: #" << ai->constvalueAttribute->constantValue_index;
	//printf("Constant Value: #%d", ai->constvalueAttribute->constantValue_index);
	switch(cp[ai->constvalueAttribute->constantValue_index-1].tag){
    case(8):
        writerFile << cp[ai->constvalueAttribute->constantValue_index-1].typeUTF8String.stringU << std::endl;
        //printf("%s\n", cp[ai->constvalueAttribute->constantValue_index-1].typeUTF8String.string);
        break;
    case(3):
        writerFile << "\t\t" << cp[ai->constvalueAttribute->constantValue_index-1].typeInt << std::endl;
        //printf("\t\t%d\n",cp[ai->constvalueAttribute->constantValue_index-1].typeInt);
        break;
    case (4):{
			float aux = 0;
			memcpy(&aux, &((cp + ai->constvalueAttribute->constantValue_index - 1)->typeFloat), sizeof(float));
			writerFile << " "<< aux << std::endl;
			//printf(" %f\n", aux);
			break;
		}
    case(5):
        writerFile << "\t\t\t"<< (cp[ai->constvalueAttribute->constantValue_index-1].typeLong) << std::endl;
        break;
    case(6):
        double aux;
        memcpy(&aux, &(cp[ai->constvalueAttribute->constantValue_index-1].typeDouble), sizeof(double));
        writerFile << " "<< aux << std::endl;
        break;

	}
}

void PrintExceptionsAttibute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile) {
    writerFile << "Number of Exceptions: " << ai->exceptionsAttribute->numberof_exceptions << std::endl;
	//printf("Number of Exceptions: %d\n", ai->exceptionsAttribute->numberof_exceptions);
	for (int i = 0; i < ai->exceptionsAttribute->numberof_exceptions; i++) {
        writerFile << "	Index: " << ai->exceptionsAttribute->exception_index_table[i] << std::endl;
		//printf("	Index: %d\n", ai->exceptionsAttribute->exception_index_table[i]);
	}
}

void printLineNumberTableAttribute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile){
    writerFile << "  Table length: " << ai->lineNumberTableAttribute->line_number_table_length << std::endl;
	//printf("  Table length: %d\n", ai->lineNumberTableAttribute->line_number_table_length);

	for(int i = 0; i < ai->lineNumberTableAttribute->line_number_table_length; i++){
		writerFile << "     Line " << i << "->\t" << (ai->lineNumberTableAttribute->line_number_table + i)->start_pc << ": "
		<< (ai->lineNumberTableAttribute->line_number_table + i)->line_number << std::endl;

		//printf("     Line %d->\t%d: %d\n", i,
		//(ai->lineNumberTableAttribute->line_number_table + i)->start_pc,
		//(ai->lineNumberTableAttribute->line_number_table + i)->line_number);
	}
	writerFile << std::endl;
	//printf("\n");
}

void printLocalVariableTableAttribute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile){
    writerFile << "	Table length: " << ai->localVariableAttribute->local_variable_table_length << std::endl;
	//printf("	Table length: %d\n", ai->localVariableAttribute->local_variable_table_length);
	writerFile << "N	|	Start_PC	|	Length	|	Name_Index	|	Descriptor_Index	|	Index	|" << std::endl;
	//printf("N	|	Start_PC	|	Length	|	Name_Index	|	Descriptor_Index	|	Index	|\n");
	for(int i = 0; i < ai->lineNumberTableAttribute->line_number_table_length; i++){
    writerFile << i << "	|	"
        << (ai->localVariableAttribute->local_variable_table + i)->start_pc << "		|	"
        << (ai->localVariableAttribute->local_variable_table + i)->length << "	|	"
        << (ai->localVariableAttribute->local_variable_table + i)->name_index << "		|	"
        << (ai->localVariableAttribute->local_variable_table + i)->descriptor_index << "			|	"
        << (ai->localVariableAttribute->local_variable_table + i)->index << "	|" << std::endl;
	//printf("%d	|	%d		|	%d	|	%d		|	%d			|	%d	|\n",i,
		//(ai->localVariableAttribute->local_variable_table + i)->start_pc,
		//(ai->localVariableAttribute->local_variable_table + i)->length,
		//(ai->localVariableAttribute->local_variable_table + i)->name_index,
		//(ai->localVariableAttribute->local_variable_table + i)->descriptor_index,
		//(ai->localVariableAttribute->local_variable_table + i)->index);
	}
	writerFile << std::endl;
	//printf("\n");
}

void printInnerClassesAttribute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile){
    writerFile << "	Number of Classes: " << ai->innerClassesAttribute->number_of_classes << std::endl;
	//printf("	Number of Classes: %d\n", ai->innerClassesAttribute->number_of_classes);
	for(int i = 0; i < ai->innerClassesAttribute->number_of_classes; i++){
        writerFile << "		" << (ai->innerClassesAttribute->classes + i)->inner_class_info_index << std::endl;
		//printf("		%d\n", (ai->innerClassesAttribute->classes + i)->inner_class_info_index);
        writerFile << "		" << (ai->innerClassesAttribute->classes + i)->outer_class_info_index << std::endl;
		//printf("		%d\n", (ai->innerClassesAttribute->classes + i)->outer_class_info_index);
		writerFile << "		" << (ai->innerClassesAttribute->classes + i)->inner_name_index << std::endl;
		//printf("		%d\n", (ai->innerClassesAttribute->classes + i)->inner_name_index);
		writerFile << "		" << (ai->innerClassesAttribute->classes + i)->inner_class_access_flags << std::endl;
		//printf("		%d\n", (ai->innerClassesAttribute->classes + i)->inner_class_access_flags);
	}
}

void printSourceFileAttribute(AttributeInfo* ai, Cp_Info* cp, std::ofstream& writerFile){
    writerFile << "	SourceFile index: #" << ai->sourceFileAttribute->sourcefile_index << " ";
	//printf("	SourceFile index: #%d ", ai->sourceFileAttribute->sourcefile_index);
	Print_Utf8_Ref(cp, ai->sourceFileAttribute->sourcefile_index, writerFile);
	writerFile << std::endl;
	//printf("\n");
}

#define PRINT_FUNCTIONS(printype) \
printype("ConstantValue", PrintConstantAttribute(ai, cp, writerFile))\
printype("Code", PrintCodeAttribute(ai, cp, writerFile))\
printype("Exceptions", PrintExceptionsAttibute(ai, cp, writerFile))\
printype("LineNumberTable", printLineNumberTableAttribute(ai, cp, writerFile))\
printype("LocalVariableTable", printLocalVariableTableAttribute(ai, cp, writerFile))\
printype("InnerClasses", printInnerClassesAttribute(ai, cp, writerFile))\
printype("SourceFile", printSourceFileAttribute(ai, cp, writerFile))


void PrintAttributes(AttributeInfo* ai, Cp_Info *cp, std::ofstream& writerFile) {
	char type[100];
	strcpy(type, (char*)cp[ai->name_index - 1].typeUTF8String.stringU);

    writerFile << type << ":\t//Attribute length: " << ai->length << std::endl;
	//printf("%s:\t//Attribute length: %d\n ", type, ai->length);
#define printype(name,function) if(strcmp(name,type)==0) { function; }
	PRINT_FUNCTIONS(printype) {}
#undef printype

}

