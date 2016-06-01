/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 09:54:59 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/27 19:37:33 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sh1.h"

char		**get_cmd(t_env *e, char *line)
{
	char	**cmd;
	int		i;
	int		j;
	char	*tmp;

	if (!(cmd = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	cmd[0] = ft_strdup("\0");
	cmd[1] = ft_strdup("\0");
	cmd[2] = NULL;
	tmp = ft_strdup("\0");
	i = 0;
	tmp = ft_strtrim(line);
	if (tmp == NULL)
		exit(0);
	tmp = epur_str(tmp);
	tmp = ft_strtrim(tmp);
	cmd = ft_strsplit(tmp, ' ');
	return (cmd);
}

char		**get_env(t_env *e)
{
	int		i;
	char	*tmp;
	char	**path;

	i = 0;
	while (e->envp[i])
	{
		if (ft_strncmp(e->envp[i], "PATH=", 5) == 0)
		{
			tmp = ft_strsub(e->envp[i], 5, ft_strlen(e->envp[i]) - 5);
			path = ft_strsplit(tmp, ':');
			free(tmp);
			break ;
		}
		i++;
	}
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoina(path[i], '/');
		i++;
	}
	return (path);
}

void		init_env(t_env *e, char **envp)
{
	char	buf[256];
	char	*pwd;
	char	**tab;

	if (*envp)
	{
		e->envp = env_cpy(envp, 0, 0);
		e->path = get_env(e);
	}
	else
	{
		pwd = ft_strjoin("PWD=", ft_strdup(getcwd(buf, 256)));
		tab = malloc(sizeof(char *) * 3);
		tab[0] = pwd;
		tab[1] = ft_strdup("SHLV1=1");
		tab[2] = ft_strdup("_=/usr/bin/env");
		e->envp = tab;
		e->path = NULL;
	}
	e->get_pwd = 1;
	e->child_pid = 0;
	e->sh_status = 0;
}

char		**env_cpy(char **envp, size_t nb, int free_it)
{
	size_t	len;
	size_t	i;
	char	**tab;

	i = 0;
	while (envp[i])
		i++;
	if (!(tab = malloc(sizeof(char *) * (i + nb + 1))))
		return (NULL);
	tab[i] = NULL;
	i = 0;
	while (envp[i])
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	while (nb--)
	{
		tab[i] = ft_strdup("\0");
		i++;
	}
	return (tab);
}

void		free_env(char **envp)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (envp[len])
		len++;
	i = 0;
	while (i <= len)
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
}
