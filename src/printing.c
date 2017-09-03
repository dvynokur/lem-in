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

#include "../header/lem-in.h"

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
			print_links(p->links);
			p = p->next;
		}
	}
	printf("%s=====================================================================%s\n", RED, RESET);
}
