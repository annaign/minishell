/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:09 by pshagwel          #+#    #+#             */
/*   Updated: 2020/12/16 00:02:11 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

extern t_env	g_e;

t_command	*ft_create_command(char **str_cmd)
{
	t_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		ft_err_exit();
	cmd->cmds = NULL;
	cmd->str = ft_strtrim(*str_cmd, " ");
	ft_free(str_cmd);
	ft_lstadd_back(&(g_e.cmd), ft_lstnew(cmd));
	if (!cmd->str)
		ft_err_exit();
	return (cmd);
}

char		*ft_filename(const char *line, char *str, int *i)
{
	int	begin;
	int	tmp;

	str[(*i)++] = '\0';
	if (str[(*i)] == '>')
		str[(*i)++] = '\0';
	while (str[*i] == ' ')
		str[(*i)++] = '\0';
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == '\0')
		return (NULL);
	begin = *i;
	while (!(ft_strchr(" ><", str[*i])) && str[*i] != '\0')
	{
		tmp = *i;
		if (ft_strchr("\\\"'", str[*i]))
		{
			ft_check_quotes(str, i);
			while (tmp != *i)
				str[tmp++] = '\0';
		}
		str[*i] = '\0';
		(*i)++;
	}
	(*i)--;
	return (ft_substr(line, begin, *i - begin + 1));
}
