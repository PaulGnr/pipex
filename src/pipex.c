/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:54:07 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/23 22:42:03 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strjoin_slash(char *s1, char *s2)
{
	char	*join;
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	if (error_catch(!tmp, NULL, "Malloc failed"))
		return (NULL);
	join = ft_strjoin(tmp, s2);
	if (error_catch(!join, NULL, "Malloc failed"))
		return (NULL);
	free(tmp);
	return (join);
}

static char	*ft_getcmd(char *arg, char **env)
{
	char	*path;
	char	**multi_path;
	char	*join;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path = &(env[i][5]);
	multi_path = ft_split(path, ':');
	i = 0;
	while (multi_path[i])
	{
		join = ft_strjoin_slash(multi_path[i++], arg);
		if (open(join, O_RDONLY) > 0)
		{
			ft_free_split(multi_path);
			return (join);
		}
		free(join);
	}
	ft_free_split(multi_path);
	return (NULL);
}

static void	ft_pipe_exec(t_data *data, int fd_in, int fd_out, int step)
{
	char	*cmd;
	char	**split;

	if (error_catch(dup2(data->fd_in, 0) < 0, NULL, strerror(errno)))
		exit (ft_free_data(data));
	if (error_catch(dup2(fd_out, 1) < 0, NULL, strerror(errno)))
		exit (ft_free_data(data));
	close(fd_in);
	close(fd_out);
	split = ft_split(data->argv[step], ' ');
	cmd = ft_getcmd(split[0], data->env);
	if (error_catch(!cmd, split[0], "Command not found"))
	{
		free(cmd);
		ft_free_split(split);
		exit (!ft_free_data(data));
	}
	execve(cmd, split, data->env);
	free(cmd);
	ft_free_split(split);
	exit (!ft_free_data(data));
}

void	ft_pipe(t_data *data, int fd_in, int fd_out, int step)
{
	int	fd[2];
	int	pid;
	int	status;

	status = 0;
	data->fd_in = fd_in;
	if (step == data->argc - 2)
		ft_pipe_exec(data, fd_in, fd_out, step);
	else
	{
		if (error_catch(pipe(fd) < 0, NULL, strerror(errno)))
			exit (ft_free_data(data));
		pid = fork();
		if (error_catch(pid < 0, NULL, strerror(errno)))
			exit (ft_free_data(data));
		if (pid == 0)
			ft_pipe_exec(data, fd[0], fd[1], step);
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (status)
			exit (1);
		ft_pipe(data, fd[0], fd_out, step + 1);
	}
}
