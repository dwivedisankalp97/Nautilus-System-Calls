

//#ifndef _SYSCALL

//#define _SYSCALL

#include <nautilus/syscall_table.h>
#include <nautilus/syscall_decl.h>

int nk_legacy_syscall_handler(excp_entry_t *excp,

                              excp_vec_t vector,

                              void *state);
void nk_syscall_init();

void init_syscall_table();











//#endif // _SYSCALL
