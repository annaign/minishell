/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 00:51:34 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/27 00:51:36 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last_lst;

	if (lst)
	{
		if (*lst)
		{
			last_lst = ft_lstlast(*lst);
			last_lst->next = new;
		}
		else
			*lst = new;
	}
}
