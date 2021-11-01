/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:59:19 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/30 14:47:11 by paulguign        ###   ########.fr       */
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

static int	ft_free_data_str(t_data *data, char *str)
{
	free(str);
	free(data);
	return (1);
}

static char	*here_doc_parse(t_data *data, char *limiter)
{
	char	*doc;
	char	*tmp;
	char	*str;

	doc = (char *)ft_calloc(sizeof(char), 1);
	if (error_catch(!doc, NULL, "Malloc failed"))
		exit (ft_free_data(data, 1));
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
			exit (ft_free_data(data, 1));
		doc = tmp;
		str = ft_getstr(0);
		if (!str)
			exit (ft_free_data_str(data, str));
	}
	free(str);
	return (doc);
}

void	ft_exec_heredoc(t_data *data, char *doc, int *fd)
{
	close(fd[0]);
	ft_putstr_fd(doc, fd[1]);
	close(fd[1]);
	ft_free_data_str(data, doc);
	exit (0);
}

int	here_doc(t_data *data, char *limiter)
{
	char	*doc;
	int		fd[2];
	int		pid;
	int		ret;

	doc = here_doc_parse(data, limiter);
	if (error_catch(pipe(fd) < 0, NULL, strerror(errno)))
		exit (ft_free_data_str(data, doc));
	pid = fork();
	if (error_catch(pid < 0, NULL, strerror(errno)))
		exit (ft_free_data_str(data, doc));
	if (pid == 0)
		ft_exec_heredoc(data, doc, fd);
	free(doc);
	close(fd[1]);
	ret = ft_pipe(data, fd[0], 2);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	return (ret);
}
