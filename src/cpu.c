#include <inttypes.h>
#include "cpu.h"
#include "utils.h"

RegisterFile newRegisterFile(){
    RegisterFile registerFile;

    registerFile.a = 0;
    registerFile.b = 0;
    registerFile.c = 0;
    registerFile.d = 0;
    registerFile.e = 0;
    registerFile.f = 0;
    registerFile.h = 0;
    registerFile.l = 0;

    registerFile.ir = 0;
    registerFile.ie = 0;

    registerFile.pc = 0;
    registerFile.sp = 0;

    return registerFile;
}

void updateFlags(Cpu* cpu){
    uint8_t *f= &cpu->registerFile.f;

    // flag register
    // 7 6 5 4 3 2 1 0
    // Z N H C 0 0 0 0
    cpu->flags.z = extractBit(*f, 7);
    cpu->flags.n = extractBit(*f, 6);
    cpu->flags.h = extractBit(*f, 5);
    cpu->flags.c = extractBit(*f, 4);

}

Cpu newCPU(){
    Cpu cpu;
    cpu.registerFile = newRegisterFile();
    updateFlags(&cpu);
    return cpu;
}