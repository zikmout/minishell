/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 09:56:52 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/27 19:51:47 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sh1.h"

char			*get_propper_pwd(t_env *e)
{
	char		buf[256];
	char		*pwd;

	if (ft_strncmp(e->cmd[1], "-", 1) == 0)
		pwd = get_var_env(e, "OLDPWD");
	else if (ft_strncmp(e->cmd[1], "~/", 2) == 0
			|| e->cmd[1][0] == '~')
		pwd = get_var_env(e, "HOME");
	else if (ft_strcmp(e->cmd[1], "/") == 0)
		pwd = ft_strdup("/");
	else if (e->cmd[1][0] == '/' && e->cmd[1][1])
		pwd = ft_strdup(e->cmd[1]);
	else
	{
		pwd = ft_strdup(getcwd(buf, 256));
		pwd = ft_strjoina(pwd, '/');
		pwd = ft_strjoin(pwd, e->cmd[1]);
	}
	return (pwd);
}

void			cd_cmd(t_env *e)
{
	struct stat	sb;
	char		buf[256];
	char		*pwd;
	char		*tmp;

	if (!e->cmd[1])
		return ;
	pwd = get_propper_pwd(e);
	stat(pwd, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		set_var_env("OLDPWD", e->cur_path, e);
		chdir(pwd);
		free(pwd);
		pwd = ft_strdup(getcwd(buf, 256));
		set_var_env("PWD", pwd, e);
		e->get_pwd = 0;
	}
	else if (S_ISREG(sb.st_mode))
		ft_printf("cd: not a directory: %s\n", e->cmd[1]);
	else
		ft_printf("cd: no such file or directory: %s\n", e->cmd[1]);
}

void			ft_wait(pid_t pid)
{
	int			status;
	int			r;

	r = waitpid(pid, &status, 0);
	while (1)
	{
		if (r < 0)
		{
			ft_putstr("\nerreur de waitpid\n");
			break ;
		}
		if (WIFEXITED(status))
			break ;
		if (WIFSIGNALED(status))
		{
			ft_putstr("\nterminaison par signal: ");
			ft_putnbr(WTERMSIG(status));
			ft_putstr("\n");
		}
		break ;
	}
}

void			siginthandler(int sig_num)
{
	ft_putstr("\n");
}

void			get_pwd_env(t_env *e)
{
	char		*cur_path;
	int			i;

	if (e->get_pwd == 1)
	{
		i = 0;
		while (e->envp[i])
		{
			if (ft_strncmp(e->envp[i], "PWD=", 4) == 0)
			{
				cur_path = ft_strsub(e->envp[i], 4, ft_strlen(e->envp[i]) - 4);
				break ;
			}
			i++;
		}
		e->cur_path = ft_strdup(cur_path);
	}
	else
		e->get_pwd = 1;
}
