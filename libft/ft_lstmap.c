/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 01:30:26 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/27 01:30:28 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;

	new_lst = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			elem = ft_lstnew(f(lst->content));
			if (!elem)
			{
				ft_lstclear(&new_lst, del);
				return (NULL);
			}
			ft_lstadd_back(&new_lst, elem);
			lst = lst->next;
		}
	}
	return (new_lst);
}
