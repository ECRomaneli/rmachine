#include "../lib/libs.h"

int main(int size, char** parameter){
    Buffer* b = newBuffer(parameter[1], 10);
    if(size < 3){
        printf("\nInicialize os registradores!\n\n");
        return 0;
    }
    int* reg = getRegisters(&parameter[2],size-1);
    executeProgram(b, reg);
    return 0;
}
