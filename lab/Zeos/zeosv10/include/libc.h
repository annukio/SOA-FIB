/*
 * libc.h - macros per fer els traps amb diferents arguments
 *          definició de les crides a sistema
 */
 
#ifndef __LIBC_H__
#define __LIBC_H__

#include <stats.h>

extern int errno;

int write(int fd, char *buffer, int size);

void itoa(int a, char *b);
void itoa16(int a, char *b);

int strlen(char *a);

int getpid();

int fork();

void exit();

void perror();

void strcpy(char *src, char *dest);

#endif  /* __LIBC_H__ */
