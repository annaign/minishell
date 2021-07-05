/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 23:26:28 by pshagwel          #+#    #+#             */
/*   Updated: 2020/06/28 23:26:29 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	gnl_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

static void	ft_strjoin_gnl(char **line, char const *buf)
{
	char	*new_line;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(*line);
	len2 = ft_strlen(buf);
	new_line = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_line)
	{
		i = -1;
		while (++i < len1)
			new_line[i] = line[0][i];
		i = -1;
		while (++i < len2)
			new_line[len1 + i] = buf[i];
		new_line[len1 + len2] = '\0';
	}
	free(*line);
	*line = new_line;
}

int			ft_read_fd(int fd, char **line)
{
	char		*b;
	ssize_t		size;
	char		*ptr;

	if (!line || BUFFER_SIZE2 < 0 || (size = read(fd, &ptr, 0)) ||
		!(b = malloc(sizeof(char) * (BUFFER_SIZE2 + 1))))
		return (FALSE);
	*line = ft_strdup("");
	while (line && (size = read(fd, b, BUFFER_SIZE2)) && size != EOF)
	{
		b[size] = '\0';
		ft_strjoin_gnl(line, b);
	}
	gnl_free(&b);
	if (!line)
		return (FALSE);
	return (TRUE);
}
