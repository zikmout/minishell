/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 09:01:54 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/31 11:52:33 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sh1.h"

int			sh_setenv(char *cmd, t_env *e)
{
	char	*value;

	if (e->cmd[1] && check_var_env(e->cmd[1]))
		return (0);
	if (e->cmd[1] != NULL)
		set_var_env(e->cmd[1], e->cmd[2], e);
	else
		ft_printf("usage: env [-i] [name=value...]\n");
	return (0);
}

int			sh_unsetenv(char *cmd, t_env *e)
{
	if (unset_var_env(e->cmd[1], e) == 0)
		ft_printf("setenv: la variable '%s' est introuvable\n", e->cmd[1]);
	else
		ft_printf("unsetenv: environment variable uccessfully removed.\n");
	return (0);
}

int			sh_env(char *cmd, t_env *e)
{
	int		i;

	if (e->cmd[1] && ft_strcmp(e->cmd[1], "-i") == 0)
	{
		free_env(e->envp);
		ft_printf("env: environment successfully unset.\n");
	}
	else if (e->cmd[1] == NULL)
	{
		i = 0;
		while (e->envp[i])
		{
			ft_printf("%s\n", e->envp[i]);
			i++;
		}
	}
	else
		ft_printf("Usage: setenv [var_name] [var_value]\n");
	return (0);
}

char		*g_builtin_str[] = { "exit", "help", "setenv", "unsetenv",
	"env", "sh_status" };

int			(*g_built_func[]) (char *, t_env *) = {
	&sh_exit,
	&sh_help,
	&sh_setenv,
	&sh_unsetenv,
	&sh_env,
	&sh_status
};

int			sh_builtin_len(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
}

int			sh_execute(char *cmd, t_env *e)
{
	int		i;

	i = 0;
	while (i < sh_builtin_len())
	{
		if (ft_strcmp(e->cmd[0], g_builtin_str[i]) == 0)
			return ((*g_built_func[i])(cmd, e));
		i++;
	}
	return (1);
}
