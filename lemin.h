/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:04 by cnails            #+#    #+#             */
/*   Updated: 2020/06/28 13:31:21 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# include <stdbool.h>
# include <limits.h>

typedef struct	s_vars
{
	bool		is_true;
	size_t		x;
	size_t		y;
	size_t		i;
	char		*line;
}				t_vars;

typedef struct	s_room
{
	bool				is_used;
	char				*name;
	size_t				x;
	size_t				y;
	int					bfs;
	bool				is_start;
	bool				is_end;
	bool				is_inter;
	size_t				input;
	size_t				output;
	bool				is_empty;
	struct s_link		**links;
	struct s_room		*next;
	struct s_room		*head;
}				t_room;

typedef struct	s_link
{
	bool			is_used;
	bool			is_unusefull;
	t_room			*prev_room;
	t_room			*next_room;
	struct s_link	*next;
	struct s_link	*prev;
}				t_link;

typedef struct	s_mod_link
{
	bool			is_used;
	bool			is_unusefull;
	t_room			**prev_room;
	t_room			**next_room;
	struct s_link	*next;
	struct s_link	*prev;
}				t_mod_link;

typedef struct	s_lemin
{
	int		qty_links;
	t_link	*links;
	t_room	*rooms;
	t_room	*head;
	t_link	*head_link;
	t_vars	var;
	int		qty_ants;
}				t_lemin;

void			ft_parse(t_lemin *data);
void			parse_room(t_lemin *data, bool start, bool end);
void			parse_ants(t_lemin *data);
int				parse_links(t_lemin *data);
void			bfs(t_lemin *data);
void			delete_same_bfs(t_lemin *data);
void			set_directions(t_lemin *data);
void			count_inp_out(t_lemin *data);
void			inp_forks(t_lemin *data);

/*
**	utils
*/

int				ft_sstrlen(char **line);
int				ft_strsim(char *str1, char *str2);
void			ft_error(char *str);
void			free_split(char **split);

#endif
