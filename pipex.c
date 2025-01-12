#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv, char **envp)
{
    char *exec_args[4];
    int fd_pipe[2];
    int in_fd;
    int out_fd;
    long pid;
 
    if ((argc != 5) || (pipe(fd_pipe) == -1))
        exit (1);
    in_fd = open(argv[1], O_RDWR | O_CREAT, 0777);
    out_fd = open(argv[4], O_WRONLY | O_CREAT, 0777);
    if (out_fd < 0) 
    {
    perror("Error opening output file");
    exit(EXIT_FAILURE); 
    }
    exec_args[0] = "/bin/sh";
    exec_args[1] = "-c";
    exec_args[2] = argv[2];
    exec_args[3] = NULL;
    
    dup2(in_fd, 0);
    dup2(fd_pipe[1], 1);
    pid = fork();

    if (pid < 0)
        exit (1);
    else if (pid == 0)
    {
        if (execve(exec_args[0], exec_args, envp) == -1)
            exit (1);
            dup2(fd_pipe[0],in_fd);
            dup2(out_fd, fd_pipe[1]);
            exec_args[2] = argv[3];
        if (execve(exec_args[0], exec_args, envp) == -1)
            exit (1);
    }
    return (0);
}
