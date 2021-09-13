/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:30:58 by paulguign         #+#    #+#             */
/*   Updated: 2021/09/13 01:28:27 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

char	*ft_getstr(int fd)
{
	char	buf[2];
	char	*str;
	char	*dup;

	str = (char *)malloc(sizeof(char));
	if (!str)
		ft_error("Erreur de malloc.\n");
	str[0] = 0;
	read(fd, buf, 1);
	buf[1] = 0;
	while (*buf)
	{
		dup = ft_strdup(str);
		if (!dup)
			ft_error("Erreur de malloc.\n");
		free(str);
		str = ft_strjoin(dup, buf);
		free(dup);
		read(fd, buf, 1);
		buf[1] = 0;
	}
	return (str);
}

char	*ft_strjoin_slash(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!join)
		ft_error("Erreur de malloc.\n");
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i++] = '/';
	j = 0;
	while (s2 && s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*ft_getcmd(char *arg, char **env)
{
	char	*path;
	char	**multi_path;
	char	*join;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = &(env[i][5]);
	multi_path = ft_split(path, ':');
	i = 0;
	while (multi_path[i])
	{
		join = ft_strjoin_slash(multi_path[i], arg);
		if (open(join, O_RDONLY) > 0)
		{
			ft_free_split(multi_path);
			return (join);
		}
		free(join);
		i++;
	}
	ft_free_split(multi_path);
	return (NULL);
}

int	ft_pipe(int argc, char **argv, char **env, int fd_in, int fd_out, int step)
{
	int		fd[2];
	int		pid;
	char	*cmd;
	char	**split;

	if (step == argc - 2)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		close(fd_in);
		close(fd_out);
		split = ft_split(argv[step], ' ');
		cmd = ft_getcmd(split[0], env);
		if (!cmd)
			ft_error("La commande n'existe pas.\n");
		execve(cmd, split, env);
		return (1);
	}
	else
	{
		if (pipe(fd) < 0)
			ft_error("Erreur de pipe.\n");
		pid = fork();
		if (pid < 0)
			return (0);
		if (pid == 0)
		{
			dup2(fd_in, 0);
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			split = ft_split(argv[step], ' ');
			cmd = ft_getcmd(split[0], env);
			if (!cmd)
				ft_error("La commande n'existe pas.\n");
			execve(cmd, split, env);
			return (1);
		}
		close(fd[1]);
		waitpid(pid, NULL, 0);
		return (ft_pipe(argc, argv, env, fd[0], fd_out, step + 1));
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd_in;
	int	fd_out;

	if (argc >= 5)
	{
		fd_in = open(argv[1], O_RDONLY, 0777);
		if (fd_in < 0)
			ft_error("Erreur de fichier.\n");
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out < 0)
			ft_error("Erreur de fichier.\n");
		if (!ft_pipe(argc, argv, env, fd_in, fd_out, 2))
			ft_error("Erreur de pipe.\n");
	}
	else
		ft_error("Erreur d'argument.\n");
	return (0);
}
