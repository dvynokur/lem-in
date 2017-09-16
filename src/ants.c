/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem_in.h"

void	adding_ants(t_room *r, t_link *b, t_link *c, int ant_name)
{
	t_room	*current_room;

	if (c)
	{
		adding_ants(r, c, c->next, ant_name);
		if (b != NULL)
		{
			current_room = find_room(r, c->room_name);
			if (find_room(r, b->room_name)->ant != 0 && current_room->ant != 0)
				current_room->ant = 0;
			if (find_room(r, b->room_name)->ant != 0 && current_room->ant == 0)
			{
				current_room->ant = find_room(r, b->room_name)->ant;
				find_room(r, b->room_name)->ant = 0;
				printing_ants(current_room->ant, current_room->room_name, 1);
			}
		}
		else
		{
			current_room = find_room(r, c->room_name);
			current_room->ant = ant_name;
			printing_ants(current_room->ant, current_room->room_name, 0);
		}
	}
}

int		is_there_ants(t_room *rooms, t_path *path)
{
	t_path	*p;
	t_link	*l;

	p = path;
	while (p)
	{
		l = p->links;
		while (l)
		{
			if (find_room(rooms, l->room_name)->ant != 0)
				return (1);
			l = l->next;
		}
		p = p->next;
	}
	return (0);
}

void	moving_rest_ants(t_room *rooms, t_link *current, t_link *next)
{
	t_room	*next_room;
	t_room	*current_room;

	if (next)
	{
		moving_rest_ants(rooms, current->next, next->next);
		next_room = find_room(rooms, next->room_name);
		current_room = find_room(rooms, current->room_name);
		if (next_room == find_first_end(rooms, 2))
			next_room->ant = 0;
		if (current_room->ant != 0)
		{
			next_room->ant = current_room->ant;
			current_room->ant = 0;
			printing_ants(current_room->ant, current->room_name, 1);
		}
	}
	else
	{
		current_room = find_room(rooms, current->room_name);
		current_room->ant = 0;
	}
}

void	last_movement(t_room *rooms, t_path *path)
{
	t_path	*p;

	while (is_there_ants(rooms, path))
	{
		p = path;
		while (p)
		{
			moving_rest_ants(rooms, p->links, p->links->next);
			if (there_is_an_ant(rooms, p))
				ft_putstr("\n");
			p = p->next;
		}
	}
}

void	running_ants(t_room *rooms, t_path *path, int n_ants)
{
	int		i;
	t_path	*p;

	i = 1;
	p = path;
	while (i <= n_ants)
	{
		p = path;
		while (p && i <= n_ants)
		{
			if (p == path || p->complexity < n_ants - i + 1)
			{
				adding_ants(rooms, NULL, p->links, i);
				i++;
				ft_putstr(" ");
			}
			else if (p->complexity >= n_ants - i + 1 &&
				there_is_an_ant(rooms, p))
				moving_rest_ants(rooms, p->links, p->links->next);
			p = p->next;
		}
		ft_putstr("\n");
	}
	last_movement(rooms, path);
}
