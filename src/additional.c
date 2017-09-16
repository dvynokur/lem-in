/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem-in.h"

t_room	*create_room(void)
{
	t_room *room;

	room = (t_room *)malloc(sizeof(t_room));
	room->room_name = NULL;
	room->x = -1;
	room->y = -1;
	room->ant = 0;
	room->complexity = 0;
	room->status = 0;
	room->max_ways = 0;
	room->occupied = 0;
	room->n_ants = 0;
	room->next = NULL;
	room->links = NULL;
	return (room);
}

void	ft_error()
{
	ft_putstr("ERROR\n");
	while (1);
	exit (0);
}

t_link	*create_link(void)
{
	t_link	*new;

	new = (t_link *)malloc(sizeof(t_link));
	new->room_name = NULL;
	new->next = NULL;
	return (new);
}

int 	status_check(char *buf, int status, t_room *room)
{
	if (status != 0 && (!ft_strcmp(buf, "##start") || !ft_strcmp(buf, "##end")))
		ft_error();
	if (!strcmp(buf, "##start"))
	{
		if (find_status(room, 1))
			ft_error();
		status = 1;
	}
	else if (!strcmp(buf, "##end"))
	{

		if (find_status(room, 2))
			ft_error();
		status = 2;
	}
	return (status);
}

int		there_is_an_ant(t_room *rooms, t_path *path)
{
	t_link	*l;

	l = path->links;
	while (l)
	{
		if (find_room(rooms, l->room_name)->ant != 0)
			return (1);
		l = l->next;
	}
	return (0);
}
