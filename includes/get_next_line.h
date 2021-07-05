/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 23:27:13 by pshagwel          #+#    #+#             */
/*   Updated: 2020/06/28 23:27:14 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

int		get_next_line(int fd, char **line);
void	ft_free(char **str);

#endif
