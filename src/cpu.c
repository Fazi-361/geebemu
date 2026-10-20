#include <stdio.h>
#include <inttypes.h>
#include "cpu.h"
#include "utils.h"

RegisterFile newRegisterFile() {
    RegisterFile registerFile;

    registerFile.af.value = 0;
    registerFile.bc.value = 0;
    registerFile.de.value = 0;
    registerFile.hl.value = 0;

    registerFile.ir = 0;
    registerFile.ie = 0;

    registerFile.pc = 0;
    registerFile.sp = 0;

    return registerFile;
}

void updateFlags(Cpu* cpu) {
    uint8_t* f = &cpu->registerFile.af.lo;

    // flag register
    // 7 6 5 4 3 2 1 0
    // Z N H C 0 0 0 0
    cpu->flags.z = extractBit(*f, 7);
    cpu->flags.n = extractBit(*f, 6);
    cpu->flags.h = extractBit(*f, 5);
    cpu->flags.c = extractBit(*f, 4);

}

Cpu newCPU() {
    Cpu cpu;
    cpu.registerFile = newRegisterFile();
    updateFlags(&cpu);
    return cpu;
}

void dumpRegisters(Cpu *cpu, char buffer[], size_t bufferSize) {
    RegisterFile* r = &cpu->registerFile;
    snprintf(buffer, bufferSize, 
        "a: %02x\tf: %02x\n"
        "b: %02x\tc: %02x\tbc: %04x\n"
        "d: %02x\te: %02x\tde: %04x\n"
        "h: %02x\tl: %02x\thl: %04x\n"
        "ir: %02x\tie: %02x\n"
        "pc: %02x\tsp: %02x",

        r->af.hi, r->af.lo, 
        r->bc.hi, r->bc.lo, r->bc.value, 
        r->de.hi, r->de.lo, r->de.value,
        r->hl.hi, r->hl.lo, r->hl.value,
        r->ir, r->ie, r->pc, r->sp
    );
}

void load_r8_n8(uint8_t *r8, uint8_t n8) {
    *r8 = n8;
}