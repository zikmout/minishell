/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:25:10 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/20 10:20:34 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sh1.h"

int			sh_status(char *cmd, t_env *e)
{
	if (e->sh_status == 0)
	{
		e->sh_status = 1;
		ft_printf("status: status on\n");
	}
	else
	{
		e->sh_status = 0;
		ft_printf("status: status off\n");
	}
	return (0);
}

int			sh_help(char *cmd, t_env *e)
{
	ft_printf("sh1: -help\n");
	ft_printf("Implemented built-in:\n");
	ft_printf("      -exit: to exit the shell\n");
	ft_printf("      -help: recap of the built-in\n");
	ft_printf("      -setenv: set a new environment variable\n");
	ft_printf("      -unsetenv: unset an environment variable\n");
	ft_printf("      -env: modifies the environment\n");
	ft_printf("      -sh_status: adds information about pid execution\n");
	return (0);
}

int			sh_exit(char *cmd, t_env *e)
{
	ft_printf("Shell exit: success.\n");
	exit(0);
}
