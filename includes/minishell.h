/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 19:42:05 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/20 19:42:07 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** malloc, free, write, open, read, close, fork, wait,
** waitpid, wait3, wait4, signal, kill, exit, getcwd,
** chdir, stat, lstat, fstat, execve, dup, dup2, pipe,
** opendir, readdir, closedir, strerror, errno
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include "ft_limits.h"
# include "libft.h"
# include "libftprintf.h"

# ifndef PATH_MAX
#  define PATH_MAX	1024
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# define SH "minishell: "
# define GREEN "\e[1;32m"
# define YELLOW "\e[0;33m"
# define RESET "\e[00m"

# ifndef BUFFER_SIZE2
#  define BUFFER_SIZE2 64
# endif

typedef	struct	s_pars
{
	char		f_slash;
	char		f_d_qoute;
	char		f_space;
	char		f_option_n;
	char		f_init_n;
	char		*ret;
	int			num;
}				t_pars;

typedef struct	s_env
{
	char		**env;
	char		*pars;
	char		*line;
	t_list		*cmd;
	t_pars		sign;
	pid_t		pid;
	int			exit_status;
}				t_env;

/*
** t_cmd files if redirect
**  f_0 : <  (0>file) reading
**  f_1 : >  (1>file) writing
**  f_2 : >> (1>file) appending
**  rdr_last : 0, 1, 2 or -1 if no
*/

typedef struct	s_cmd
{
	char		**cmd;
	int			rdr_last;
	t_list		*f_0;
	t_list		*f_1;
	t_list		*f_2;
	int			pipe;
	int			fdin;
	int			fdout;
	int			fdpipe[2];
	int			err_pipe[2];
}				t_cmd;

typedef struct	s_command
{
	char		*str;
	t_cmd		**cmds;
}				t_command;

void			ft_init(char *envp[]);
void			ft_init_cmd(t_cmd *cmd);
void			ft_copy_env(char ***env, char *envp[]);
void			ft_main_arg_exit(char *arg);
void			ft_err_exit(void);
void			msg_err(int status, char *msg1, char *arg, char *msg2);
void			msg_err2(int status, char *msg1, char *arg, char *msg2);
void			ft_free_split_arr(char **arr);
void			ft_free_cmd(void *ptr);
void			ft_free_memory(void);
void			ft_clear_command(void);
void			ft_read_command(void);
int				ft_check_quotes(char *s, int *i);
int				ft_parse_command(char **str_cmd);
void			ft_cmd_pwd(void);
void			ft_cmd_export(char **arg);
void			ft_cmd_env(void);
void			ft_cmd_exit(char **arg, int print);
void			ft_cmd_echo(char **arg);
void			ft_cmd_cd(char **arg);
void			ft_cmd_unset(char **arg);
void			ft_cmd_external(char **arg);
int				ft_check_env_var(char *arg);
void			ft_env_add_var(char *var);
int				ft_env_search_var(char *var);
void			ft_single_quote(char *arg);
void			ft_back_slash(char *arg);
void			ft_double_quote(char *arg);
int				ft_slash_in_d_quote(char *arg);
void			ft_init_parse(void);
void			ft_dup2(int fd_old, int fd_new, char *cmd);
char			*ft_get_env(char *arg);
char			*ft_parse_signs(char *arg);
char			*ft_strjoin_c(char *s2, char c, int f);
void			ft_parse_arg(char *arg);
void			ft_parse_dollar(char *arg);
void			ft_parse_tool(char *arg);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_parse_str(char *arg);
void			ft_transform_cmd(t_cmd *cmd);
char			*ft_get_path(char *ptr);
void			ft_run_pipe(t_cmd *cmd[]);
void			ft_signals(int sig);
void			ft_check_waitpid_status(int status);
void			ft_prompt(void);
void			ft_read_exit(void);
void			ft_run_redirect(t_cmd *cmd);
int				ft_builtin_function(char **cmd);
void			ft_parent_exit(char **arg, pid_t pid);

int				ft_open_fd(t_list *lst, int flags, char mode, int fd_old);
int				ft_open_fd_select(t_cmd *cmd, int fd_old);

t_command		*ft_create_command(char **str_cmd);
char			*ft_filename(const char *line, char *str, int *i);
int				ft_parse_redicrect(char **line, t_cmd *cmd);

int				ft_read_fd(int fd, char **line);

#endif
