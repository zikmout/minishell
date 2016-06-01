/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 09:27:40 by ssicard           #+#    #+#             */
/*   Updated: 2016/01/26 20:54:09 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

long long	ft_count_print(int fill_me, char *c)
{
	static	int	here;
	int			tmp;

	tmp = 0;
	if (c == "stop")
	{
		tmp = here;
		here = 0;
		return (tmp);
	}
	here = here + fill_me;
	return (here);
}

size_t		ft_cslen(wchar_t wc)
{
	size_t	len2;

	len2 = 0;
	if (wc < 0x80)
		len2 = 1;
	else if (wc < 0x0800)
		len2 = 2;
	else if (wc < 0x10000)
		len2 = 3;
	else if (wc < 0x110000)
		len2 = 4;
	return (len2);
}

size_t		ft_wcslen(wchar_t *str)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (*str)
		{
			len = len + ft_cslen(*str);
			str++;
		}
	}
	return (len);
}
