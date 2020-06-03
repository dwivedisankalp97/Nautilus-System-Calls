#include <nautilus/nautilus.h>
#include <nautilus/fs.h>

int
sys_fstat(int fd, struct nk_fs_stat *st)
{
	int ret = nk_fs_fstat((struct nk_fs_open_file_state*)fd,st);
	return ret;
}
