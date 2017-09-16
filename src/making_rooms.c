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

#include "../header/lem_in.h"

t_room	*adding_information(char *buf, t_room *temp, int *n, t_room *room)
{
	char	**room_split;
	int		status;
	int		i;

	i = -1;
	status = *(n);
	room_split = ft_strsplit(buf, ' ');
	if (find_coord(temp, ft_atoi(room_split[1]), ft_atoi(room_split[2]))
		|| find_name(temp, room_split[0]))
		ft_error();
	room->room_name = ft_strdup(room_split[0]);
	room->x = ft_atoi(room_split[1]);
	room->y = ft_atoi(room_split[2]);
	room->next = create_room();
	room->status = status;
	room = room->next;
	*(n) = 0;
	while (room_split[++i])
		free(room_split[i]);
	free(room_split);
	return (room);
}

int		links_processing(char **buf, t_room *temp, char **str)
{
	if (check_if_link(*buf) && if_is_start_end(temp))
	{
		filling_links(temp, *buf, str);
		free(*buf);
		return (1);
	}
	return (0);
}

t_room	*filling_rooms(char **str)
{
	t_room	*room;
	t_room	*temp;
	char	*buf;
	int		status;

	buf = NULL;
	room = create_room();
	temp = room;
	status = 0;
	while (get_next_line(0, &buf))
	{
		making_str(str, buf);
		if (!(buf[0] == '#' && buf[1] != '#'))
		{
			if (links_processing(&buf, temp, str))
				return (temp);
			if (!ft_strncmp(buf, "##", 2))
				status = status_check(buf, status, temp);
			else if (strncmp(buf, "#", 1) && if_correct_room(buf))
				room = adding_information(buf, temp, &status, room);
		}
		free(buf);
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
		ft_error();
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
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
