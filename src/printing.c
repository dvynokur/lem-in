/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem_in.h"

void	print_links(t_link *l)
{
	t_link	*p;

	p = l;
	if (l == NULL) {
		printf("links: none\n");
		return ;
	}
	printf("links: ");
	if (p->next == NULL)
	{
		printf("[%s]", p->room_name);
	}
	else
	{
		while (p->next->next != NULL)
		{
			printf("[%s]-", p->room_name);
			p = p->next;
		}
		printf("[%s]-", p->room_name);
		p = p->next;
		printf("[%s]", p->room_name);

	}
	printf("\n");
}



void	print_ways(t_path *path)
{
	t_path	*p;
	t_link	*l;

	p = path;
	l = path->links;

	while (p)
	{
		printf("%spath complexity: %d\n", CYAN, p->complexity);
		l = p->links;
		while (l)
		{
			printf("%s ", l->room_name);
			l = l->next;
		}
		printf("\n");
		p = p->next;
	}
	printf("%s", RESET);
}

void 	print_rooms(t_room *room)
{
	t_room	*p;

	p = room;

//	printf("status in print_rooms: %d\n", room->status);

	if (room->next == NULL)
	{
		printf("%s=====================================================================%s\n", RED, RESET);
		printf("name: %s\n", p->room_name);
		printf("x: %d\n", p->x);
		printf("y: %d\n", p->y);
		printf("status: %d\n", p->status);
		printf("complexity: %d\n", p->complexity);
		printf("max_ways: %d\n", p->max_ways);
		printf("occupied: %d\n", p->occupied);
		printf("ant: %d\n", p->ant);
		print_links(p->links);
		printf("%s=====================================================================%s\n", RED, RESET);
	}
	else
	{
		while (p->next != NULL)
		{
			printf("%s=====================================================================%s\n", RED, RESET);
			printf("name: %s\n", p->room_name);
			printf("x: %d\n", p->x);
			printf("y: %d\n", p->y);
			printf("status: %d\n", p->status);
			printf("complexity: %d\n", p->complexity);
			printf("max_ways: %d\n", p->max_ways);
			printf("occupied: %d\n", p->occupied);
			print_links(p->links);
			printf("ant: %d\n", p->ant);
			p = p->next;
		}
	}
	printf("%s=====================================================================%s\n", RED, RESET);
}
