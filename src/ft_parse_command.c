/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 01:05:57 by pshagwel          #+#    #+#             */
/*   Updated: 2020/12/04 01:05:59 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

extern t_env	g_e;

static int		ft_count_cmds(char *str, char delimetr)
{
	int	i;
	int	sum;

	sum = 1;
	i = -1;
	while (str[++i] != '\0')
	{
		if (!(ft_check_quotes(str, &i)))
		{
			msg_err(2, SH, "", "not support multiline commands");
			ft_clear_command();
			return (-1);
		}
		if (str[i] == delimetr)
			sum++;
	}
	return (sum);
}

static void		ft_parse_cmd(t_cmd *cmd, char *line, int len)
{
	int		first;
	int		last;

	first = 0;
	last = 0;
	while (line[last] != '\0')
	{
		if (line[last] == '\\' || line[last] == '"' || line[last] == '\'')
			ft_check_quotes(line, &last);
		if (line[last] == ' ' || line[last + 1] == '\0')
		{
			line[last] = (line[last] == ' ') ? '\0' : line[last];
			cmd->cmd[len] = ft_strdup(&line[first]);
			if (!cmd->cmd[len++])
				ft_err_exit();
			last++;
			while (line[last] != '\0' && line[last] == ' ')
				last++;
			first = last;
			continue;
		}
		last++;
	}
	ft_free(&line);
}

static int		ft_create_cmd(char *s, int *i, int *begin, t_cmd *cmd)
{
	char	*line;
	int		len;

	if ((*i == 0 && *i == *begin && s[*i] == '|') || s[*i + 1] == '|')
	{
		msg_err(2, SH, "", "syntax error near unexpected token `|'");
		ft_clear_command();
		return (FALSE);
	}
	cmd->pipe = (s[*i] == '|');
	s[*i] = (s[*i] == '|') ? '\0' : s[*i];
	line = ft_strtrim(&s[*begin], " ");
	*begin = *i + 1;
	if (!(ft_parse_redicrect(&line, cmd)))
	{
		ft_free(&line);
		return (FALSE);
	}
	if ((len = ft_count_cmds(line, ' ')) < 0)
		len = 1;
	cmd->cmd = malloc(sizeof(char *) * (len + 1));
	while (len >= 0)
		cmd->cmd[len--] = NULL;
	ft_parse_cmd(cmd, line, 0);
	return (TRUE);
}

static int		ft_parse_cmds(t_command *cmd, int len)
{
	int			i;
	int			begin;

	i = -1;
	begin = 0;
	while (cmd->str[++i] != '\0')
	{
		ft_check_quotes(cmd->str, &i);
		if (cmd->str[i] == '|' && cmd->str[i + 1] == '\0')
		{
			msg_err(2, SH, "", "syntax error near unexpected token `|'");
			ft_clear_command();
			return (FALSE);
		}
		if (cmd->str[i] == '|' || cmd->str[i + 1] == '\0')
		{
			if (!(cmd->cmds[len] = malloc(sizeof(t_cmd))))
				ft_err_exit();
			ft_init_cmd(cmd->cmds[len]);
			if (!(ft_create_cmd(cmd->str, &i, &begin, cmd->cmds[len++])))
				break ;
		}
	}
	return (TRUE);
}

int				ft_parse_command(char **str_cmd)
{
	t_command	*cmd;
	int			len;

	cmd = ft_create_command(str_cmd);
	if ((len = ft_count_cmds(cmd->str, '|')) < 0)
		return (TRUE);
	if (!(cmd->cmds = malloc(sizeof(t_cmd *) * (len + 1))))
		ft_err_exit();
	while (len >= 0)
		cmd->cmds[len--] = NULL;
	if (ft_parse_cmds(cmd, 0))
		return (TRUE);
	else
	{
		ft_clear_command();
		return (FALSE);
	}
}
