#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "cpu.h"

void rlc_r8(uint8_t* r8){
    return (*r8 << 1) | (*r8 >> 7);
}

void rrc_r8(uint8_t* r8){
    return (*r8 >> 1) | (*r8 << 7);
}