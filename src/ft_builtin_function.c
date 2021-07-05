/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:53:49 by pshagwel          #+#    #+#             */
/*   Updated: 2020/12/17 14:53:51 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

int		ft_builtin_function(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_cmd_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_cmd_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_cmd_export(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_cmd_env();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cmd_cd(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_cmd_unset(cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_cmd_exit(cmd, 0);
	else
		return (0);
	ft_free_memory();
	exit(g_e.exit_status);
	return (1);
}
