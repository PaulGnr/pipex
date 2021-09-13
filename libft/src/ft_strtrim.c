/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 09:10:04 by pguignie          #+#    #+#             */
/*   Updated: 2021/05/23 14:16:03 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char const c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

static size_t	ft_trimsize(char const *s1, char const *set)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s1[i] && ft_isinset(s1[i++], set))
		count++;
	i = ft_strlen(s1);
	while (i && s1[--i] && ft_isinset(s1[i], set))
		count++;
	if (count > ft_strlen(s1))
		return (0);
	return (ft_strlen(s1) - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	*trim;

	if (s1 == NULL)
		return (NULL);
	count = ft_trimsize(s1, set);
	trim = (char *)malloc(sizeof(char) * (count + 1));
	if (!trim)
		return (NULL);
	i = 0;
	while (s1[i] && ft_isinset(s1[i], set))
		i++;
	j = i;
	while (i - j < count)
	{
		trim[i - j] = s1[i];
		i++;
	}
	trim[i - j] = 0;
	return (trim);
}
