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

#include "../header/lem-in.h"

void	adding_ants(t_room *rooms, t_link *before, t_link *current, int ant_name)
{
	t_room	*before_room;
	t_room	*current_room;

	if (current)
	{
		adding_ants(rooms, current, current->next, ant_name);
		if (before != NULL)
		{

			before_room = find_room(rooms, before->room_name);
			current_room = find_room(rooms, current->room_name);
			if (before_room->ant != 0 && current_room->ant != 0)
				current_room->ant = 0;
			if (before_room->ant != 0 && current_room->ant == 0)
			{
				current_room->ant = before_room->ant;
				before_room->ant = 0;

				printf("L%d", current_room->ant);
				printf("-%s ", current_room->room_name);
			}
		}
		else
		{
			current_room = find_room(rooms, current->room_name);
			current_room->ant = ant_name;
			printf("L%d", current_room->ant);
			printf("-%s", current_room->room_name);
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
			printf("L%d", next_room->ant);
			printf("-%s ", next_room->room_name);
		}
	}
	else
	{
		current_room = find_room(rooms, current->room_name);
		current_room->ant = 0;
	}
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
				printf("\n");
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
				printf("%s %s", RED, RESET);
			}
			else if (p->complexity >= n_ants - i + 1 && there_is_an_ant(rooms, p))
				moving_rest_ants(rooms, p->links, p->links->next);
			p = p->next;
		}
		printf("\n");
	}
	last_movement(rooms, path);
}