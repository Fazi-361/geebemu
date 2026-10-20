#include <inttypes.h>
#include <stdbool.h>

#include "utils.h"

_Bool extractBit(uint8_t num, int position) {
    if (position < 0 || position > 8){
        return false;
    }

    uint8_t mask = 1 << position;
    _Bool extracted_bit = (num & mask) >> position;

    return extracted_bit;
}