/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:19:08 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/24 15:19:09 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

void	ft_free_split_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

void	ft_free_cmd(void *ptr)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *)ptr;
	free(cmd->str);
	cmd->str = NULL;
	i = -1;
	while (cmd->cmds && cmd->cmds[++i] != NULL)
	{
		if (cmd->cmds[i]->cmd)
			ft_free_split_arr(cmd->cmds[i]->cmd);
		ft_lstclear(&cmd->cmds[i]->f_0, free);
		ft_lstclear(&cmd->cmds[i]->f_1, free);
		ft_lstclear(&cmd->cmds[i]->f_2, free);
		free(cmd->cmds[i]);
		cmd->cmds[i] = NULL;
	}
	free(cmd->cmds);
	cmd->cmds = NULL;
	free(cmd);
	cmd = NULL;
}

void	ft_clear_command(void)
{
	if (g_e.cmd)
		ft_lstclear(&g_e.cmd, ft_free_cmd);
}

void	ft_free_memory(void)
{
	free(g_e.line);
	g_e.line = NULL;
	if (g_e.env)
		ft_free_split_arr(g_e.env);
	ft_clear_command();
}
