#include <inttypes.h>
#include <stdbool.h>

typedef struct{
    // accumulator  // flags register
    uint8_t a;      uint8_t f;
    
    // General purpose combinable 8-bit registers 
    uint8_t b;      uint8_t c;
    uint8_t d;      uint8_t e;
    uint8_t h;      uint8_t l;

    uint8_t ir;     // instruction register
    uint8_t ie;     // interrupt enable

    uint16_t pc;    // program counter
    uint16_t sp;    // stack pointer
    
} RegisterFile;

typedef struct{
    _Bool z;    // Zero flag, enabled if last operation == 0
    _Bool n;    // Subtraction flag, enabled if last instruction was a subtraction
    _Bool h;    // Half carry flag, indicates carry for the lower 4 bits of the result
    _Bool c;    // Carry flag, indicates whether there resulted in an underflow or overflow.
} Flags;

typedef struct{
    RegisterFile registerFile;
    Flags flags;
}Cpu;

/**
 * @brief generates an empty RegisterFile structure
 * @return an empty register file
 */
RegisterFile newRegisterFile();

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
 * @param n8 Pointer we want to load from
 */
void load_r8_n8(uint8_t *r8, uint8_t n8);