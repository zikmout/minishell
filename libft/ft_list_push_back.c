/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanet <tmanet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 14:24:23 by tmanet            #+#    #+#             */
/*   Updated: 2016/03/25 14:09:34 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_back(t_list **alst, t_list *new)
{
	t_list	*elem;

	if (alst && new)
	{
		elem = *alst;
		if (elem)
		{
			while (elem->next)
				elem = elem->next;
			elem->next = new;
		}
		else
			*alst = new;
	}
}
