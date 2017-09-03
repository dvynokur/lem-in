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
		if (temp->complexity == 0)
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
		if (flag == -1)
			return ;
		if (p->next == NULL)
		{
			p = rooms;
			i++;
			flag = -1;
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

void	filling_ways(t_room *rooms, t_room *current, t_path *path)
{
	t_link	*l;
	t_room	*r;
	t_room	*temp;

	r = NULL;
	temp = NULL;
	l = current->links;
	while (l)
	{
		r = find_room(rooms, l->room_name);
		if (r->occupied == 0)
		{
			if (temp == NULL && r->complexity != 0)
				temp = r;
			else
				if (r->complexity < temp->complexity && r->complexity != 0)
					temp = r;
		}
		l = l->next;
	}
	filling_path_structure(path, temp);
	if (ft_strcmp(temp->room_name, find_first_end(rooms, 1)->room_name))
		filling_ways(rooms, temp, path);
}

void	filling_path_structure(t_path *path, t_room *current)
{
	t_link *new;

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

void	print_ways(t_path *path)
{
	// t_path	*p;

	// p = path;
	// while (p)
	// {
	// 	printf("path complexity: %d\n", p->complexity);

	// }
	t_link	*l;

	l = path->links;
	printf("%spath: ", CYAN);
	while (l)
	{
		printf("%s ", l->room_name);
		l = l->next;
	}
	printf("\n%s", RESET);
}

t_path	*finding_path(t_room *rooms)
{
	t_room	*first;
	t_path	*path;
	t_room	*end;

	if (rooms->room_name == NULL)
		ft_error();

	first = find_first_end(rooms, 1);
	first->complexity = 1;
	writing_complexity(rooms, 1);
	print_rooms(rooms);

	path = create_path();
	end = find_first_end(rooms, 2);
	filling_ways(rooms, end, path);

	print_ways(path);

	return (0);
}