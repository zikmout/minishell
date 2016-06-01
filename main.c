/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 08:41:13 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/27 19:49:57 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

static int		norm(t_env *e, int ret, char *line, char **envp)
{
	if (e->cmd[0] == 0)
		ft_printf("\n");
	ft_printf("\033[31msh1$> \033[m");
	ret = get_next_line(0, &line);
	if (*envp)
		get_pwd_env(e);
	e->cmd = get_cmd(e, line);
	return (ret);
}

void			sh_start(t_env *e, char *line, char **envp, char **av)
{
	int			ret;

	while (1)
	{
		ret = norm(e, ret, line, envp);
		if (e->cmd[0] != NULL && sh_execute(line, e) && ret == 1)
		{
			if (ft_strncmp(e->cmd[0], "cd", 2) == 0)
				cd_cmd(e);
			else if (access(e->cmd[0], F_OK) == 0)
				ft_exec(e);
			else
				ft_execute(av, line, e);
			signal(SIGINT, siginthandler);
		}
		if (ret == 0)
			ft_putchar('\n');
	}
}

int				main(int ac, char **av, char **envp)
{
	char		*line;
	t_env		*e;
	int			ret;

	ret = 0;
	if (!(e = (t_env *)malloc(sizeof(t_env))))
		return (0);
	init_env(e, envp);
	sh_start(e, line, envp, av);
}
