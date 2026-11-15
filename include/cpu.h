#include <inttypes.h>
#include <stdbool.h>

typedef union {
    uint16_t value;
    struct {
        uint8_t lo;
        uint8_t hi;
    };
} Register16;

typedef struct {
    // accumulator  // flags register
    Register16 af;
    
    // General purpose combinable 8-bit registers 
    Register16 bc;
    Register16 de;
    Register16 hl;

    uint8_t ir;     // instruction register
    uint8_t ie;     // interrupt enable

    uint16_t pc;    // program counter
    uint16_t sp;    // stack pointer
} RegisterFile;

typedef struct {
    _Bool z;    // Zero flag, enabled if last operation == 0
    _Bool n;    // Subtraction flag, enabled if last instruction was a subtraction
    _Bool h;    // Half carry flag, indicates carry for the lower 4 bits of the result
    _Bool c;    // Carry flag, indicates whether there resulted in an underflow or overflow.
} Flags;

typedef struct {
    RegisterFile registerFile;
    Flags flags;
    uint8_t addressBus[0xFFFF];
} Cpu;

/**
 * @brief Reads the F register and toggles the corresponding flags
 * @param cpu A pointer to the CPU structure
 */
void updateFlags(Cpu* cpu);

/**
 * @brief Generates an empty CPU structure
 * @return guess what
 */
Cpu newCPU();

/**
 * @brief Prints all the register values
 * @param cpu A pointer to the CPU structure
 * @param buffer A buffer where to print the characters to
 */
void dumpRegisters(Cpu *cpu, char buffer[], size_t bufferSize);

/**
 * @brief Sets the desired flag (z, n, h, c)
 * 
 * @param cpu Pointer to the CPU structure
 * @param flag Flag to turn on
 */
void setFlag(Cpu *cpu, char flag);

/**
 * @brief Turns off the desired flag (z, n, h, c)
 * 
 * @param cpu Pointer to the CPU structure
 * @param flag Flag to turn off
 */
void unsetFlag(Cpu *cpu, char flag);

/**
 * @brief Resets all the flags to 0
 * 
 * @param cpu Pointer to the CPU structure
 */
void resetFlags(Cpu *cpu);


// Fetch Decode Execute
uint8_t fetchByte(Cpu *cpu);
uint16_t fetch16(Cpu *cpu);
void advance(Cpu *cpu);


// Actual Assembly operations

/**
 * @brief Copy (aka Load) the value in register on the right into the register on the left.
 * @param r8_1 Pointer to the register we want to load to
 * @param r8_2 Pointer we want to load from
 */
void load_r8_r8(uint8_t *r8_1, uint8_t *r8_2);


/**
 * @brief Copy the value n8 in register r8
 * @param r8 Pointer to the register we want to load to
 * @param n8 Number we want to load
 */
void load_r8_n8(uint8_t *r8, uint8_t n8);

/**
 * @brief Copy the value n16 in register r16
 * 
 * @param r16 Pointer to the 16 bit register we want to load to
 * @param n16 Number to load in the 16 bit register 
 */
void load_r16_n16(Register16* r16, uint16_t n16);

/**
 * @brief Copy the value in register r8 to the address pointed to by HL
 * 
 * @param addressBus Pointer to the address bus 
 * @param hl Pointer to the hl register HL
 * @param r8 Pointer to the 8 bit register we want to load from
 */
void load_ahl_r8(uint8_t* addressBus, Register16* hl, uint8_t* r8);

/**
 * @brief Copy the value n8 into the address pointed to by hl
 * 
 * @param addressBus Pointer to the address bus 
 * @param hl Pointer to the hl register
 * @param n8 Number we want to load
 */
void load_ahl_n8(uint8_t* addressBus, Register16* hl, uint8_t n8);

/**
 * @brief Copy the value in the address pointed to by hl in r8
 * 
 * @param addressBus Pointer to the address bus 
 * @param hl Pointer to the hl register 
 * @param r8 Pointer to the 8 bit register we want to load to
 */
void load_r8_ahl(uint8_t* addressBus, uint8_t* r8, Register16* hl);

/**
 * @brief Copy the value in register A into the byte pointed to by r16.
 * 
 * @param addressBus Pointer to the address bus 
 * @param r16 Pointer to the register we want to load from
 * @param a Pointer to the accumulator register
 */
void load_ar16_a(uint8_t* addressBus, uint16_t* r16, uint8_t* a);


// ---- ARITHMETIC / LOGIC SHTUFF ------

/**
 * @brief Rotate the value in r8 left circularly
 * 
 * @param r8 Pointer to the 8 bit register
 */
void rlc_r8(uint8_t* r8);

/**
 * @brief Rotate the value in r8 right circularly
 * 
 * @param r8 Pointer to the 8 bit register
 */
void rrc_r8(uint8_t* r8);