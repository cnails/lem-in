/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:04 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 12:57:44 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "../libft/libft.h"
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
	int					ant_id;
	int					bfs;
	bool				is_start;
	bool				is_end;
	bool				is_inter;
	size_t				input;
	size_t				output;
	bool				is_empty;
	struct s_room		*next;
	struct s_room		*head;
}				t_room;

typedef struct	s_link
{
	bool			is_used;
	bool			is_unusefull;
	int				ant_id;
	int				count_ants;
	t_room			*prev_room;
	t_room			*next_room;
	struct s_link	*next;
	int				length;
}				t_link;

typedef struct	s_lemin
{
	int		qty_links;
	t_link	*links;
	t_room	*rooms;
	t_room	*head;
	t_link	*head_link;
	t_vars	var;
	int		qty_ants;
	int		ants_in_road;
	int		qty_paths;
	int		ant_id;
	bool	print_paths;
	bool	print_errors;
	bool	print_count;
	bool	print_help;
	char	print_unknown;
	bool	print_count_ants;
	t_link	**paths;
}				t_lemin;

void			ft_parse(t_lemin *data);
void			parse_room(t_lemin *data, bool start, bool end);
void			parse_ants(t_lemin *data);
int				parse_links(t_lemin *data);
void			bfs(t_lemin *data);
void			delete_same_bfs(t_lemin *data);
void			set_directions(t_lemin *data);
void			count_inp_out(t_lemin *data, size_t nbr);
void			inp_forks(t_lemin *data);
int				delete_dead_links(t_lemin *data);
void			print_links(t_lemin *data);
void			delete_unusefull(t_lemin *data, t_link *tmp);
void			count_paths(t_lemin *data);
void			alg(t_lemin *data);
void			move_ants_from_start(t_lemin *data);
void			move_ants(t_lemin *data);
void			check_move_ants(t_lemin *data, t_link *head);
void			move_ants_dop_func(t_lemin *data);
void			print_step(t_room *room, int ant_id);
void			clear_rooms(t_lemin *data);
void			make_step(t_lemin *data, t_link *link);
t_room			*find_room(t_lemin *data, char *name);
t_link			*find_link_by_len(t_lemin *data, int len);
t_link			*find_link(t_lemin *data, t_room *room);
void			count_paths(t_lemin *data);
void			calc_len_paths(t_lemin *data);
void			add_path(t_lemin *data, t_link *link);
void			form_paths(t_lemin *data);
void			make_step(t_lemin *data, t_link *link);
int				calc_len(t_lemin *data, t_link *link);
void			clear_rooms(t_lemin *data);
void			print_step(t_room *room, int ant_id);
void			init(t_lemin *data);
void			init_room(t_room *room);
void			validate_room(t_lemin *data, t_room *room);
void			print_paths(t_lemin *data);
void			free_all(t_lemin *data);
void			flags(t_lemin *data);
bool			is_valid_int(int nbr, char *str);
int				ft_sstrlen(char **line);
int				ft_strsim(char *str1, char *str2);
void			ft_error(t_lemin *data, char *str);
void			free_split(char **split);
void			free_links(t_lemin *data);
void			free_rooms(t_lemin *data);
void			print_help();

#endif
