// Commented code is from kitten system call for reference
#include<nautilus/nautilus.h>
#include <nautilus/naut_types.h>
#include <nautilus/fs.h>

ssize_t
sys_read(int     fd,
	  int buf,
	  int  len, int d, int e, int f)
{
	//int orig_fd = fd;
	int ret = (int)nk_fs_read((struct nk_fs_open_file_state*)fd,(void*)buf,(ssize_t)len);
  // open file from descriptor. I have assumed the fd to be a pointer to nk_fs_open_file_state
  // This write assumes a fs is mounted.
	//struct file * const file = get_current_file(fd);
	return ret;
}
