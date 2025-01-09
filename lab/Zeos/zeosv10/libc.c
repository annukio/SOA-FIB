/*
 * libc.c 
 */

#include <libc.h>
#include <errno.h>
#include <types.h>

int errno;

void itoa(int a, char *b)
{
  int i, i1;
  char c;
  
  if (a==0) { b[0]='0'; b[1]=0; return ;}
  
  i=0;
  while (a>0)
  {
    b[i]=(a%10)+'0';
    a=a/10;
    i++;
  }
  
  for (i1=0; i1<i/2; i1++)
  {
    c=b[i1];
    b[i1]=b[i-i1-1];
    b[i-i1-1]=c;
  }
  b[i]=0;
}

//he copiat itoa canviant alguns parametres per a que passi a base 16
/*void itoa16(int a, char *b){
  int i;

  if(strlen(b) < 7) {
  	errno = -EINVAL; 
  	perror(); 
  	return;
  }

  b[0]= '0';
  b[1]= 'x';
  
  if (a==0) { b[2]=0; b[3]='0'; b[4]=0; b[5]=0; b[6]=0; return ;}
  
  i=2;
  while (a>0)
  {
    char temp;
    temp = (a%16);
    a=a/16;
    // si nombre 0 a 9 ok sino ABCDEF
    if(temp >= 10) b[i]=temp+'0';
    else b[i]= temp - 10 +'A';

    i++;
   }
 }*/

int strlen(char *a)
{
  int i;
  
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}

void strcpy(char *src, char *dest){

	while(*src != '\0'){
		*dest = *src;
		dest++;
		src++;
	}
}

void perror(){
	char buffer[256];
	switch(errno){
		case 0:
			break;
		case EBADF:
			strcpy("Bad file number\n", buffer);
			break;
		case EACCES:
			strcpy("Permission denied\n", buffer);
			break;
		case EFAULT:
			strcpy("Bad address\n", buffer);
			break;
		case EINVAL:
			strcpy("Invalid argument\n", buffer);
			break;
		default:
			strcpy("Error indef\n", buffer);
			break;
	}
	write(1, buffer, strlen(buffer));
}

