/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvynokur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:49:51 by dvynokur          #+#    #+#             */
/*   Updated: 2017/08/20 16:49:52 by dvynokur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define BLACK   "\x1b[37m"
# define RESET   "\x1b[0m"
# include <stdio.h>
# include "../libft/libft.h"
# include <stdlib.h>

typedef struct		s_link
{
	char 			*room_name;
	struct s_link	*next;
}					t_link;

typedef struct		s_room
{
	char 			*room_name;
	int 			x;
	int 			y;
	int 			ant;
	int 			complexity;
	int 			status;
	int				max_ways;
	int				occupied;
	int				n_ants
	struct s_room	*next;
	t_link			*links;
}					t_room;

typedef struct		s_path
{
	int 			complexity;
	int				ants;
	t_link			*links;
	struct s_path	*next;
}					t_path;

//============================ Error management ==========================

// Additional
void			ft_error();
t_room			*create_room(void);
t_link			*create_link(void);
int				if_is_start_end(t_room *room);

//Find parameters
int 			find_status(t_room *room, int status);
int 			find_name(t_room *room, char *name);
int				find_coord(t_room *room, int x, int y);
int				find_link(t_link *l, char *name);

//Links
int				check_if_link(char *s);
void			filling_links(t_room *room, char *first_link);
void			adding_link_to_room(t_room *room, char *first_link, char *second_link);
void			add_last_link(t_link *links, char *last_link);

//Rooms
t_room			*filling_rooms();
int				if_correct_room(char *buf);
void			check_coords(char *buf);
int 			status_check(char *buf, int status, t_room *room);

//Number of Ants
int				correct_num(void);

//=============================== Printing =============================
// Printing
void			print_links(t_link *l);
void 			print_rooms(t_room *room);
void			print_ways(t_path *path);


//=============================== Finding path =========================
t_room			*find_first_end(t_room *rooms, int status);
t_room			*find_room(t_room *rooms, char *name);
void			writing_complexity(t_room *rooms, int i);
void			filling_complexity(t_room *rooms, t_room *current, int i);
t_path			*create_path();
t_path			*finding_path(t_room *rooms);
int				filling_ways(t_room *rooms, t_room *current, t_path *path);
t_room			*find_first_end(t_room *rooms, int status);
void			filling_path_structure(t_path *path, t_room *current, t_room *rooms);

//=============================== Running ants =========================
void			running_ants(t_room *rooms, t_path *path, int n_ants);


#endif
