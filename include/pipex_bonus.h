/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:32:22 by paulguign         #+#    #+#             */
/*   Updated: 2021/11/05 00:56:29 by paulguign        ###   ########.fr       */
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
	int		oflag;
}	t_data;

int		error_catch(int test, char *file, char *msg);
int		ft_pipe(t_data *data, int fd_in, int step);
char	*ft_getcmd(char *arg, char **env);
int		ft_get_infile(t_data *data, int *fd, int fd_in, int step);
int		ft_get_outfile(t_data *data, int *fd, int step);
int		here_doc(t_data *data, char *limiter);
void	ft_free_split(char **split);

#endif
