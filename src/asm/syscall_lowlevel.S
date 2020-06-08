#include <asm/lowlevel.h>
#include <nautilus/syscall_kernel.h>

/*
Entry point for syscall handler
*/

.section .text
.code64

ENTRY(syscall_entry)
    //swapgs
    SAVE_GPRS_SYSCALL()
    movq %rsp, %rdi
    callq nk_syscall_handler
    //movq $10, %rax
    RESTORE_GPRS_EXCEPT_RAX()
    sysret
