/*
 * interrupt.c -
 */
#include <types.h>
#include <interrupt.h>
#include <segment.h>
#include <hardware.h>
#include <io.h>
#include <mm.h>
#include <zeos_interrupt.h>

Gate idt[IDT_ENTRIES];
Register    idtR;

void clk_handler();
void kbd_handler();
void pf_handler();
void syscall_handler_sysenter();
int writeMSR(int msr, unsigned long value);

int zeos_ticks;

int strlen(char *a)
{
  int i;
  
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}

void itoa16(int a, char *b){
  int i = 7; //comencem des d'el final
  int residu;

  b[0]= '0';
  b[1]= 'x';
  
  if (a==0) { b[2]='0'; b[3]='0'; b[4]='0'; b[5]='0'; b[6]='0'; b[7] = '\0'; return ;}
  
  while (i > 1) {
      residu = a % 16;
      a = a / 16;

      if (residu < 10) {
          b[i] = residu + '0';  // 0-9 digits
      } else {
          b[i] = residu - 10 + 'A';  // A-F digits
      }

      i--;
  }
}
 
 void strcpy(char *src, char *dest){

	while(*src != '\0'){
		*dest = *src;
		dest++;
		src++;
	}
}

char char_map[] =
{
  '\0','\0','1','2','3','4','5','6',
  '7','8','9','0','\'','�','\0','\0',
  'q','w','e','r','t','y','u','i',
  'o','p','`','+','\0','\0','a','s',
  'd','f','g','h','j','k','l','�',
  '\0','�','\0','�','z','x','c','v',
  'b','n','m',',','.','-','\0','*',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0','\0','\0','\0','\0','\0','7',
  '8','9','-','4','5','6','+','1',
  '2','3','0','\0','\0','\0','<','\0',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0'
};

void setInterruptHandler(int vector, void (*handler)(), int maxAccessibleFromPL)
{
  /***********************************************************************/
  /* THE INTERRUPTION GATE FLAGS:                          R1: pg. 5-11  */
  /* ***************************                                         */
  /* flags = x xx 0x110 000 ?????                                        */
  /*         |  |  |                                                     */
  /*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
  /*         |   \ DPL = Num. higher PL from which it is accessible      */
  /*          \ P = Segment Present bit                                  */
  /***********************************************************************/
  Word flags = (Word)(maxAccessibleFromPL << 13);
  flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

  idt[vector].lowOffset       = lowWord((DWord)handler);
  idt[vector].segmentSelector = __KERNEL_CS;
  idt[vector].flags           = flags;
  idt[vector].highOffset      = highWord((DWord)handler);
}

void setTrapHandler(int vector, void (*handler)(), int maxAccessibleFromPL)
{
  /***********************************************************************/
  /* THE TRAP GATE FLAGS:                                  R1: pg. 5-11  */
  /* ********************                                                */
  /* flags = x xx 0x111 000 ?????                                        */
  /*         |  |  |                                                     */
  /*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
  /*         |   \ DPL = Num. higher PL from which it is accessible      */
  /*          \ P = Segment Present bit                                  */
  /***********************************************************************/
  Word flags = (Word)(maxAccessibleFromPL << 13);

  //flags |= 0x8F00;    /* P = 1, D = 1, Type = 1111 (Trap Gate) */
  /* Changed to 0x8e00 to convert it to an 'interrupt gate' and so
     the system calls will be thread-safe. */
  flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

  idt[vector].lowOffset       = lowWord((DWord)handler);
  idt[vector].segmentSelector = __KERNEL_CS;
  idt[vector].flags           = flags;
  idt[vector].highOffset      = highWord((DWord)handler);
}


void setIdt()
{
  /* Program interrups/exception service routines */
  idtR.base  = (DWord)idt;
  idtR.limit = IDT_ENTRIES * sizeof(Gate) - 1;
  
  set_handlers();

  /* ADD INITIALIZATION CODE FOR INTERRUPT VECTOR */
  
  setInterruptHandler(32, clk_handler, 0);
  setInterruptHandler(33, kbd_handler, 0);
  setInterruptHandler(14, pf_handler, 0);

  //programem msr
  writeMSR(0x174, __KERNEL_CS);
  writeMSR(0x175, INITIAL_ESP);
  writeMSR(0x176, (unsigned long)syscall_handler_sysenter);

  set_idt_reg(&idtR);
}

void kbd_routine(){
	unsigned char val = inb(0x60);
	unsigned char mb = 0x80 & val;
	unsigned char ch = 0x7F & val;
	if (mb == 0){ // make
		printc_xy(0,0,char_map[ch]); //?
	}
	
}
void clk_routine(){
	++zeos_ticks;
	zeos_show_clock();
}

void pf_routine(){
	int bad_adress;
	char num_buff[9];
	asm("movl %%eax, %0" : "=r"(bad_adress));
	itoa16(bad_adress, num_buff);
	
	char buffer[256];
	strcpy("Process generates a PAGE FAULT exception at EIP: ", buffer);

  printk (buffer);
  printk(num_buff);
  printk("\n");

	while(1);
	
}

