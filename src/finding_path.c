/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem_in.h"

t_room	*finding_less_complexity(t_link *link, t_room *rooms)
{
	t_room	*temp;
	t_room	*r;
	t_link	*l;

	r = NULL;
	temp = NULL;
	l = link;
	while (l)
	{
		r = find_room(rooms, l->room_name);
		if (r->occupied == 0 && r != find_first_end(rooms, 2)
			&& r->complexity != 0)
		{
			if (temp == NULL && r->complexity != 0)
				temp = r;
			else if (r->complexity < temp->complexity && r->complexity != 0)
				temp = r;
		}
		l = l->next;
	}
	return (temp);
}

int		filling_ways(t_room *rooms, t_room *current, t_path *path)
{
	t_link	*l;
	t_room	*temp;
	t_path	*p;

	temp = NULL;
	p = path;
	l = current->links;
	if (current == find_first_end(rooms, 2))
	{
		p->links = create_link();
		p->links->room_name = find_first_end(rooms, 2)->room_name;
	}
	temp = finding_less_complexity(l, rooms);
	if (temp)
	{
		filling_path_structure(path, temp, rooms);
		if (ft_strcmp(temp->room_name, find_first_end(rooms, 1)->room_name))
			if (!filling_ways(rooms, temp, path))
				return (0);
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
}

void	check_if_path(t_room *rooms, t_room *end)
{
	t_link	*l;
	int		flag;

	flag = 0;
	l = end->links;
	while (l)
	{
		if (find_room(rooms, l->room_name)->complexity != 0)
			flag = 1;
		l = l->next;
	}
	if (flag == 0)
		ft_error();
}

t_path	*finding_path(t_room *rooms)
{
	t_path	*path;
	t_room	*end;
	int		i;
	t_path	*p;

	i = 0;
	if (rooms->room_name == NULL)
		ft_error();
	find_first_end(rooms, 1)->complexity = 1;
	writing_complexity(rooms, 1);
	path = create_path();
	p = path;
	end = find_first_end(rooms, 2);
	check_if_path(rooms, end);
	while (i < rooms->max_ways)
	{
		if (filling_ways(rooms, end, p) && i + 1 < rooms->max_ways)
		{
			p->next = create_path();
			p = p->next;
		}
		i++;
	}
	return (path);
}
