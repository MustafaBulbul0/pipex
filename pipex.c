#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char **argv, char **envp)
{
    char *exec_args[4];
    int fd_pipe[2];
    int in_fd;
    int out_fd;
    long pid;
    long pid2;

    if ((argc != 5) || (pipe(fd_pipe) == -1))
        exit (1);
    in_fd = open(argv[1], O_RDONLY | O_CREAT, 0777);
    out_fd = open(argv[4], O_WRONLY | O_CREAT, 0777);
    if (out_fd < 0 || in_fd < 0) 
    exit (1); 
    exec_args[0] = "/bin/sh";
    exec_args[1] = "-c";
    exec_args[2] = argv[2];
    exec_args[3] = NULL;
    
    pid = fork();

    if (pid < 0)
        exit (1);
    else if (pid == 0)
    {
        dup2(in_fd, 0);
        dup2(fd_pipe[1], 1);
        close(fd_pipe[0]);
        close(fd_pipe[1]);
        close(in_fd);
        close(out_fd);

        if (execve(exec_args[0], exec_args, envp) == -1)
            exit (1);
    }

    pid2 = fork();

    if (pid2 < 0)
        exit (0);
    else if (pid2 == 0)
    {
            dup2(fd_pipe[0],0);
            dup2(out_fd, 1);
            close(fd_pipe[0]);
            close(fd_pipe[1]);
            close(in_fd);
            close(out_fd);

            exec_args[2] = argv[3];
        if (execve(exec_args[0], exec_args, envp) == -1)
            exit (1);        
    }
    wait(NULL);
    return (0);
}
