#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Invalid args!\n"
				"Enter %s <filename>", argv[0]);
		return -1;
	}

	struct stat s;
	stat(argv[1], &s);

	printf("mode: %d\n", s.st_mode);
	printf("ino: %llu\n", s.st_ino);
	printf("dev: %d\n", s.st_dev);
	printf("nlink: %d\n", s.st_nlink);
	printf("uid: %d\n", s.st_uid);
	printf("gid: %d\n", s.st_gid);
	printf("size: %lld\n", s.st_size);

	return 0;
}
