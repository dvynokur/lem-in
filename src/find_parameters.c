/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem_in.h"

int		find_status(t_room *room, int status)
{
	t_room *p;

	p = room;
	while (p)
	{
		if (p->status == status)
			return (1);
		p = p->next;
	}
	return (0);
}

int		find_name(t_room *room, char *name)
{
	t_room	*p;
	int		flag;

	p = room;
	flag = 0;
	while (p)
	{
		if (p->room_name != NULL && !ft_strcmp(p->room_name, name))
		{
			return (1);
		}
		p = p->next;
	}
	return (0);
}

int		find_coord(t_room *room, int x, int y)
{
	t_room *p;

	p = room;
	while (p)
	{
		if (p->x == x && p->y == y)
			return (1);
		p = p->next;
	}
	return (0);
}

int		find_link(t_link *l, char *name)
{
	t_link	*p;

	p = l;
	if (p->room_name == NULL)
		return (1);
	else
	{
		while (p)
		{
			if (!ft_strcmp(p->room_name, name))
				return (0);
			p = p->next;
		}
	}
	return (1);
}
