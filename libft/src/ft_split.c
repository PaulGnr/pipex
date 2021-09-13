/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:19:32 by pguignie          #+#    #+#             */
/*   Updated: 2021/05/23 11:28:34 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tabsize(char const *s, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (i != 0 && s[i] != c && s[i - 1] == c))
			size++;
		i++;
	}
	return (size);
}

static void	ft_getstr(char const *s, char c, char **split)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
	{
		(*split)[i] = s[i];
		i++;
	}
	(*split)[i] = 0;
}

static void	ft_free_everything(char **split, int pos)
{
	while (pos--)
	{
		free(split[pos]);
		split[pos] = NULL;
	}
	free(split);
}

static int	ft_fillstr(char const *s, char c, char **split)
{
	int	pos;
	int	len;

	pos = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			len = 0;
			while (s[len] != c && s[len])
				len++;
			split[pos] = (char *)malloc(sizeof(char) * (len + 1));
			if (!split[pos])
			{
				ft_free_everything(split, pos);
				return (0);
			}
			ft_getstr(s, c, &split[pos]);
			s += len;
			pos++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		size;

	if (s == NULL)
		return (NULL);
	size = ft_tabsize(s, c);
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	if (!ft_fillstr(s, c, split))
		return (NULL);
	split[size] = NULL;
	return (split);
}
