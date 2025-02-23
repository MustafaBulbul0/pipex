#include "pipex.h"

static t_pipe	*init_struct(t_pipe *ft_pipex, char **argv);
static void		first_command(t_pipe *pipex);
static void		second_command(t_pipe *ft_pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*ft_pipex;

	if (argc != 5)
		exit(2);
	ft_pipex = (t_pipe *)malloc(sizeof(t_pipe));
	if (!ft_pipex)
		exit(STDERR_FILENO);
	ft_pipex = init_struct(ft_pipex, argv);
	ft_pipex->envp = envp;
	ft_pipex->pid1 = fork();
	if (ft_pipex->pid1 < 0)
		shut_pro_err(ft_pipex);
	else if (ft_pipex->pid1 == 0)
		first_command(ft_pipex);
	ft_pipex->pid2 = fork();
	ft_pipex->arg[2] = argv[3];
	if (ft_pipex->pid2 < 0)
		shut_pro_err(ft_pipex);
	else if (ft_pipex->pid2 == 0)
		second_command(ft_pipex);
	wait(NULL);
	free(ft_pipex);
	return (0);
}

static t_pipe	*init_struct(t_pipe *ft_pipex, char **argv)
{
	ft_pipex->in_fd = open (argv[1], O_RDONLY | O_CREAT, 0777);
	ft_pipex->out_fd = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ft_pipex->in_fd < 0 || ft_pipex->out_fd < 0)
		shut_pro_err(ft_pipex);
	ft_pipex->pi = pipe(ft_pipex->fd_pipe);
	if (ft_pipex->pi == -1)
		shut_pro_err(ft_pipex);
	ft_pipex->arg[0] = "/bin/sh";
	ft_pipex->arg[1] = "-c";
	ft_pipex->arg[2] = argv[2];
	ft_pipex->arg[3] = NULL;
	return (ft_pipex);
}

static void	first_command(t_pipe *ft_pipex)
{
	dup2(ft_pipex->in_fd, 0);
	dup2(ft_pipex->fd_pipe[1], 1);
	close(ft_pipex->fd_pipe[0]);
	close(ft_pipex->fd_pipe[1]);
	close(ft_pipex->in_fd);
	close(ft_pipex->out_fd);
	ft_pipex->pi = execve(ft_pipex->arg[0], ft_pipex->arg, ft_pipex->envp);
	if (ft_pipex->pi == -1)
		exit (2);
}

static void	second_command(t_pipe *ft_pipex)
{
	dup2(ft_pipex->fd_pipe[0], 0);
	dup2(ft_pipex->out_fd, 1);
	close(ft_pipex->fd_pipe[0]);
	close(ft_pipex->fd_pipe[1]);
	close(ft_pipex->in_fd);
	close(ft_pipex->out_fd);
	ft_pipex->pi = execve(ft_pipex->arg[0], ft_pipex->arg, ft_pipex->envp);
	if (ft_pipex->pi == -1)
		exit (2);
}
