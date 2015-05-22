#include "instruction.h"
#define MAXLINE 5
#define MAXOP 5

/******************
 * 		          *
 *   Instruction  *
 *                *
 *	Implementação *
 *                *
 ******************/

Instruction* newInstruction(int LINE, char* OPERATION, char REGISTER, int JUMP1, int JUMP2){
	Instruction* INSTRUCTION = (Instruction*) malloc(sizeof(Instruction));
	INSTRUCTION->LINE        = LINE;
	INSTRUCTION->OPERATION   = OPERATION;
	INSTRUCTION->REGISTER    = REGISTER;
	INSTRUCTION->JUMP1       = JUMP1;
	INSTRUCTION->JUMP2       = JUMP2;
	return INSTRUCTION;
}

void destroyInstruction(Instruction* INSTRUCTION){
    free(INSTRUCTION->OPERATION);
    free(INSTRUCTION);
}

int isValid(char ASCII){
	if((ASCII >= '0' && ASCII <= '9')
	|| (ASCII >= 'A' && ASCII <= 'Z')
	|| (ASCII >= 'a' && ASCII <= 'z'))
		return 1;
	return 0;
}

int nextValid(Buffer* BUFFER, int INDEX){
	if(getBuffer(BUFFER, INDEX) != '\n' && getBuffer(BUFFER, INDEX) != EOF)
		if(!isValid(getBuffer(BUFFER, INDEX)))
			return nextValid(BUFFER, INDEX+1);
		else
			return INDEX;
	return -1;
}

int getSize(int NUMBER){int i=NUMBER?0:1; while(NUMBER>0){NUMBER/=10;i++;}return i;}

int lineFind(Buffer* BUFFER, int LINE){
    int j, i = (-1);
    int SIZE = getSize(LINE);
    char STRING_LINE[SIZE];
    sprintf(STRING_LINE, "%d", LINE);
    while(getBuffer(BUFFER, ++i) != EOF)
        if(getBuffer(BUFFER, i+SIZE) == ':'){
            for(j = 0; j < SIZE; ++j)
                if(STRING_LINE[j] != getBuffer(BUFFER, i+j))
                    break;
            if(j == SIZE)
                return i;
        }
    return (-1);
}

int* getRegisters(char** STRING_REGISTER, int SIZE){
    int i;
    int *REGISTER = (int*) malloc(sizeof(int)*(SIZE));
    REGISTER[0] = SIZE;
    for(i = 1; i < SIZE; ++i)
        REGISTER[i] = atoi(STRING_REGISTER[i-1]);
    return REGISTER;
}

Instruction* getInstruction(Buffer* BUFFER, int LINE){
	int i, INDEX = lineFind(BUFFER, LINE);
	if(INDEX == (-1)) return NULL;

	char STRING_LINE[MAXLINE], *OPERATION, REGISTER, JUMP1[MAXLINE], JUMP2[MAXLINE];
    OPERATION = (char*) malloc(sizeof(char) * MAXOP);

	for(i = 0; isValid(getBuffer(BUFFER, INDEX)); ++i)
        STRING_LINE[i] = getBuffer(BUFFER, INDEX++);
    STRING_LINE[i]='\0';

	INDEX = nextValid(BUFFER, INDEX);
	for(i = 0; isValid(getBuffer(BUFFER, INDEX)); ++i)
        OPERATION[i] = getBuffer(BUFFER, INDEX++);
    OPERATION[i]='\0';

	INDEX = nextValid(BUFFER, INDEX);
	if(isValid(getBuffer(BUFFER, INDEX)))
        REGISTER = getBuffer(BUFFER,INDEX++);

	INDEX = nextValid(BUFFER, INDEX);
	for(i = 0; isValid(getBuffer(BUFFER, INDEX)); ++i)
        JUMP1[i] = getBuffer(BUFFER, INDEX++);
    JUMP1[i]='\0';

	INDEX = nextValid(BUFFER, INDEX);
	if(INDEX != (-1)){
		for(i = 0; isValid(getBuffer(BUFFER, INDEX)); ++i)
            JUMP2[i] = getBuffer(BUFFER, INDEX++);
        JUMP2[i]='\0';
		return newInstruction(atoi(STRING_LINE), OPERATION, REGISTER, atoi(JUMP1), atoi(JUMP2));
	}
	else
		return newInstruction(atoi(STRING_LINE), OPERATION, REGISTER, atoi(JUMP1), NULL);
}

