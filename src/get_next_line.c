/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:00:36 by rmanfred          #+#    #+#             */
/*   Updated: 2020/06/25 12:47:25 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

static	char	*to_join(int bytes_to_read, char *buf, char *to_save)
{
	char		*temp;

	buf[bytes_to_read] = '\0';
	temp = to_save;
	to_save = ft_strjoin(to_save, buf);
	free(temp);
	temp = NULL;
	return (to_save);
}

static	int		get_result(char **line, char **to_save)
{
	char		*find_n;
	char		*temp;

	find_n = ft_strchr(*to_save, '\n');
	*find_n = '\0';
	if (!(*line = ft_strdup(*to_save)))
	{
		ft_free(to_save);
		return (-1);
	}
	find_n++;
	temp = *to_save;
	if (!(*to_save = ft_strdup(find_n)))
	{
		free(temp);
		temp = NULL;
		return (-1);
	}
	free(temp);
	temp = NULL;
	ft_free(to_save);
	return (1);
}

static	int		check_result(int byt, char **line, char **save, int f)
{
	if (byt == 0 && f == 1)
	{
		ft_free(save);
		return (0);
	}
	else if (byt < 0)
	{
		ft_free(save);
		return (-1);
	}
	else if (byt == 0)
	{
		if (!(*line = ft_strdup(*save)))
		{
			ft_free(save);
			return (-1);
		}
		ft_free(save);
		return (0);
	}
	else
		return (get_result(line, save));
}

int				get_next_line(int fd, char **line)
{
	static char	*s;
	char		*buf;
	int			bytes_to_read;

	if ((fd < 0) || !line || (BUFFER_SIZE < 1) || (!s && !(s = ft_strdup(""))))
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		ft_free(&s);
		return (-1);
	}
	while ((!(ft_strchr(s, '\n')))
		&& ((bytes_to_read = read(fd, buf, BUFFER_SIZE)) >= 0))
		if (bytes_to_read == 0 && !ft_strlen(s))
		{
			free(buf);
			return (check_result(bytes_to_read, line, &s, 1));
		}
		else if (!(s = to_join(bytes_to_read, buf, s)))
		{
			free(buf);
			return (-1);
		}
	free(buf);
	return (check_result(bytes_to_read, line, &s, 0));
}
