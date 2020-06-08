#include <nautilus/syscall_table.h>

// uint64_t a1, uint64_t a2, uint64_t a3,
//
//                        uint64_t a4, uint64_t a5, uint64_t a6
uint64_t syscall_int80(uint64_t num, ...) {

  uint64_t rc;

  va_list args;
  va_start(args, num);
  uint64_t l[6];
  int i = 0;
  while (i < 6) {
    l[i] = va_arg(args, uint64_t);
    i++;
  }

  uint64_t a1 = l[0];
  uint64_t a2 = l[1];
  uint64_t a3 = l[2];
  uint64_t a4 = l[3];
  uint64_t a5 = l[4];
  uint64_t a6 = l[5];

  va_end(args);

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

void syscall_entry(struct nk_regs *r);

uint64_t syscall_syscall(uint64_t num, uint64_t a1, uint64_t a2, uint64_t a3,
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
      "syscall; "
      "movq %%rax, %0; "
      : "=m"(rc)
      : "m"(num), "m"(a1), "m"(a2), "m"(a3), "m"(a4), "m"(a5), "m"(a6)
      : "%rax", "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%r9", "%r11");

  return rc;
}

#define SAVE_GPRS_SYSCALL()                                                    \
  movq % rax, -8(% rsp);                                                       \
  movq % rbx, -16(% rsp);                                                      \
  movq % rcx, -24(% rsp);                                                      \
  movq % rdx, -32(% rsp);                                                      \
  movq % rsi, -40(% rsp);                                                      \
  movq % rdi, -48(% rsp);                                                      \
  movq % rbp, -56(% rsp);                                                      \
  movq % r8, -64(% rsp);                                                       \
  movq % r9, -72(% rsp);                                                       \
  movq % r10, -80(% rsp);                                                      \
  movq % r11, -88(% rsp);                                                      \
  movq % r12, -96(% rsp);                                                      \
  movq % r13, -104(% rsp);                                                     \
  movq % r14, -112(% rsp);                                                     \
  movq % r15, -120(% rsp);                                                     \
  subq $120, % rsp;

#define RESTORE_GPRS_EXCEPT_RAX()                                              \
  movq(% rsp), % r15;                                                          \
  movq 8(% rsp), % r14;                                                        \
  movq 16(% rsp), % r13;                                                       \
  movq 24(% rsp), % r12;                                                       \
  movq 32(% rsp), % r11;                                                       \
  movq 40(% rsp), % r10;                                                       \
  movq 48(% rsp), % r9;                                                        \
  movq 56(% rsp), % r8;                                                        \
  movq 64(% rsp), % rbp;                                                       \
  movq 72(% rsp), % rdi;                                                       \
  movq 80(% rsp), % rsi;                                                       \
  movq 88(% rsp), % rdx;                                                       \
  movq 96(% rsp), % rcx;                                                       \
  movq 104(% rsp), % rbx;                                                      \
  addq $120, % rsp;
// 120 since last 8 is for RAX which we do not restore

#define read(X, Y, Z) ({ syscall_int80(READ, X, Y, Z); })
#define write(X, Y, Z) ({ syscall_int80(WRITE, X, Y, Z); })
#define close(X) ({ syscall_int80(CLOSE, X); })
#define stat(X, Y) ({ syscall_int80(STAT, X, Y); })
#define fstat(X, Y) ({ syscall_int80(FSTAT, X, Y); })
#define lseek(X, Y, Z) ({ syscall_int80(LSEEK, X, Y, Z); })
#define fork() ({ syscall_int80(FORK); })
#define exit(X) ({ syscall_int80(EXIT, X); })
#define ftruncate(X, Y) ({ syscall_int80(FTRUNCATE, X, Y); })
#define getpid() ({ syscall_int80(GETPID); })
