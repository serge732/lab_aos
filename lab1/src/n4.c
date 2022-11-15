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

	int curr_pos = 0;
	int offset = 0;
	
	offset = read(fd, str1_buffer, 5);
	curr_pos += offset;
	printf("Read first. Current position: %d\n", curr_pos);

	offset = read(fd, str2_buffer, 5);
	curr_pos += offset;
	printf("Read second. Current position: %d\n", curr_pos);

	curr_pos = lseek(fd, 0, SEEK_SET);
	printf("Seek set 0. Current position: %d\n", curr_pos);

	offset = write(fd, str2_buffer, 5);
	curr_pos += offset;
	printf("Write second. Current position: %d\n", curr_pos);

	offset = write(fd, str1_buffer, 5);
	curr_pos += offset;
	printf("Write first. Current position: %d\n", curr_pos);
}
