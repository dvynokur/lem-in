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

#include "../header/lem_in.h"

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

int		start_end_connected(t_room *rooms, char *str)
{
	t_link	*l;
	int		i;

	i = 1;
	l = find_first_end(rooms, 1)->links;
	while (l)
	{
		if (!ft_strcmp(l->room_name, find_first_end(rooms, 2)->room_name))
		{
			ft_putstr(str);
			ft_putstr("\n\n");
			while (i <= rooms->n_ants)
			{
				ft_putstr("L");
				ft_putnbr(i);
				ft_putstr("-end ");
				i++;
			}
			ft_putstr("\n");
			return (1);
		}
		l = l->next;
	}
	return (0);
}

int		main(void)
{
	int		n_ants;
	t_room	*room;
	t_path	*path;
	char	*str;

	str = NULL;
	path = NULL;
	n_ants = correct_num(&str);
	if (n_ants == 0)
		ft_error();
	room = filling_rooms(&str);
	if (room->room_name == NULL)
		ft_error();
	room->n_ants = n_ants;
	room->max_ways = finding_max_ways(room);
	if (start_end_connected(room, str))
		exit(0);
	path = finding_path(room);
	ft_putstr(str);
	ft_putstr("\n\n");
	running_ants(room, path, n_ants);
	return (0);
}
