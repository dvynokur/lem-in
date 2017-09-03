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

	// r1 = NULL;
	if (current)
	{
		adding_ants(rooms, current, current->next, ant_name);
		if (before != NULL)
		{
			before_room = find_room(rooms, before->room_name);
			current_room = find_room(rooms, current->room_name);
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

void	running_ants(t_room *rooms, t_path *path, int n_ants)
{
	int		i;
	t_path	*p;

	i = 1;
	p = path;
	n_ants = 20;
	while (i <= n_ants)
	{
		p = path;
		while (p)
		{
			adding_ants(rooms, NULL, p->links, i);
			printf("\n");
			p = p->next;
			i++;

		}
		// prining_ants(path);
	}
}