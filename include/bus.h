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
MemoryMap newMemoryMap() {
    MemoryMap mm;

    mm.rom.bank00  = {0x0000, 0x3FFF};
    mm.rom.bankNN  = {0x4000, 0x7FFF};
    mm.vRam        = {0x8000, 0x9FFF};
    mm.exRam       = {0xA000, 0xBFFF};
    mm.wRam        = {0xC000, 0xDFFF};
    mm.echoRam     = {0xE000, 0xFDFF};
    mm.oam         = {0xFE00, 0xFE9F};
    mm.forbidden   = {0xFEA0, 0XFEFF};
    mm.ioRegisters = {0xFF00, 0xFF7F};
    mm.hRam        = {0xFF80, 0xFFFE};
    mm.enableIE    = {0xFFFF, 0xFFFF};

    return mm;
}

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