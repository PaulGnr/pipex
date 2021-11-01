/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:30:58 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/30 14:06:26 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_data	*init_data(int argc, char **argv, char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (error_catch(!data, NULL, "Malloc failed"))
		return (NULL);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc == 5)
	{
		data = init_data(argc, argv, env);
		if (!data)
			return (1);
		return (ft_pipe(data, -1, 1));
	}
	else
		return (error_catch(1, NULL, "Error of arguments"));
	return (0);
}
