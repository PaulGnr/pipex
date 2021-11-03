/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:59:19 by paulguign         #+#    #+#             */
/*   Updated: 2021/11/03 15:19:02 by pguignie         ###   ########.fr       */
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

static int	ft_free_str(char *str)
{
	free(str);
	return (1);
}

static char	*here_doc_parse(char *limiter)
{
	char	*doc;
	char	*tmp;
	char	*str;

	doc = (char *)ft_calloc(sizeof(char), 1);
	if (error_catch(!doc, NULL, "Malloc failed"))
		exit (1);
	str = ft_getstr(0);
	if (!str)
		exit (ft_free_str(str));
	while (ft_strncmp(str, limiter, ft_strlen(limiter))
		|| str[ft_strlen(limiter)] != '\n')
	{
		tmp = ft_strjoin(doc, str);
		free(doc);
		free(str);
		if (error_catch(!tmp, NULL, "Malloc failed"))
			exit (1);
		doc = tmp;
		str = ft_getstr(0);
		if (!str)
			exit (ft_free_str(str));
	}
	free(str);
	return (doc);
}

void	ft_exec_heredoc(char *doc, int *fd)
{
	close(fd[0]);
	ft_putstr_fd(doc, fd[1]);
	close(fd[1]);
	free(doc);
	exit (0);
}

int	here_doc(t_data *data, char *limiter)
{
	char	*doc;
	int		fd[2];
	int		pid;
	int		ret;

	data->here_doc = 1;
	doc = here_doc_parse(limiter);
	if (error_catch(pipe(fd) < 0, NULL, strerror(errno)))
		exit (ft_free_str(doc));
	pid = fork();
	if (error_catch(pid < 0, NULL, strerror(errno)))
		exit (ft_free_str(doc));
	if (pid == 0)
		ft_exec_heredoc(doc, fd);
	free(doc);
	close(fd[1]);
	ret = ft_pipe(data, fd[0], 2);
	waitpid(pid, NULL, 0);
	return (ret);
}
