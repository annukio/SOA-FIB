#include<asm.h>

ENTRY(write)
	pushl %ebp
	mov %esp, %ebp

	pushl %edx
	pushl %ecx

	movl 8(%ebp), %edx 		# par1(ebx + 8): ebx <- fd
	movl 12(%ebp), %ecx 	# par2(ebx + 12): ecx <- buffer
	movl 16(%ebp), %ebx 	# par3(ebx + 16): edx <- size

	movl $4, %eax			# Identificador = 4
	
	pushl $w_return
	pushl %ebp
	mov %esp,%ebp

	sysenter
    
w_return:
	popl %ebp
	addl $4, %esp
	popl %ecx
	popl %edx
	cmpl $0, %eax
	jge w_end
	# Si tenim error (eax < 0)
	negl %eax 			#eax es num negatiu, el passem a absolut
	movl %eax, errno	#el passem a errno
	movl $-1, %eax		#la funcio retorna -1

w_end:
	popl %ebp
	ret

ENTRY(gettime)
	pushl %ebp
	mov %esp, %ebp

	pushl %edx
	pushl %ecx

	movl $10, %eax			# Identificador = 10

	pushl $gt_return
	pushl %ebp
	mov %esp,%ebp

	sysenter

gt_return:
	popl %ebp
	addl $4, %esp
	popl %ecx
	popl %edx
	cmpl $0, %eax
	jge gt_end
	# Si tenim error (eax < 0)
	negl %eax 			#eax es num negatiu, el passem a absolut
	movl %eax, errno	#el passem a errno
	movl $-1, %eax		#la funcio retorna -1

gt_end:
	popl %ebp
	ret
