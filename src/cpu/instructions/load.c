#include <stdio.h>
#include <inttypes.h>
#include "cpu.h"
#include "utils.h"
#include "bus.h"

void load_r8_n8(uint8_t *r8, uint8_t n8)         { *r8 = n8; }
void load_r8_r8(uint8_t *r8_1, uint8_t *r8_2)    { *r8_1 = *r8_2; }
void load_r16_n16(Register16* r16, uint16_t n16) { r16->value = n16; }

void load_ahl_r8(uint8_t* addressBus, Register16* hl, uint8_t* r8){
    bus_write8(addressBus, hl->value, *r8);
}

void load_ahl_n8(uint8_t* addressBus, Register16* hl, uint8_t n8){
    bus_write8(addressBus, hl->value, n8);
}

void load_r8_ahl(uint8_t* addressBus, uint8_t* r8, Register16* hl){
    *r8 = bus_read8(addressBus, hl->value);    
}
