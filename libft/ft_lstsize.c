/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 00:43:50 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/27 00:43:53 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int size;

	size = 0;
	if (lst)
	{
		while (lst)
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}
