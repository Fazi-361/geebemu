#include <inttypes.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    uint16_t start;
    uint16_t end;
} Range16;

typedef struct {
    Range16 bank00;
    Range16 bankNN;
} RomBank;

/**
 * @brief Struct that represents the Gameboy Memory Map.
 * Look at https://gbdev.io/pandocs/Memory_Map.html for more info
 * 
 */
typedef struct {    

    RomBank rom;
    Range16 vRam;
    Range16 exRam;
    Range16 wRam;

    Range16 echoRam;
    Range16 oam;
    Range16 forbidden;
    Range16 ioRegisters;
    Range16 hRam;

    Range16 enableIE;

} MemoryMap;


/**
 * @brief Returns a new MemoryMap
 * 
 * @return MemoryMap 
 */
MemoryMap newMemoryMap();

/**
 * @brief Writes a byte in the specified memory location
 * 
 * @param addressBus Pointer to the address bus
 * @param location location to write the byte in
 * @param n Number to load 
 */
void bus_write8(uint8_t* addressBus, uint16_t location, uint8_t n);

/**
 * @brief Writes 2 bytes in the specified memory location
 * 
 * @param addressBus Pointer to the address bus
 * @param location location to write in
 * @param n Number to load 
 */
void bus_write16(uint8_t* addressBus, uint16_t location, uint16_t n);

/**
 * @brief Reads a byte in the specified memory location
 * 
 * @param addressBus Pointer to the address bus
 * @param location location to write in
 * @return uint8_t The read byte
 */
uint8_t bus_read8(uint8_t* addressBus, uint16_t location);

/**
 * @brief Reads a byte in the specified memory location
 * 
 * @param addressBus Pointer to the address bus
 * @param location location to write in
 * @return `uint_8` The read two bytes, in LITTLE ENDIAN (0x12, 0x34 are combined in 0x3412)
 */
uint16_t bus_read16(uint8_t* addressBus, uint16_t location);