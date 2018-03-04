/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 16:31:13 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 00:12:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_dot		*ft_dotlstcreate(int x, int y)
{
	t_dot	*t;

	if ((t = (t_dot*)malloc(sizeof(t_dot))) == NULL)
		return (NULL);
	t->x = x;
	t->y = y;
	t->next = NULL;
	return (t);
}

void		ft_dotlstpushback(t_dot **begin_list, int x, int y)
{
	t_dot	*tmp;

	if (!begin_list)
		return ;
	if (*begin_list)
	{
		tmp = *begin_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_dotlstcreate(x, y);
	}
	else
		*begin_list = ft_dotlstcreate(x, y);
}

void		ft_dotlstpushfront(t_dot **begin_list, int x, int y)
{
	t_dot	*t;

	if (!begin_list)
		return ;
	if (*begin_list)
	{
		t = ft_dotlstcreate(x, y);
		t->next = (*begin_list);
		(*begin_list) = t;
	}
	else
	{
		t = ft_dotlstcreate(x, y);
		(*begin_list) = t;
	}
}

void		ft_dotlstdel(t_dot **alst)
{
	t_dot	*tmp;

	if (!alst)
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		free(*alst);
		*alst = NULL;
		*alst = tmp;
	}
}
