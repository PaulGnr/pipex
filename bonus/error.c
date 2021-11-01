/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:37:57 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/29 18:12:09 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	error_catch(int test, char *file, char *msg)
{
	char	*str;
	char	*tmp;

	if (test)
	{
		if (file)
		{
			tmp = ft_strjoin("Pipex: ", file);
			str = ft_strjoin(tmp, ": ");
			free(tmp);
			tmp = ft_strjoin(str, msg);
			free(str);
		}
		else
			tmp = ft_strjoin("Pipex: ", msg);
		str = ft_strjoin(tmp, "\n");
		free(tmp);
		if (error_catch(!str, NULL, "Malloc failed"))
			return (1);
		ft_putstr_fd(str, 2);
		free(str);
	}
	return (test);
}
