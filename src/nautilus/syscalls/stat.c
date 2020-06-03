#include <nautilus/nautilus.h>
#include <nautilus/fs.h>

int
sys_stat(char *pathname, struct nk_fs_stat *st)
{
	int ret = nk_fs_stat(pathname,st);
	return ret;
}
