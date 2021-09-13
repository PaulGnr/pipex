/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulguignier <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:10:25 by paulguign         #+#    #+#             */
/*   Updated: 2021/08/23 00:44:18 by paulguign        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *lst)
{
	t_list	*cpy;
	t_list	*new;

	cpy = NULL;
	while (lst)
	{
		new = ft_lstnew(lst->content);
		ft_lstadd_back(&cpy, new);
		lst = lst->next;
	}
	return (cpy);
}