void _uppercase(char* STRING){
    if(STRING[0] != '\0'){
        if(STRING[0] >= 'a' && STRING[0] <= 'z')
            STRING[0] -= 32;
        _uppercase(&STRING[1]);
    }
}

int _operation(char* OPERATION){
    _uppercase(OPERATION);
    if(!strcmp(OPERATION, "ADD"))       return 1;
    else if(!strcmp(OPERATION, "INC"))  return 1;
    else if(!strcmp(OPERATION, "SUB"))  return (-1);
    else if(!strcmp(OPERATION, "DEC"))  return (-1);
    else if(!strcmp(OPERATION, "ZERO")) return 0;
    else if(!strcmp(OPERATION, "BEQZ")) return 0;
    else if(!strcmp(OPERATION, "ZER"))  return 0;
    else if(!strcmp(OPERATION, "BQZ"))  return 0;
    else{
        printf("\nOperacao nao reconhecida: '%s'\n", OPERATION);
        exit(0);
    }
}

int isAlphabetic(char ascii){
    int i = 0;
    if(ascii >= 'a' && ascii <= 'z')
        i = -1;
    else if(ascii >= 'A' && ascii <= 'Z')
        i = 1;
    return i;
}

int _register(char REGISTER, char INIT_TYPE){
    return (int)REGISTER - (int)INIT_TYPE + 1;
}

void executeInstruction(Buffer* BUFFER, int LINE, int* REGISTER){
    Instruction* INSTRUCTION = getInstruction(BUFFER, LINE);
    if(INSTRUCTION == NULL) return NULL;
    int REGISTER_INDEX;
    if(isAlphabetic(INSTRUCTION->REGISTER) == (-1))
        REGISTER_INDEX = _register(INSTRUCTION->REGISTER, 'a');
    else if(isAlphabetic(INSTRUCTION->REGISTER) == 1)
        REGISTER_INDEX = _register(INSTRUCTION->REGISTER, 'A');
    int OPERATION_VALUE = _operation(INSTRUCTION->OPERATION);

    if(REGISTER_INDEX >= REGISTER[0]){
        printf("\n\nTentando acessar registrador inexistente!\n\n");
        exit(-1);
    }
    printFunctionComputed(INSTRUCTION, REGISTER);
    REGISTER[REGISTER_INDEX] += OPERATION_VALUE;

    int NEXT_LINE = INSTRUCTION->JUMP1;
    if(!OPERATION_VALUE)
        if(REGISTER[REGISTER_INDEX])
            NEXT_LINE = INSTRUCTION->JUMP2;

    destroyInstruction(INSTRUCTION);
    executeInstruction(BUFFER, NEXT_LINE, REGISTER);
}

void executeProgram(Buffer* BUFFER, int* REGISTER){
    int i;

    printf("\n(%d",REGISTER[1]);
    for(i = 2; i < REGISTER[0]; ++i) printf(",%d",REGISTER[i]);
    printf("),M)    \tENTRADA DE DADOS");

    executeInstruction(BUFFER, 1, REGISTER);

    printf("\n(%d",REGISTER[1]);
    for(i = 2; i < REGISTER[0]; ++i) printf(",%d",REGISTER[i]);
    printf("),M)    \tSAIDA DE DADOS\n\n");
}

void printFunctionComputed(Instruction* INSTRUCTION, int* REGISTER){
    int i;
    printf("\n(%d",REGISTER[1]);
    for(i = 2; i < REGISTER[0]; ++i) printf(",%d",REGISTER[i]);
    printf("),%d)",INSTRUCTION->LINE);

    int OPERATION = _operation(INSTRUCTION->OPERATION);
    switch(OPERATION){
    case 1: case -1:
        printf("    \tFACA %s(%c) VA_PARA %d", INSTRUCTION->OPERATION, INSTRUCTION->REGISTER, INSTRUCTION->JUMP1);
        break;
    case 0:
        printf("    \tSE %s(%c) ENTAO %d SENAO VA_PARA %d", INSTRUCTION->OPERATION, INSTRUCTION->REGISTER, INSTRUCTION->JUMP1, INSTRUCTION->JUMP2);
        break;
    }
}

void printInstruction(Instruction* INSTRUCTION){
    printf("\n%d: " , INSTRUCTION->LINE);
    printf("%s"     , INSTRUCTION->OPERATION);
    printf("(%c) "  , INSTRUCTION->REGISTER);
    printf("%d "    , INSTRUCTION->JUMP1);
    printf("%d\n"   , INSTRUCTION->JUMP2);
}
