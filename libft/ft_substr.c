/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 10:12:51 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/08 10:12:53 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			len_to_end;

	if (!s || len <= 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	len_to_end = ft_strlen(&s[start]);
	if (len_to_end < len)
		len = len_to_end;
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str)
	{
		while ((s[start + i] != '\0') && (i <= len))
		{
			str[i] = s[start + i];
			i++;
		}
		str[len] = '\0';
	}
	return (str);
}
