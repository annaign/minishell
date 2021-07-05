/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 18:26:00 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/22 18:26:01 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*ptr_last;

	ptr = (char *)s;
	ptr_last = NULL;
	while (*ptr != '\0')
	{
		if (*ptr == c)
			ptr_last = ptr;
		ptr++;
	}
	if (c == '\0')
		return (ptr);
	return (ptr_last);
}
