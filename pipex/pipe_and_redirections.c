#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

//example using dup : --> The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor.
/*
int main()
{
    char buff[20];
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int copy = dup(fd);
    printf("%d %d \n",fd,copy);  //--> fd is 3   and   copy is 4;
    write(fd, "Hello\n", 6);
    read(copy, buff, 6); // Both go into test.txt (the file desc 3 and 4 both point to the same file) !!AND THEY SHARE THE SAME file OFFSET!!

    close(fd);
    close(copy);
    return 0;
}
*/




// example using dup2 :The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor,  it uses the file descriptor number specified in newfd.
                        //If the file descriptor newfd was previously open, it is silently closed before being reused.

int main()
{
    int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    dup2(fd, STDOUT_FILENO);  // Redirect stdout to file

    printf("%d %d\n",fd, STDOUT_FILENO);
    printf("This will go to the file!\n");

    close(fd);
    return 0;
}


// In PIPEX You use dup2() like this:

// dup2(pipefd[1], STDOUT_FILENO); // child: send output into pipe
// dup2(pipefd[0], STDIN_FILENO);  // parent: read from pipe
