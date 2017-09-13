/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
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
//
//t_path	*create_path()
//{
//	t_path	*new;
//
//	new = (t_path *)malloc(sizeof(t_path));
//	new->complexity = 0;
//	new->links = NULL;
//	new->next = NULL;
//	return (new);
//}

int		if_is_start_end(t_room *room)
{
	if (!find_status(room, 1) || (!find_status(room, 2)))
		ft_error();
	return (1);
}

int		finding_max_ways(t_room *rooms)
{
	t_room	*r;
	t_link	*l;
	int		first_ways;
	int		end_ways;

	first_ways = 0;
	end_ways = 0;
	r = find_first_end(rooms, 1);
	l = r->links;
	while (l)
	{
		first_ways++;
		l = l->next;
	}
	r = find_first_end(rooms, 2);
	l = r->links;
	while (l)
	{
		end_ways++;
		l = l->next;
	}
	if (first_ways < end_ways)
		return (first_ways);
	else
		return (end_ways);
}

int		start_end_connected(t_room *rooms)
{
	t_room	*start;
	t_room	*end;
	t_link	*l;
	int		i;

	i = 1;
	start = find_first_end(rooms, 1);
	l = start->links;
	while (l)
	{
		if (!ft_strcmp(l->room_name, find_first_end(rooms, 2)->room_name))
		{
			while (i <= rooms->n_ants)
			{
				printf("L%d-end ", i);
				i++;
			}
			printf("\n");
			return (1);
		}
		l = l->next;
	}
	return (0);
}

int 	main(void)
{
	int 	n_ants;
	t_room	*room;
	t_path	*path;

	path = NULL;
	n_ants = correct_num();
	room = filling_rooms();
	room->n_ants = n_ants;
	room->max_ways = finding_max_ways(room);
	if (start_end_connected(room))
		exit (0);
	path = finding_path(room);
	
	print_ways(path);
	
	running_ants(room, path, n_ants);
	// print_rooms(room);

	return (0);
}