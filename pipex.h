#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipe
{
	char	*arg[4];
	char	**envp;
	int		in_fd;
	int		out_fd;
	int		fd_pipe[2];
	int		pi;
	int		pid1;
	int		pid2;
}	t_pipe;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include "library/libft/libft.h"


#endif
