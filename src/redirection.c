/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:38:12 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/30 14:38:49 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_infile(t_data *data, int *fd, int fd_in, int step)
{
	close(fd[0]);
	if (step == 1)
	{
		fd[0] = open(data->argv[1], O_RDONLY);
		if (error_catch(fd[0] < 0, data->argv[1], strerror(errno)))
			exit (ft_free_data(data, 1));
	}
	else
		fd[0] = fd_in;
	return (fd[0]);
}

int	ft_get_outfile(t_data *data, int *fd, int step)
{
	if (step == data->argc - 3)
	{
		close(fd[1]);
		fd[1] = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (error_catch(fd[1] < 0, data->argv[data->argc - 1],
				strerror(errno)))
			exit (ft_free_data(data, 1));
	}
	return (fd[1]);
}
