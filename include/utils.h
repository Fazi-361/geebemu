#include <inttypes.h>
#include <stdbool.h>

void utils_setBit (uint8_t *num, int position);

void utils_unsetBit (uint8_t *num, int position);

/**
 * @brief Extracts a bit from a 8 bit integer in the specified location
 * @param num The byte to operate on
 * @param position Number 0-7 that specifies the location of the bit. 0 = LSB
 * @return `true` if the bit in the specified location is 1, else `false` 
 * @note The function always returns 0 if `position` is outside of the 0-7 range is given.
 */
_Bool utils_extractBit(uint8_t num, int position);

uint8_t utils_extractByteHi(uint16_t num);

uint8_t utils_extractByteLo(uint16_t num);

uint16_t utils_mergeBytesBE(uint8_t lo, uint8_t hi);

uint16_t utils_mergeBytesLE(uint8_t lo, uint8_t hi);