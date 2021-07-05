/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 18:29:41 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/22 18:29:43 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (str)
	{
		i = 0;
		while (i < len)
		{
			str[i] = s[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
