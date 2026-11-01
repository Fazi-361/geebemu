#include <stdio.h>
#include <inttypes.h>
#include "cpu.h"
#include "utils.h"
#include "bus.h"

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
    cpu->flags.z = utils_extractBit(*f, 7);
    cpu->flags.n = utils_extractBit(*f, 6);
    cpu->flags.h = utils_extractBit(*f, 5);
    cpu->flags.c = utils_extractBit(*f, 4);

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


// Fetch Decode Execute: Big function incoming!

uint8_t fetchByte(Cpu *cpu){
    uint8_t byte = bus_read8(cpu->addressBus, cpu->registerFile.pc++);
    return byte;
}

uint16_t fetch16(Cpu *cpu){
    return bus_read16(cpu->addressBus, cpu->registerFile.pc++);
}

void advance(Cpu *cpu){
    uint16_t opcode;
    uint8_t op1 = fetchByte(cpu);

    switch (op1){
        case 0x00: {
            break;
        }

        // RLCA
        case 0x07:{
            rlc_r8(&cpu->registerFile.af.hi);
            break;
        }

        // RRCA
        case 0x0F:{
            rrc_r8(&cpu->registerFile.af.hi);
            break;
        }

        // RLA
        case 0x17: {
            cpu->registerFile.af.hi << 1;
        }

        // RRA
        case 0x1F: {
            cpu->registerFile.af.hi >> 1;
        }

        //

        // TODO: change to HALT
        case 0x76: {
            break;
        }

        // TODO: change to DI
        case 0xF3: {
            break;
        }

        // TODO: change to EI
        case 0xFB: {
            break;
        }


    }
}