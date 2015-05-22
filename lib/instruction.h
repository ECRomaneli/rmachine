#include "libs.h"

/******************
 * 		          *
 *	Instruction   *
 *                *
 ******************/

Instruction* newInstruction(int,char*,char,int,int);

void destroyInstruction(Instruction*);

int isValid(char);

int nextValid(Buffer*,int);

int getSize(int);

int lineFind(Buffer*,int);

int* getRegisters(char**,int);

int _operation(char*);

int _register(char,char);

void executeInstruction(Buffer*,int,int*);

void executeProgram(Buffer*,int*);

void printFunctionComputed(Instruction*,int*);

void printInstruction(Instruction*);
