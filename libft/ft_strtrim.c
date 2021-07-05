/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:46:00 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/08 22:46:03 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*ptr;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	ptr = (char *)s1;
	while (*ptr && ft_strchr(set, *ptr))
		ptr++;
	len = ft_strlen(ptr);
	while (len && ft_strchr(set, ptr[len]))
		len--;
	str = ft_substr(ptr, 0, len + 1);
	return (str);
}
