#include <nautilus/syscall_table.h>
#include <nautilus/syscall_kernel.h>

#define read(X, Y, Z) ({ syscall_int80(READ, X, Y, Z); })
#define write(X, Y, Z) ({ syscall_int80(WRITE, X, Y, Z); })
#define close(X) ({ syscall_int80(CLOSE, X); })
#define open(X,Y) ({ syscall_int80(OPEN, X, Y); })
#define stat(X, Y) ({ syscall_int80(STAT, X, Y); })
#define fstat(X, Y) ({ syscall_int80(FSTAT, X, Y); })
#define lseek(X, Y, Z) ({ syscall_int80(LSEEK, X, Y, Z); })
#define fork() ({ syscall_int80(FORK); })
#define exit(X) ({ syscall_int80(EXIT, X); })
#define ftruncate(X, Y) ({ syscall_int80(FTRUNCATE, X, Y); })
#define getpid() ({ syscall_int80(GETPID); })
