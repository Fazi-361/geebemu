#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "utils.h"


int main(){

    char buffer[200];
    Cpu cpu = newCPU();
    
    cpu.registerFile.f = 0b01110000;
    updateFlags(&cpu);

    // printf("Z: %d\nN: %d\nH: %d\nC: %d\n", 
    //     cpu.flags.z, cpu.flags.n, cpu.flags.h, cpu.flags.c);


    dumpRegisters(&cpu, buffer, 200);
    printf("%s\n----------\n", buffer);

    dumpRegisters(&cpu, buffer, 200);
    printf("%s\n", buffer);
    
    return 0;   
}