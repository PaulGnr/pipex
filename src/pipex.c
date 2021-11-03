/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:54:07 by paulguign         #+#    #+#             */
/*   Updated: 2021/11/03 15:29:00 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	error_cmd(char *arg, char **env)
{
	int		i;

	if (!arg)
	{
		arg = (char *)malloc(sizeof(char));
		if (error_catch(!arg, NULL, "Malloc failed"))
			exit (1);
		*arg = 0;
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		error_catch(1, arg, "No such file or directory");
	else
		error_catch(1, arg, "command not found");
	if (!arg[0])
		free(arg);
}

static void	ft_pipe_exec(t_data *data, int *fd, int step)
{
	char	*pathname;
	char	**argv;

	if (error_catch(dup2(fd[0], STDIN_FILENO) < 0, NULL, strerror(errno)))
		exit (1);
	if (error_catch(dup2(fd[1], STDOUT_FILENO) < 0, NULL, strerror(errno)))
		exit (1);
	close(fd[0]);
	close(fd[1]);
	argv = ft_split(data->argv[step + 1], ' ');
	pathname = ft_getcmd(argv[0], data->env);
	if (!pathname)
	{
		error_cmd(argv[0], data->env);
		ft_free_split(argv);
		exit (1);
	}
	execve(pathname, argv, data->env);
	free(pathname);
	ft_free_split(argv);
	exit (1);
}

void	ft_redirection(t_data *data, int *fd, int fd_in, int step)
{
	fd[0] = ft_get_infile(data, fd, fd_in, step);
	fd[1] = ft_get_outfile(data, fd, step);
	ft_pipe_exec(data, fd, step);
}

int	ft_pipe(t_data *data, int fd_in, int step)
{
	int	fd[2];
	int	pid;
	int	status;
	int	ret;

	status = 0;
	if (error_catch(pipe(fd) < 0, NULL, strerror(errno)))
		exit (1);
	pid = fork();
	if (error_catch(pid < 0, NULL, strerror(errno)))
		exit (1);
	if (pid == 0)
		ft_redirection(data, fd, fd_in, step);
	if (fd_in >= 0)
		close(fd_in);
	close(fd[1]);
	if (step < data->argc - 3)
		ret = ft_pipe(data, fd[0], step + 1);
	waitpid(pid, &status, 0);
	if (step == data->argc - 3)
		ret = WEXITSTATUS(status);
	return (ret);
}
