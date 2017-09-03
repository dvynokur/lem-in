/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem-in.h"

void	add_last_link(t_link *links, char *last_link)
{
	t_link			*p;
	unsigned long	i;

	i = 0;
	p = links;
	if (find_link(links, last_link))
	{
		if (p->room_name != NULL) {
			while (p->next != NULL)
				p = p->next;
			p->next = create_link();
			p = p->next;
		}
		p->room_name = malloc(sizeof(char) * (ft_strlen(last_link)) + 1);
		while (i < ft_strlen(last_link) + 1)
		{
			p->room_name[i] = last_link[i];
			i++;
		}
		p->room_name[ft_strlen(last_link) + 1] = '\0';
	}
}

void	adding_link_to_room(t_room *room, char *first_link, char *second_link)
{
	t_room	*temp;

	temp = room;
	while (temp->next != NULL)
	{
		if (!ft_strcmp(temp->room_name, first_link))
		{
			if (temp->links == NULL)
				temp->links = create_link();
			add_last_link(temp->links, second_link);
		}
		if (!ft_strcmp(temp->room_name, second_link))
		{
			if (temp->links == NULL)
				temp->links = create_link();
			add_last_link(temp->links, first_link);
		}
		temp = temp->next;
	}
}

void	filling_links(t_room *room, char *first_link)
{
	char 	*buf;
	char 	**one_link;

	one_link = ft_strsplit(first_link, '-');
	if (find_name(room, one_link[0]) && find_name(room, one_link[1]))
		adding_link_to_room(room, one_link[0], one_link[1]);
	else
		ft_error();
	while (get_next_line(0, &buf))
		if (strncmp(buf, "#", 1))
		{
			if (check_if_link(buf))
			{
				one_link = ft_strsplit(buf, '-');
				if (find_name(room, one_link[0]) && find_name(room, one_link[1]))
					adding_link_to_room(room, one_link[0], one_link[1]);
				else
					ft_error();
			}
			else
				ft_error();
	}
}

int		check_if_link(char *s)
{
	size_t	i;
	int		count;
	int		space;
	char 	**temp;

	i = 0;
	count = 0;
	space = 0;

	while (i < ft_strlen(s))
	{
		if (s[i] == '-')
			count++;
		if (s[i] == ' ')
			space++;
		i++;
	}
	if (count == 1 && ft_strlen(s) >= 3 && s[0] != '-' &&
		s[ft_strlen(s)] != '-' && space == 0)
	{
		temp = ft_strsplit(s, '-');
		if (temp[0][0] != 'L' || temp[1][0] != 'L' ||
			temp[0][0] != '#' || temp[1][0] != '#')
			return (1);
	}
	return (0);
}