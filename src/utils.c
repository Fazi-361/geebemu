#include <inttypes.h>
#include <stdbool.h>

#include "utils.h"

_Bool utils_extractBit(uint8_t num, int position) {
    if (position < 0 || position > 8){
        return false;
    }

    uint8_t mask = 1 << position;
    _Bool extracted_bit = (num & mask) >> position;

    return extracted_bit;
}

uint8_t utils_extractByteHi(uint16_t num){
    return (num & 0xFF00) >> 8;
}

uint8_t utils_extractByteLo(uint16_t num){
    return num & 0x00FF;
}

uint16_t utils_mergeBytesBE(uint8_t lo, uint8_t hi){
    return (hi << 8) | lo;
}

uint16_t utils_mergeBytesLE(uint8_t lo, uint8_t hi){
    return (lo << 8) | hi;
}