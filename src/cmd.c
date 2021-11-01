/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <pguignie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:13:20 by pguignie          #+#    #+#             */
/*   Updated: 2021/10/29 18:08:57 by pguignie         ###   ########.fr       */
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

char	*ft_try_path(char *arg, char *path)
{
	char	*join;
	char	**multi_path;
	int		i;
	int		fd;

	multi_path = ft_split(path, ':');
	i = 0;
	while (multi_path[i])
	{
		join = ft_strjoin_slash(multi_path[i++], arg);
		if (!join)
			return (NULL);
		fd = open(join, O_RDONLY);
		if (fd >= 0)
		{
			ft_free_split(multi_path);
			return (join);
		}
		free(join);
	}
	ft_free_split(multi_path);
	return (NULL);
}

char	*ft_getcmd(char *arg, char **env)
{
	char	*path;
	char	*join;
	int		i;
	int		fd;

	fd = open(arg, O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		join = ft_strdup(arg);
		if (error_catch(!join, NULL, "Malloc failed"))
			return (NULL);
		return (join);
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i] || !arg)
		return (NULL);
	path = &(env[i][5]);
	return (ft_try_path(arg, path));
}
