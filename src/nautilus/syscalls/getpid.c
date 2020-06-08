#include <nautilus/nautilus.h>
#include <nautilus/thread.h>

int sys_getpid(int a, ...){
  nk_thread_t *thread_id = get_cur_thread();
  unsigned long tid = thread_id->tid;
  return (int)tid;
}
