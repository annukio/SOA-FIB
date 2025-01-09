#include <buffer.h>

void initBc(struct bufferCircular *bc){
	bc->g_index = 0;
	bc->i_index = 0;
}


int state(struct bufferCircular *bc){
	if (bc->i_index == MAX_BUFFER_SIZE) return 1;
	else if (bc->i_index == bc->g_index) return -1;
	return 0;
}

int insert(struct bufferCircular *bc, char b){

	if (state(bc) == FULL){
		return -1; // buffer ple
	}
	else {
		bc->buffer[bc->i_index] = b;
		bc->i_index++;
		return 0;
	}

}

int get(struct bufferCircular *bc, char *b){
	if (state(bc) == EMPTY) return -1;
	else {
		*b = bc->buffer[bc->g_index];
		bc->g_index++;
		return 0;
	}
}


