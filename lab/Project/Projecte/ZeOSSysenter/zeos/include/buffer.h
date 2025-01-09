	/*
 * buffer.h
 */

#ifndef __BUFFER_H__
#define __BUFFER_H__

#define MAX_BUFFER_SIZE 64
#define EMPTY -1
#define WRITEABLE 0
#define FULL 1


struct bufferCircular {
	char buffer[MAX_BUFFER_SIZE];
	int i_index; //index per a insertar
	int g_index; //index per a obtenir
};

void initBc(struct bufferCircular *bc);

/*Retorna 1 si esta ple, 0 si hi ha espai, -1 si esta buit*/
int state(struct bufferCircular *bc);

int insert(struct bufferCircular *bc, char b);

int get(struct bufferCircular *bc, char *b);


#endif  /* __BUFFER_H__ */
