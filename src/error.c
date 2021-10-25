/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:37:57 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/20 23:45:34 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_catch(int test, char *file, char *msg)
{
	if (test)
	{
		ft_putstr_fd("Pipex: ", 2);
		if (file)
		{
			ft_putstr_fd(file, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	return (test);
}
