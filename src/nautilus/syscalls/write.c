// Commented code is from kitten system call for reference
#include<nautilus/nautilus.h>
#include <nautilus/naut_types.h>
#include <nautilus/fs.h>

ssize_t
sys_write(int     fd,
	  void* buf,
	  size_t  len)
{
	unsigned long flags;
	//int orig_fd = fd;
	ssize_t ret = nk_fs_write((struct nk_fs_open_file_state*)fd,buf,len);
  // open file from descriptor. I have assumed the fd to be a pointer to nk_fs_open_file_state
  // This write assumes a fs is mounted.
	//struct file * const file = get_current_file(fd);
	return ret;
}
