/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 22:59:08 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/02 14:49:14 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(void)
{
	t_filler	f;

	ft_bzero(&f, sizeof(t_filler));
	if (!get_player(&f))
		return (0);
	while (1)
	{
		f.min_score = 9999;
		if (!get_board(&f))
			return (-1);
		//ft_printf("3 3\n");
		//return (0);
	}
	return (0);
}
