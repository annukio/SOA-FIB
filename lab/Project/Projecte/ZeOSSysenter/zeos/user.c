#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

  char b;

  char *top = sbrk(0x3000);
  

  while(1) { 
  	/* probar getKey
  	int err = getKey(&b);
    if (err >= 0) write(1, &b, sizeof(char));*/
  }
}
