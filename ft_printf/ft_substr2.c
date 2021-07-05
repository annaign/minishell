/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:14:55 by rmanfred          #+#    #+#             */
/*   Updated: 2020/06/21 15:52:40 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_substr2(char const *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen_l(s) <= start)
		return (ft_strdup(""));
	if (len > (ft_strlen_l(s) - start))
		len = ft_strlen_l(s) - start;
	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
