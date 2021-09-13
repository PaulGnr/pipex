/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguignie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:18:25 by pguignie          #+#    #+#             */
/*   Updated: 2021/05/22 15:49:29 by pguignie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	int		res;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	sign = 1;
	if (*str == 43 || *str == 45)
		sign *= 44 - *str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
		res = 10 * res + *str++ - '0';
	res *= sign;
	return (res);
}
