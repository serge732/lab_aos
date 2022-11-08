#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Invalid args!\nEnter %s <filename> <permissions>\n", argv[0]);
    }

    int fd = creat(argv[1], strtoul(argv[2], NULL, 0));
    if (fd == -1) {
        perror("creat perror");
        return -1;
    }

	char content[50];

	printf("Enter some text...\n");
	scanf("%s", content);
	write(fd, content, strlen(content));

	printf("Another one...\n");
	scanf("%s", content);
	write(fd, content, strlen(content));

	close(fd);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("read only open perror");
		return -1;
	}

	char str_buffer[100];

	read(fd, str_buffer, 100);
	printf("File content: %s", str_buffer);

	close(fd);

	fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		perror("read-write open error");
		return -1;
	}
	
	close(fd);

	return 0;
}
