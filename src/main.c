/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 19:40:54 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/21 19:35:27 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	g_e;

void		ft_prompt(void)
{
	char	*pwd;
	char	buf[PATH_MAX];

	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		ft_err_exit();
	ft_printf(GREEN"minishell:"YELLOW"%s"RESET"$ ", pwd);
}

static void	ft_transform_lst(t_list *ptr)
{
	t_list	*lst;
	char	*tmp;

	lst = ptr;
	while (lst)
	{
		tmp = ft_parse_str(lst->content);
		free(lst->content);
		lst->content = tmp;
		lst = lst->next;
	}
}

void		ft_transform_cmd(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (cmd->cmd[++i])
	{
		tmp = ft_parse_str(cmd->cmd[i]);
		free(cmd->cmd[i]);
		cmd->cmd[i] = tmp;
	}
	ft_transform_lst(cmd->f_0);
	ft_transform_lst(cmd->f_1);
	ft_transform_lst(cmd->f_2);
}

static void	ft_run_command(t_command *ptr)
{
	char	*cmd;
	int		i;

	i = -1;
	while (ptr->cmds[++i] != NULL)
	{
		ft_transform_cmd(ptr->cmds[i]);
		cmd = ptr->cmds[i]->cmd[0];
		if (ft_strcmp(cmd, "echo") == 0)
			ft_cmd_echo(ptr->cmds[i]->cmd);
		else if (ft_strcmp(cmd, "cd") == 0)
			ft_cmd_cd(ptr->cmds[i]->cmd);
		else if (ft_strcmp(cmd, "pwd") == 0)
			ft_cmd_pwd();
		else if (ft_strcmp(cmd, "export") == 0)
			ft_cmd_export(ptr->cmds[i]->cmd);
		else if (ft_strcmp(cmd, "unset") == 0)
			ft_cmd_unset(ptr->cmds[i]->cmd);
		else if (ft_strcmp(cmd, "env") == 0)
			ft_cmd_env();
		else if (ft_strcmp(cmd, "exit") == 0)
			ft_cmd_exit(ptr->cmds[i]->cmd, 1);
		else
			ft_cmd_external(ptr->cmds[i]->cmd);
	}
}

int			main(int argc, char *argv[], char *envp[])
{
	t_list	*ptr;

	if (argc != 1)
		ft_main_arg_exit(argv[0]);
	ft_init(envp);
	while (TRUE)
	{
		ft_signals(1);
		ft_prompt();
		ft_read_command();
		ptr = g_e.cmd;
		while (ptr)
		{
			if (((t_command *)ptr->content)->cmds[0]->pipe == 1)
				ft_run_pipe(((t_command *)ptr->content)->cmds);
			else if (((t_command *)ptr->content)->cmds[0]->rdr_last != -1)
				ft_run_redirect(((t_command *)ptr->content)->cmds[0]);
			else
				ft_run_command((t_command *)ptr->content);
			ptr = ptr->next;
		}
		ft_clear_command();
	}
	return (0);
}
