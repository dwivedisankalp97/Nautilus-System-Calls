#include <asm/lowlevel.h>
#include <nautilus/syscall.h>

/*
Entry point for syscall handler
*/

.section .text
.code64

ENTRY(syscall_entry)
    SAVE_GPRS_SYSCALL()
    movq %rsp, %rdi
    call syscall_entry
    RESTORE_GPRS_EXCEPT_RAX()
    sysret