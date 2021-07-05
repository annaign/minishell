/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 01:16:48 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/27 01:16:50 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *elem;

	if (lst && del)
	{
		while (*lst)
		{
			del((*lst)->content);
			elem = *lst;
			*lst = elem->next;
			free(elem);
		}
		*lst = NULL;
	}
}
