#pragma once
#include <stdint.h>

//Registers

extern int8_t V[16];

extern uint16_t I, PC;

extern uint8_t SP, DT, ST;

//Memory

extern int8_t mem[4096];

#define PROGRAM_START 0x200

extern uint16_t stack[16];

//Instruction Sections

extern uint16_t INST, NNN;

extern int8_t FN, NN, N, X, Y;
