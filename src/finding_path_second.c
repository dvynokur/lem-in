/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_path_second.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem-in.h"

t_room	*find_room(t_room *rooms, char *name)
{
	t_room	*p;

	p = rooms;
	while (p)
	{
		if (!ft_strcmp(p->room_name, name))
			return (p);
		p = p->next;
	}
	return (0);
}

t_room	*find_first_end(t_room *rooms, int status)
{
	t_room	*p;

	p = rooms;
	while (p)
	{
		if (p->status == status)
		{
			return (p);
		}
		p = p->next;
	}
	return (0);
}

void	filling_complexity(t_room *rooms, t_room *current, int i)
{
	t_link	*l;
	t_room	*temp;

	l = current->links;
	while (l)
	{
		temp = find_room(rooms, l->room_name);
		if (temp->complexity == 0 &&
			ft_strcmp(temp->room_name, find_first_end(rooms, 2)->room_name))
		{
			temp->complexity = i;
		}
		l = l->next;
	}
}

void	writing_complexity(t_room *rooms, int i)
{
	t_room	*p;
	int		flag;

	flag = 0;
	p = rooms;
	while (p)
	{
		if (p->next == NULL)
		{
			if (flag == -1)
				return ;
			p = rooms;
			flag = -1;
			i++;
		}
		if (p->complexity == i)
		{
			filling_complexity(rooms, p, i + 1);
			flag = 1;
		}
		p = p->next;
	}
}

t_path	*create_path(void)
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->complexity = 0;
	new->ants = 0;
	new->links = NULL;
	new->next = NULL;
	return (new);
}
