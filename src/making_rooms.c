/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem-in.h"

t_room	*filling_rooms()
{
	t_room	*room;
	t_room	*temp;
	char 	*buf;
	char 	**room_split;
	int 	status;

	buf = NULL;
	room = create_room();
	temp = room;
	status = 0;
	
	while (get_next_line(0, &buf))
	{
		if (!(buf[0] == '#' && buf[1] != '#'))
		{
			if (check_if_link(buf) && if_is_start_end(temp))
			{
				filling_links(temp, buf);
				return (temp);
			}
			if (!ft_strncmp(buf, "##", 2))
			{
				status = status_check(buf, status, temp);
			}
			else if (strncmp(buf, "#", 1) && if_correct_room(buf))
			{
				room_split = ft_strsplit(buf, ' ');
				if (find_coord(temp, ft_atoi(room_split[1]), ft_atoi(room_split[2])) || find_name(temp, room_split[0]))
				{
					ft_error();
				}
				room->room_name = room_split[0];
				room->x = ft_atoi(room_split[1]);
				room->y = ft_atoi(room_split[2]);
				room->next = create_room();
				room->status = status;
				room = room->next;
				status = 0;
			}

		}
	}
	return (temp);
}

int		if_correct_room(char *buf)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_strlen(buf))
	{
		if (buf[i] == ' ')
			count++;
		i++;
	}
	if ((count != 2) || (buf[0] == ' ' || buf[ft_strlen(buf)] == ' ') ||
		buf[0] == 'L' || buf[0] == '#')
	{

		ft_error();
	}
	check_coords(buf);
	return (1);
}

void	check_coords(char *buf)
{
	char	**str;
	size_t	i;

	i = 0;
	str = ft_strsplit(buf, ' ');
	if (str[0] == NULL || str[1] == NULL || str[2] == NULL)
		ft_error();
	while (i < ft_strlen(str[1]))
	{
		if (!ft_isdigit(str[1][i]))
			ft_error();
		i++;
	}
	i = 0;
	while (i < ft_strlen(str[2]))
	{
		if (!ft_isdigit(str[2][i]))
			ft_error();
		i++;
	}
}

int 	status_check(char *buf, int status, t_room *room)
{
	if (status != 0)
		ft_error();
	if (!strcmp(buf, "##start"))
	{
		if (find_status(room, 1))
			ft_error();
		status = 1;
	}
	else if (!strcmp(buf, "##end"))
	{

		if (find_status(room, 2))
			ft_error();
		status = 2;
	}
	return (status);
}

int		correct_num(void)
{
	size_t	i;
	char	*buf;

	i = 0;
	buf = NULL;

	while (get_next_line(0, &buf))
	{
		if (!strcmp(buf, "##start") || !strcmp(buf, "##end"))
			ft_error();
		if (strncmp(buf, "#", 1))
		{
			while (buf[i] >= '0' && buf[i] <= '9')
				i++;
			if (i < ft_strlen(buf))
			{
				ft_putstr("ERROR\n");
				exit(0);
			}
			else
				return (ft_atoi(buf));
		}
	}
	ft_error();
	return (0);
}
