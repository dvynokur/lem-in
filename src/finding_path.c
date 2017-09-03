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
		if (temp->complexity == 0 && ft_strcmp(temp->room_name, find_first_end(rooms, 2)->room_name))
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

t_path	*create_path()
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->complexity = 0;
	new->ants = 0;
	new->links = NULL;
	new->next = NULL;
	return (new);
}

int		filling_ways(t_room *rooms, t_room *current, t_path *path)
{
	t_link	*l;
	t_room	*r;
	t_room	*temp;
	t_path	*p;

	r = NULL;
	temp = NULL;
	p = path;
	l = current->links;
	while (l)
	{
		// printf("l->room : %10s\n", l->room_name);
		r = find_room(rooms, l->room_name);
		if (r->occupied == 0 && r != find_first_end(rooms, 2))
		{
			if (temp == NULL && r->complexity != 0)
				temp = r;
			else
				if (r->complexity < temp->complexity && r->complexity != 0)
					temp = r;
		}
		l = l->next;
	}
	if (temp)
	{
		filling_path_structure(path, temp, rooms);
		if (ft_strcmp(temp->room_name, find_first_end(rooms, 1)->room_name))
		{
			if (!filling_ways(rooms, temp, path))
			{
				return (0);
			}
		}
	}
	else
		return (0);
	return (1);
}

void	filling_path_structure(t_path *path, t_room *current, t_room *rooms)
{
	t_link *new;

	if (ft_strcmp(current->room_name, find_first_end(rooms, 1)->room_name))
	{
		current->occupied = 1;
	}
	if (path->complexity == 0)
		path->complexity = current->complexity;
	if (path->links == NULL)
	{
		path->links = create_link();
		path->links->room_name = current->room_name;
	}
	else
	{
		new = create_link();
		new->next = path->links;
		path->links = new;
		new->room_name = current->room_name;
	}
}

t_path	*finding_path(t_room *rooms)
{
	t_room	*first;
	t_path	*path;
	t_room	*end;
	int		i;
	t_path	*p;

	i = 0;
	if (rooms->room_name == NULL)
		ft_error();

	first = find_first_end(rooms, 1);
	first->complexity = 1;
	writing_complexity(rooms, 1);

	path = create_path();
	p = path;
	end = find_first_end(rooms, 2);
	while (i < rooms->max_ways)
	{
		if (filling_ways(rooms, end, p) && i + 1 < rooms->max_ways)
		{
			p->next = create_path();
			p = p->next;
		}
		i++;
	}
	// print_rooms(rooms);


	return (path);
}