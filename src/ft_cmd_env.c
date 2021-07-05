/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_g_e.env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:42:46 by rmanfred          #+#    #+#             */
/*   Updated: 2020/11/21 19:42:48 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bash command: env [option]… [name=value]… [command [args]…]
**    minishell: env without any options and any arguments
*/

#include "minishell.h"

extern t_env	g_e;

char		*ft_get_env(char *arg)
{
	int		j;
	int		len;
	char	*ret;

	j = 0;
	while (g_e.env[j])
	{
		if ((ft_strncmp(g_e.env[j], arg, ft_strlen(arg))) == 0
				&& g_e.env[j][ft_strlen(arg)] == '=')
		{
			len = ft_strlen(&g_e.env[j][ft_strlen(arg) + 1]);
			if (!(ret = ft_substr(&g_e.env[j][ft_strlen(arg) + 1], 0, len)))
				ft_err_exit();
			return (ret);
		}
		j++;
	}
	return (NULL);
}

int			ft_check_env_var(char *arg)
{
	int		i;

	i = -1;
	if (ft_isdigit(arg[0]))
		return (FALSE);
	while (arg[++i] != '\0')
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (FALSE);
	return (TRUE);
}

void		ft_env_add_var(char *var)
{
	int		i;
	char	**env_new;

	i = 0;
	while (g_e.env[i] != NULL)
		i++;
	env_new = malloc(sizeof(char *) * (i + 2));
	if (!env_new)
		ft_err_exit();
	i = -1;
	while (g_e.env[++i] != NULL)
		env_new[i] = g_e.env[i];
	env_new[i++] = var;
	env_new[i] = NULL;
	free(g_e.env);
	g_e.env = env_new;
}

int			ft_env_search_var(char *var)
{
	int		len;
	int		i;

	len = -1;
	while (var[++len] != '\0')
		if (var[len] == '=')
			break ;
	i = -1;
	while (g_e.env[++i] != NULL)
		if ((ft_strncmp(g_e.env[i], var, len)) == 0)
			return (i);
	return (-1);
}

void		ft_cmd_env(void)
{
	int		i;

	g_e.exit_status = 0;
	if (!g_e.env)
		return ;
	i = 0;
	while (g_e.env[i] != NULL)
	{
		ft_printf("%s\n", g_e.env[i]);
		i++;
	}
}
