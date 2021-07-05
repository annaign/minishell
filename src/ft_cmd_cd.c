/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:38:02 by rmanfred          #+#    #+#             */
/*   Updated: 2020/11/24 20:38:03 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bash command: cd [-L|[-P [-e]] [-@] [directory]
**    minishell: cd with only a relative or absolute path
*/

#include "minishell.h"

extern t_env	g_e;

void	ft_cmd_cd(char **arg)
{
	int		ret;
	char	*path;

	g_e.exit_status = 0;
	ret = 0;
	path = arg[1];
	if (!arg[1])
	{
		path = ft_get_env("HOME");
		if (!path)
			ft_err_exit();
	}
	else if (arg[2] != NULL)
	{
		g_e.exit_status = 1;
		ft_putstr_fd(SH"cd: too many arguments\n", 2);
		return ;
	}
	ret = chdir(path);
	if (ret == -1)
		msg_err(1, SH"cd: ", arg[1], strerror(errno));
}
