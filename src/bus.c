#include <inttypes.h>
#include <stdbool.h>
#include <math.h>

#include "bus.h"
#include "utils.h"

MemoryMap newMemoryMap() {
    MemoryMap mm;

    // mm.rom.bank00  = {0x0000, 0x3FFF};
    mm.rom.bank00  = (Range16) {0x0000, 0x3FFF};
    mm.rom.bankNN  = (Range16) {0x4000, 0x7FFF};
    mm.vRam        = (Range16) {0x8000, 0x9FFF};
    mm.exRam       = (Range16) {0xA000, 0xBFFF};
    mm.wRam        = (Range16) {0xC000, 0xDFFF};
    mm.echoRam     = (Range16) {0xE000, 0xFDFF};
    mm.oam         = (Range16) {0xFE00, 0xFE9F};
    mm.forbidden   = (Range16) {0xFEA0, 0XFEFF};
    mm.ioRegisters = (Range16) {0xFF00, 0xFF7F};
    mm.hRam        = (Range16) {0xFF80, 0xFFFE};
    mm.enableIE    = (Range16) {0xFFFF, 0xFFFF};

    return mm;
}

void bus_write8(uint8_t* addressBus, uint16_t location, uint8_t n){
    addressBus[location] = n;
}

void bus_write16(uint8_t* addressBus, uint16_t location, uint16_t n){
    uint8_t nHi = utils_extractByteHi(n); 
    uint8_t nLo = utils_extractByteLo(n);
    
    bus_write8(addressBus, location, nHi);
    bus_write8(addressBus, location+1, nLo);
}

uint8_t bus_read8(uint8_t* addressBus, uint16_t location){
    return addressBus[location];
}

uint16_t bus_read16(uint8_t* addressBus, uint16_t location){
    uint8_t nHi = bus_read8(addressBus, location);
    uint8_t nLo = bus_read8(addressBus, location + 1);

    uint16_t n = utils_mergeBytesLE(nLo, nHi);
    return n;
}