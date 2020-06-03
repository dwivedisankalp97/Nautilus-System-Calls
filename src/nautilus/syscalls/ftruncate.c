#include <nautilus/nautilus.h>
#include <nautilus/fs.h>

int
sys_ftruncate(int fd, int len)
{
  int ret;
	ret = nk_fs_ftruncate((struct nk_fs_open_file_state*)fd, (off_t)len);
	return ret;
}
