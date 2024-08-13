#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "graphics.h"

#include "SDL2/SDL.h"

int8_t V[16] = { 0 };
int8_t mem[4096] = { 0 };
uint16_t stack[16] = { 0 };
uint8_t screen[2048] = { 0 };
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
				PC = stack[--SP];
			} else {
				//CLS
				memset(screen, 0, 2048);
			}
			break;
		case 0x1:
			//JUMP NNN
			PC = NNN;
			break;
		case 0x2:
			//CALL NNN
			stack[SP++] = PC;
			PC = NNN;
			break;
		case 0x3:
			//SE VX, NN
			if (V[X] == NN)
				PC += 2;
			break;
		case 0x4:
			//SNE VX, NN
			if (V[X] != NN)
				PC += 2;
			break;
		case 0x5:
			//SE VX, VY
			if (V[X] == V[Y])
				PC += 2;
			break;
		case 0x6:
			//LD VX, NN
			V[X] = NN;
			break;
		case 0x7:
			//ADD VX, NN
			V[X] += NN;
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

//return 0 on success
int load_mem(const char *file) {
	printf("Loading file <%s>...\n", file);

	//load fontset
	uint8_t fontset[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
	memcpy(mem + FONTSET_START, fontset, 80);

	//get file size
	FILE *fd = fopen(file, "rb");
	if (!fd) {
		perror("Error opening file");
		return 1;
	}

	fseek(fd, 0, SEEK_END);
	int f_size = ftell(fd);
	rewind(fd);

	if (f_size > MAX_PROGRAM_SIZE) {
		fprintf(stderr, "File is too large.\n");
		return 1;
	}

	//load file
	fread(mem + PROGRAM_START, 1, f_size, fd);
	if (ferror(fd)) {
		perror("Error reading file");
		return 1;
	}

	fclose(fd);
	printf("File <%s> loaded succesfully!\n", file);
	return 0;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		printf("No filename given. Run the command as ./chip8 <file>\n");
		return 1;
	}

	if(load_mem(argv[1]))
		return 1;

	init_window();

	SDL_Event event;
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}

	destroy_window();

	return 0;
}
