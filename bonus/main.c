/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:30:58 by paulguign         #+#    #+#             */
/*   Updated: 2021/11/03 15:18:10 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static t_data	init_data(int argc, char **argv, char **env)
{
	t_data	data;

	data.argc = argc;
	data.argv = argv;
	data.env = env;
	data.here_doc = 0;
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc >= 5)
	{
		data = init_data(argc, argv, env);
		if (argc >= 7 && !ft_strncmp(argv[1], "here_doc", 9))
			return (here_doc(&data, argv[2]));
		else
			return (ft_pipe(&data, -1, 1));
	}
	else
		return (error_catch(1, NULL, "Error of arguments"));
	return (0);
}
