#include "pipex.h"

static void	clear_2d_pointer(char **map);

void	shut_pro_err(t_pipe *ft_pipex)
{
	if (ft_pipex)
	{
		clear_2d_pointer(ft_pipex->arg);
		clear_2d_pointer(ft_pipex->envp);
		free(ft_pipex);
	}
	exit (2);
}

static void	clear_2d_pointer(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}
