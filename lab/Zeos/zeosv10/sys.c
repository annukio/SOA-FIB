/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#include <errno.h>

#define LECTURA 0
#define ESCRIPTURA 1

#define BUFF_SIZE 256

extern int zeos_ticks;

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -9; /*EBADF*/
  if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
  return 0;
}

int sys_ni_syscall()
{
	return -38; /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

int sys_fork()
{
  int PID=-1;

  // creates the child process
  
  return PID;
}

void sys_exit()
{  
}

int sys_write(int fd, char * buffer, int size){

  char kernel_buffer[256];

  int error = check_fd(fd, ESCRIPTURA);
  if (error) return error;			// 9    EBADF	Bad file number
  if (buffer == NULL) return -EFAULT; 		// 14 	EFAULT 	Bad address
  if (size < 0) return -EINVAL; 		// 22 	EINVAL 	Invalid argument

  int w_bytes;        //writen bytes
  int bytes_l = size; //bytes left

// Loop per escriure quan (size > BUFF_SIZE)
  while (bytes_l >= BUFF_SIZE) {
      copy_from_user(buffer, kernel_buffer, BUFF_SIZE);
      int written = sys_write_console(kernel_buffer, BUFF_SIZE);  //Escriure en consola
      
      if (written < 0) {
          return written;
      }
      
      w_bytes += written;      // Total bytes escrits
      bytes_l -= written;      // Decrementem bytes que queden
      buffer += written;       // Movem el pointer
  }

  // Loop per els bytes restants (size < BUFF_SIZE)
  if (bytes_l > 0) {
      copy_from_user(buffer, kernel_buffer, bytes_l);
      int written = sys_write_console(kernel_buffer, bytes_l);

      if (written < 0) {
          return written;
      }

      w_bytes += written;      // Suma els bytes escrits
      bytes_l -= written;      // Hauria de ser 0
  }

  // Retorna els bytes escrits
  return w_bytes;
}

int sys_gettime(){
  return zeos_ticks;
}
