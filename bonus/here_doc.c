/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:59:19 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/23 21:58:32 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_getstr(int fd)
{
	char	buf[2];
	char	*str;
	char	*tmp;

	str = (char *)ft_calloc(sizeof(char), 1);
	if (error_catch(!str, NULL, "Malloc failed"))
		return (NULL);
	read(fd, buf, 1);
	buf[1] = 0;
	while (*buf != '\n')
	{
		tmp = ft_strjoin(str, buf);
		free(str);
		if (error_catch(!str, NULL, "Malloc failed"))
			return (NULL);
		str = tmp;
		read(fd, buf, 1);
		buf[1] = 0;
	}
	tmp = ft_strjoin(str, buf);
	free(str);
	if (error_catch(!str, NULL, "Malloc failed"))
		return (NULL);
	str = tmp;
	return (str);
}

static void	ft_pipe_heredoc(t_data *data, int fd_out, int step, char *doc)
{
	int	fd[2];
	int	pid;
	int	status;

	status = 0;
	if (error_catch(pipe(fd) < 0, NULL, strerror(errno)))
		exit (1);
	pid = fork();
	if (error_catch(pid < 0, NULL, strerror(errno)))
		exit (1);
	if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(doc, fd[1]);
		exit (0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (status)
		exit (1);
	ft_pipe(data, fd[0], fd_out, step + 1);
}

static int	ft_free_data_str(t_data *data, char *str)
{
	free(str);
	return (ft_free_data(data));
}

static char	*here_doc_parse(t_data *data, char *limiter)
{
	char	*doc;
	char	*tmp;
	char	*str;

	doc = (char *)ft_calloc(sizeof(char), 1);
	if (error_catch(!doc, NULL, "Malloc failed"))
		exit (ft_free_data(data));
	str = ft_getstr(0);
	if (!str)
		exit (ft_free_data_str(data, str));
	while (ft_strncmp(str, limiter, ft_strlen(limiter))
		|| str[ft_strlen(limiter)] != '\n')
	{
		tmp = ft_strjoin(doc, str);
		free(doc);
		free(str);
		if (error_catch(!tmp, NULL, "Malloc failed"))
			exit (ft_free_data(data));
		doc = tmp;
		str = ft_getstr(0);
		if (!str)
			exit (ft_free_data_str(data, str));
	}
	free(str);
	return (doc);
}

void	here_doc(t_data *data, char *limiter)
{
	char	*doc;
	int		fd_out;

	doc = here_doc_parse(data, limiter);
	fd_out = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (error_catch(fd_out < 0, data->argv[data->argc - 1], strerror(errno)))
		exit (ft_free_data(data));
	ft_pipe_heredoc(data, fd_out, 3, doc);
}
