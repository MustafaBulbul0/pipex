#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

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

void	shut_pro_err(t_pipe *ft_pipex);

#endif
