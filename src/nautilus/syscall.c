

#include <nautilus/irq.h>

#include <nautilus/nautilus.h>

#include <nautilus/syscall.h>
#include <nautilus/shell.h>
#include <nautilus/thread.h>

uint64_t syscall_int80(uint64_t num, uint64_t a1, uint64_t a2, uint64_t a3,

                       uint64_t a4, uint64_t a5, uint64_t a6) {

  uint64_t rc;

  __asm__ __volatile__(



      "movq %1, %%rax; "

      "movq %2, %%rdi; "

      "movq %3, %%rsi; "

      "movq %4, %%rdx; "

      "movq %5, %%r10; "

      "movq %6, %%r8; "

      "movq %7, %%r9; "

      "int $0x80; "

      "movq %%rax, %0; "

      : "=m"(rc)

      : "m"(num), "m"(a1), "m"(a2), "m"(a3), "m"(a4), "m"(a5), "m"(a6)

      : "%rax", "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%r9", "%r11");



  return rc;

}


unsigned long getpid(){
  nk_thread_t *thread_id = get_cur_thread();
  unsigned long tid = thread_id->tid;
  return tid;
}

int int80_handler(excp_entry_t *excp, excp_vec_t vector, void *state) {

  struct nk_regs *r = (struct nk_regs *)((char *)excp - 128);
  nk_vc_printf("Inside syscall irq handler\n");
  //if(r->rax==39){
  	nk_vc_printf("Invoked syscall no: %d\n",r->rax);
  	unsigned long tid = getpid();
	// Write to RAX
	uint64_t *test = &tid;
  	nk_vc_printf("Returning new pid %ld\n",*test);
    nk_vc_printf("Returning new pid %ld\n",tid);
	r->rax = tid;
	//return 0;
  //}
  // now you have access to the registers at the system call site:   r->rax,

  // r->rbx, etc.
  return 0;
}


void nk_syscall_init() { register_int_handler(0x80, int80_handler, 0); }



// handle shell command

static int handle_syscall_test(char *buf, void *priv) {
  nk_vc_printf("Shell command for testing syscall invoked\n");
  uint64_t pid = syscall_int80(39, 0, 0, 0, 0, 0, 0); // get PID
  //unsigned long pid;
  nk_vc_printf("%ld\n",pid);
  return 0;

}



static struct shell_cmd_impl syscall_impl = {

    .cmd = "syscall_test",

    .help_str = "syscall_test",

    .handler = handle_syscall_test,

};


nk_register_shell_cmd(syscall_impl);
