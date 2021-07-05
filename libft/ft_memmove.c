/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 13:04:33 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/22 13:04:34 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			i;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = 0;
	if (ptr_src < ptr_dest)
		while (++i <= n)
			ptr_dest[n - i] = ptr_src[n - i];
	else if (ptr_src > ptr_dest)
		while (n-- > 0)
			*(ptr_dest++) = *(ptr_src++);
	return (dest);
}
