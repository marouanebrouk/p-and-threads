#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *buff = malloc(50);
    close(0);
    int fd = open("test.txt",O_RDWR);
    read(fd,buff,11);
    int fd2 = open("test.txt",O_RDWR);
    write(0,"hassan",6);
    printf("%d\n",fd);
    printf("%d\n",fd2);
    printf("%s\n",buff);
}