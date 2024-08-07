#include "global.h"

int8_t V[16] = { 0 };
int8_t mem[4096] = { 0 };
uint16_t stack[16] = { 0 };
uint16_t I = 0, PC = 0, INST = 0, NNN = 0;
uint8_t SP = 0, DT = 0, ST = 0;
int8_t FN = 0, NN = 0, N = 0, X = 0, Y = 0;

void fetch() {
	INST = mem[PC++] << 8;
	INST = INST | mem[PC++];
}

void decode() {
	NNN = INST & 0x0FFF;
	FN = (INST >> 12) & 0x0F;
	NN = INST & 0x0FF;
	N = INST & 0x0F;
	X = (INST >> 8) & 0x0F;
	Y = (INST >> 4) & 0x0F;
}

void execute() {
	switch (FN) {
		case 0x0:
			if (N) {
				//RET
			} else {
				//CLS
			}
			break;
		case 0x1:
			break;
		case 0x2:
			break;
		case 0x3:
			break;
		case 0x4:
			break;
		case 0x5:
			break;
		case 0x6:
			break;
		case 0x7:
			break;
		case 0x8:
			switch (N) {
				case 0x0:
					break;
				case 0x1:
					break;
				case 0x2:
					break;
				case 0x3:
					break;
				case 0x4:
					break;
				case 0x5:
					break;
				case 0x6:
					break;
				case 0x7:
					break;
				case 0xE:
					break;
			}
			break;
		case 0x9:
			break;
		case 0xA:
			break;
		case 0xB:
			break;
		case 0xC:
			break;
		case 0xD:
			break;
		case 0xE:
			break;
		case 0xF:
			break;
	}
}

void step() {
	fetch();
	decode();
	execute();
}

void run() {
	while (1)
		step();
}

int main(int argc, char **argv) {

	return 0;
}
