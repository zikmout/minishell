/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 09:37:15 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/31 11:57:58 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sh1.h"

char		*get_var_env(t_env *e, char *var)
{
	char	*value;
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (e->envp[i])
	{
		if (ft_strncmp(e->envp[i], var, len) == 0)
		{
			value = ft_strsub(e->envp[i], len + 1, ft_strlen(e->envp[i]) - len);
			break ;
		}
		i++;
	}
	return (value);
}

int			check_exist(t_env *e, char *var_name)
{
	size_t	i;
	int		exist;
	size_t	len;

	len = ft_strlen(var_name);
	exist = 0;
	i = 0;
	while (e->envp[i])
	{
		if (ft_strncmp(e->envp[i], var_name, len) == 0)
		{
			free(e->envp[i]);
			e->envp[i] = ft_strdup("TO_UNSET");
			exist = 1;
		}
		i++;
	}
	if (exist)
		return (i);
	else
		return (0);
}

int			unset_var_env(char *var_name, t_env *e)
{
	size_t	j;
	char	**new_env;
	int		i;

	i = 0;
	if (var_name != NULL && (i = check_exist(e, var_name)))
	{
		if (!(new_env = malloc(sizeof(char *) * (i + 1))))
			return (0);
		new_env[i + 1] = NULL;
		i = 0;
		j = 0;
		while (e->envp[i + j])
		{
			if (ft_strcmp(e->envp[i], "TO_UNSET") == 0)
				j = 1;
			new_env[i] = ft_strdup(e->envp[i + j]);
			i++;
		}
		e->envp = new_env;
	}
	else
		return (0);
	return (1);
}

int			check_var_env(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(ft_strchr(LABEL, str[i])))
		{
			ft_printf("Wrong format, you can only use: %s\n", LABEL);
			return (1);
		}
		i++;
	}
	return (0);
}

void		set_var_env(char *var_name, char *value, t_env *e)
{
	int		i;
	size_t	len;
	char	*new_env_line;
	int		exist;

	exist = 0;
	new_env_line = ft_strjoin(var_name, "=");
	new_env_line = ft_strjoin(new_env_line, value);
	len = ft_strlen(var_name);
	i = -1;
	while (e->envp[++i])
	{
		if (ft_strncmp(e->envp[i], var_name, len) == 0)
		{
			exist = 1;
			break ;
		}
	}
	if (exist == 1)
		e->envp[i] = new_env_line;
	else
	{
		e->envp = env_cpy(e->envp, 1, 1);
		e->envp[i] = new_env_line;
	}
}
