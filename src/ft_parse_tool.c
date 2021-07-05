/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:12:06 by rmanfred          #+#    #+#             */
/*   Updated: 2020/12/02 18:12:07 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

char		*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str)
	{
		i = -1;
		while (++i < (int)ft_strlen(s1))
			str[i] = s1[i];
		i = -1;
		while (++i < (int)ft_strlen(s2))
			str[ft_strlen(s1) + i] = s2[i];
		str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	}
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (str);
}

char		*ft_strjoin_c(char *s2, char c, int f)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!c && !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen_l(s2) + 2))))
		return (NULL);
	while (s2[i])
		str[j++] = s2[i++];
	if (c)
		str[j++] = c;
	str[j] = '\0';
	if (f == 1)
	{
		free(s2);
		s2 = NULL;
	}
	return (str);
}

void		ft_parse_tool(char *arg)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (arg[i] == '?')
		ret = ft_itoa(g_e.exit_status);
	else if (arg[i] != '\'' && arg[i] != '\"' && g_e.sign.f_d_qoute != 1)
	{
		ret = ft_strdup("$");
		ret = ft_strjoin_c(ret, arg[i], 1);
	}
	else if (arg[i] != '\'' && arg[i] != '\"')
		ret = ft_strdup("$");
	if (!ret && arg[i] != '\'' && arg[i] != '\"')
		ft_err_exit();
	if (ret && !(g_e.sign.ret = ft_strjoin_free(g_e.sign.ret, ret)))
		ft_err_exit();
	if (g_e.sign.f_d_qoute != 1 && ((arg[i] != '\'' && arg[i] != '\"')
		|| ft_isalpha(arg[i + 1]) || arg[i + 1] == '\\'))
		ft_parse_arg(&arg[++i]);
	else if (g_e.sign.f_d_qoute != 1)
		ft_parse_arg(&arg[i + 2]);
}
