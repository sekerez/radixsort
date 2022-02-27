#include <stdio.h>
#include <stdlib.h>

int main() {
    uint col = 0;
    uint byte = 128 + 1;
    uint row = (1 << 17) + 1024 + 32;

    printf("%08x, %08x\n", row, byte);

    injectByte(&row, byte, col);
    
    printf("%08x\n", row);

    uint some = sizeof(uint);
    printf("%08x\n", some);
    printf("%08x\n", --some);
    printf("%08x\n", --some);
    printf("%08x\n", --some);
    printf("%08x\n", --some);
    printf("%08x\n", --some);
}
        
uint extractByte(uint num, uint col) {
    uint shift = 8 * col;

    uint mask = 0xff << shift;
    uint byte = (num & mask) >> shift;
    return byte;
}

void injectByte(uint* num, uint byte, uint col) {
    uint shift = 8 * col;
    uint mask = 0x000000ff << shift;
    *num = ((*num) & (~mask)) | (byte << shift);
}


// int ReplaceByte(int index, int value, char replaceByte) 
// {
    // return ( value & ~( 0xFF << ( index * 8 ) ) ) | ( replaceByte << ( index * 8 ) );
// }



