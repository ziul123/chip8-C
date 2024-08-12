#pragma once
#include <stdint.h>

//Registers

extern int8_t V[16];

extern uint16_t I, PC;

extern uint8_t SP, DT, ST;

//Memory

extern int8_t mem[4096];

#define FONTSET_START 0x50

#define PROGRAM_START 0x200

#define MAX_PROGRAM_SIZE 3232	//0xE9F - 0x200 + 1

extern uint16_t stack[16];

//Instruction Sections

extern uint16_t INST, NNN;

extern int8_t FN, NN, N, X, Y;
