/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:09 by cnails            #+#    #+#             */
/*   Updated: 2020/08/17 22:22:55 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

static void	init(t_lemin *data)
{
	data->rooms = NULL;
	data->qty_ants = 0;
	data->qty_links = 0;
	data->head_link = NULL;
	data->head = NULL;
	data->links = NULL;
	data->ants_in_road = 0;
	data->qty_paths = 0;
	data->ant_id = 1;
}

void		free_links(t_lemin *data)
{
	int		i = 0;
	t_link	*link;

	while (data->head_link)
	{
		i++;
		link = data->head_link->next;
		free(data->head_link);
		data->head_link = link;
	}
	// printf("%d links have been cleaned\n", i);
}

void		free_rooms(t_lemin *data)
{
	int		i = 0;
	t_room	*room;

	while (data->head)
	{
		i++;
		room = data->head->next;
		free(data->head->name);
		free(data->head);
		data->head = room;
	}
	// printf("%d rooms have been cleaned\n", i);
}

int			main(int ac, char **av)
{
	t_lemin	*data;
	size_t one = 1;
	size_t zero = 0;

	data = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	init(data);
	parse_ants(data);
	bfs(data);
	delete_same_bfs(data);
	set_directions(data);
	count_inp_out(data, one);
	while (delete_dead_links(data))
		count_inp_out(data, zero);
	inp_forks(data);
	print_links(data);
	count_paths(data);
	printf("\n");
	alg(data);
	free_rooms(data);
	free_links(data);
	free(data->paths);
	free(data);
	return (0);
}
