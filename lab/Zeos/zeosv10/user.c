#include <libc.h>
#include <suma.h>

char buff[24];

int pid;

int add(int par1,int par2){
	return par1 + par2;
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */
    

// PAGEFFAULT TESTING ---------------- només descomentar per a probar
  char* p = 0;
  *p = 'x';

// WRITE TESTING ---------------------
  /*char *c = "Testing write syscall\n";
  int error = write(1, c, strlen(c));
  if (error < 0) perror();

// GETTIME TESTING ------------------ Ha de donar 1, o incrementar si el posem al loop
  int a;
  c = "\nGettime:";
  write(1, c, strlen(c));
  a = gettime();
  // c ha de ser un punter sino peta
  itoa(a, c);
  error = write(1, c, strlen(c));
  if (error < 0) perror();*/
  
  
 //PERROR TESTING ----------------------
  /*char *c = "\nPerror Testing:\n";
  write(1, c, strlen(c));
   
  int error = write(3, c, strlen(c));
  if (error < 0) perror();
  itoa(errno, c);
  write(1, c, strlen(c));*/
  
  
  while(1) {}
}


