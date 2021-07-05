/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:37:43 by rmanfred          #+#    #+#             */
/*   Updated: 2020/11/24 20:37:45 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bash command: unset [-fnv] [name]
**    minishell: unset without any options
*/

#include "minishell.h"

extern t_env	g_e;

static void	ft_unset_del_var(char *arg, size_t len)
{
	size_t	i;

	i = -1;
	while (g_e.env[++i] != NULL)
	{
		if ((ft_strncmp(g_e.env[i], arg, len)) == 0)
		{
			free(g_e.env[i]);
			g_e.env[i] = g_e.env[i + 1];
			while (g_e.env[i] != NULL)
			{
				g_e.env[i] = g_e.env[i + 1];
				i++;
			}
			break ;
		}
	}
}

void		ft_cmd_unset(char **arg)
{
	size_t	len;
	int		i;

	g_e.exit_status = 0;
	if (!arg[1])
		return ;
	i = 0;
	while (arg[++i] != NULL)
	{
		len = ft_strlen(arg[i]);
		if (len == 0 || !(ft_check_env_var(arg[i])))
		{
			msg_err2(1, SH"unset", arg[i], "not a valid identifier");
			return ;
		}
		ft_unset_del_var(arg[i], len);
	}
}
