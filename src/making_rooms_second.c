/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_rooms_second.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem_in.h"

void	making_str(char **str, char *buf)
{
	char *res;

	res = NULL;
	if (*str == NULL)
	{
		res = ft_strdup(buf);
		*str = res;
	}
	else
	{
		res = ft_strjoin(*str, "\n");
		free(*str);
		*str = res;
		res = ft_strjoin(*str, buf);
		free(*str);
		*str = res;
	}
}

int		num_processing(char *buf)
{
	int		i;

	i = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
		i++;
	if (i < (int)ft_strlen(buf))
	{
		free(buf);
		ft_error();
	}
	else
	{
		free(buf);
		return (ft_atoi(buf));
	}
	return (0);
}

int		correct_num(char **str)
{
	size_t	i;
	char	*buf;
	int		res;

	i = 0;
	res = 0;
	buf = NULL;
	while (get_next_line(0, &buf))
	{
		making_str(str, buf);
		if (!strcmp(buf, "##start") || !strcmp(buf, "##end"))
			ft_error();
		if (strncmp(buf, "#", 1))
		{
			res = num_processing(buf);
			return (res);
		}
		free(buf);
	}
	ft_error();
	return (0);
}

void	printing_ants(int ant, char *name, int n)
{
	ft_putstr("L");
	ft_putnbr(ant);
	ft_putstr("-");
	ft_putstr(name);
	if (n == 1)
		ft_putstr(" ");
}

void	filling_links(t_room *room, char *first_link, char **str)
{
	char	*buf;
	char	**one_link;
	int		i;

	one_link = ft_strsplit(first_link, '-');
	if (find_name(room, one_link[0]) && find_name(room, one_link[1]))
		adding_link_to_room(room, one_link[0], one_link[1]);
	else
		ft_error();
	i = 0;
	while (one_link[i])
		free(one_link[i++]);
	free(one_link);
	while (get_next_line(0, &buf))
	{
		making_str(str, buf);
		if (strncmp(buf, "#", 1))
			making_links(buf, &one_link, room);
		free(buf);
	}
}
