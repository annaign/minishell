/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:22:40 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/22 16:22:42 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bash command: pwd [-LP]
**    minishell: pwd without any options
*/

#include "minishell.h"

extern t_env	g_e;

void	ft_cmd_pwd(void)
{
	char	buf[PATH_MAX];
	char	*pwd;

	g_e.exit_status = 0;
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		ft_err_exit();
	ft_printf("%s\n", pwd);
}
