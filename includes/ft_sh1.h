/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 10:06:21 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/27 19:32:06 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H
# define LABEL "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
# include "../libft/libft.h"
# include "../libft/printf.h"
# include <pwd.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_env	t_env;
struct	s_env
{
	char			*cur_path;
	char			**path;
	char			**cmd;
	char			*name;
	int				get_pwd;
	char			**envp;
	pid_t			child_pid;
	int				sh_status;
};
/*
** tools.c
*/
void	put_error(t_env *e);
void	ft_execute(char **av, char *line, t_env *e);
void	ft_exec(t_env *e);
char	*epur_str(char *s1);
/*
** struct.c
*/
void	init_env(t_env *e, char **envp);
char	**get_env(t_env *e);
char	**get_cmd(t_env *e, char *line);
char	**env_cpy(char **envp, size_t nb, int free_it);
void	free_env(char **envp);
/*
** builtins.c
*/
int		sh_setenv(char *cmd, t_env *e);
int		sh_unsetenv(char *cmd, t_env *e);
int		sh_env(char *cmd, t_env *e);
int		sh_builtin_len();
int		sh_execute(char *cmd, t_env *e);
/*
** builtins2.c
*/
int		sh_help(char *cmd, t_env *e);
int		sh_status(char *cmd, t_env *e);
int		sh_exit(char *cmd, t_env *e);
/*
** cd_pwd.c
*/
void	cd_cmd(t_env *e);
void	ft_wait(pid_t pid);
void	siginthandler(int sig_num);
char	*get_propper_pwd(t_env *e);
void	get_pwd_env(t_env *e);
/*
** var_env.c
*/
char	*get_var_env(t_env *e, char *var);
int		unset_var_env(char *var_name, t_env *e);
void	set_var_env(char *var_name, char *value, t_env *e);
int		check_var_env(char *str);
int		check_exist(t_env *e, char *var_name);
void	sh_start(t_env *e, char *line, char **envp, char **av);
#endif
