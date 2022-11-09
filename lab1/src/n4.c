#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
	if (argc != 2) {
		printf("Invalid args!\n"
				"Enter %s <filename>", argv[0]);
		return -1;
	}

	int fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		perror("open perror");
		return -1;
	}
	
	char str1_buffer[5];
	char str2_buffer[5];

	read(fd, str1_buffer, 5);
	read(fd, str2_buffer, 5);
	lseek(fd, 0, SEEK_SET);
	write(fd, str2_buffer, 5);
	write(fd, str1_buffer, 5);
}
