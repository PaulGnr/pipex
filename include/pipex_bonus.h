/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:32:22 by paulguign         #+#    #+#             */
/*   Updated: 2021/10/23 22:02:38 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**env;
	int		fd_in;
}	t_data;

int		error_catch(int test, char *file, char *msg);
void	ft_pipe(t_data *data, int fd_in, int fd_out, int step);
void	here_doc(t_data *data, char *limiter);
void	ft_free_split(char **split);
int		ft_free_data(t_data *data);

#endif
