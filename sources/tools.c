/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 10:08:23 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/27 19:37:32 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sh1.h"

char			*epur_str(char *s1)
{
	char		*s2;
	int			i;

	s2 = ft_strdup("\0");
	i = 0;
	while (s1[i])
	{
		while (s1[i] && s1[i] != ' ' && s1[i] != '\t')
		{
			s2 = ft_strjoina(s2, s1[i]);
			i++;
		}
		while (s1[i] && (s1[i] == ' ' || s1[i] == '\t'))
			i++;
		if (s1[i])
			s2 = ft_strjoina(s2, ' ');
	}
	return (s2);
}

void			ft_exec(t_env *e)
{
	struct stat	sb;
	pid_t		status;
	pid_t		pid;

	pid = fork();
	if (pid != 0)
		wait(&status);
	else
	{
		execve(e->cmd[0], e->cmd, e->envp);
		put_error(e);
		exit(42);
	}
}

void			ft_execute(char **av, char *line, t_env *e)
{
	int			i;
	pid_t		status;
	int			count;

	e->name = ft_strdup(e->cmd[0]);
	count = 0;
	i = -1;
	if (e->path == NULL)
		sh_start(e, line, e->envp, av);
	while (e->path[++i])
	{
		e->cmd[0] = ft_strjoin(e->path[i], e->cmd[0]);
		if (access(e->cmd[0], F_OK) == 0)
			ft_exec(e);
		else
			count++;
		free(e->cmd[0]);
		e->cmd[0] = ft_strdup(e->name);
	}
	if (count == 6)
		ft_printf("sh1: command not found: %s\n", e->name);
	if (WIFEXITED(status) && e->sh_status)
		ft_printf("->child pid exited with %d\n", WEXITSTATUS(status));
	if (WIFSIGNALED(status) && e->sh_status)
		ft_printf("\nsh1: terminaison par signal %d\n", WTERMSIG(status));
}

void			put_error(t_env *e)
{
	if (access(e->cmd[0], X_OK) != 0)
		ft_printf("sh1: permission denied : %s\n",
				ft_strsub(e->cmd[0], 2, ft_strlen(e->cmd[0])));
}
