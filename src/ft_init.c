/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 23:39:29 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/21 23:39:31 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

void	ft_dup2(int fd_old, int fd_new, char *cmd)
{
	if (dup2(fd_old, fd_new) < 0)
	{
		msg_err(1, SH, cmd, strerror(errno));
		ft_free_memory();
		exit(1);
	}
	close(fd_old);
}

void	ft_copy_env(char ***env, char *envp[])
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env[0] = malloc(sizeof(char *) * (i + 1));
	if (!env)
		ft_err_exit();
	i = 0;
	while (envp[i] != NULL)
	{
		env[0][i] = ft_strdup(envp[i]);
		if (!env[0][i])
			ft_err_exit();
		i++;
	}
	env[0][i] = NULL;
}

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->rdr_last = -1;
	cmd->f_0 = NULL;
	cmd->f_1 = NULL;
	cmd->f_2 = NULL;
	cmd->pipe = 0;
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->fdpipe[0] = -1;
	cmd->fdpipe[1] = -1;
	cmd->err_pipe[1] = -1;
	cmd->err_pipe[1] = -1;
}

void	ft_init_parse(void)
{
	g_e.sign.f_d_qoute = 0;
	g_e.sign.f_slash = 1;
	g_e.sign.f_space = 0;
	g_e.sign.num = 1;
	if (!(g_e.sign.ret = ft_strdup("")))
		ft_err_exit();
}

void	ft_init(char *envp[])
{
	g_e.env = NULL;
	g_e.pars = NULL;
	g_e.line = NULL;
	g_e.cmd = NULL;
	g_e.pid = 0;
	g_e.exit_status = 0;
	if (envp)
		ft_copy_env(&(g_e.env), envp);
}
