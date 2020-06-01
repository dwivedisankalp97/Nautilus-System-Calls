#include <nautilus/nautilus.h>
#include <nautilus/fs.h>

int
sys_open(char *filename,
	 int     flags,
	 int  mode)
{
	struct nk_fs_open_file_state *file;
	file = nk_fs_open(filename,flags,(int)mode);
}
