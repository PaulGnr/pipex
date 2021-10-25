/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:30:58 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/25 14:54:28 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static t_data	*init_data(int argc, char **argv, char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (error_catch(!data, NULL, "Malloc failed"))
		exit (1);
	data->argc = argc;
	data->argv = argv;
	if (error_catch(!env[0], NULL, "No environement"))
		exit (1);
	data->env = env;
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_out;
	t_data	*data;

	if (argc >= 5)
	{
		data = init_data(argc, argv, env);
		if (!ft_strncmp(argv[1], "here_doc", 9))
			here_doc(data, argv[2]);
		data->fd_in = open(argv[1], O_RDONLY);
		if (!ft_strncmp(argv[1], argv[argc - 1], ft_strlen(argv[1]) + 1))
			fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
		else
			fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (error_catch(data->fd_in < 0, argv[1], strerror(errno)))
			return (ft_free_data(data));
		if (error_catch(fd_out < 0, argv[argc - 1], strerror(errno)))
			return (ft_free_data(data));
		ft_pipe(data, data->fd_in, fd_out, 2);
	}
	else
	{
		error_catch(1, NULL, "Error of arguments");
		return (1);
	}
	return (0);
}
