/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:09 by cnails            #+#    #+#             */
/*   Updated: 2020/09/06 13:39:20 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void		free_links(t_lemin *data)
{
	t_link	*link;

	while (data->head_link)
	{
		link = data->head_link->next;
		free(data->head_link);
		data->head_link = link;
	}
}

void		free_rooms(t_lemin *data)
{
	t_room	*room;

	while (data->head)
	{
		room = data->head->next;
		free(data->head->name);
		free(data->head);
		data->head = room;
	}
}

int			main(int ac, char **av)
{
	t_lemin	*data;

	data = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	init(data);
	if (ac >= 2)
	{
		if (!ft_strcmp(av[1], "-p"))
			data->print_paths = true;
	}
	// TODO: validaciya - coords can be only INT
	parse_ants(data);
	bfs(data);
	delete_same_bfs(data);
	set_directions(data);
	count_inp_out(data, 1);
	while (delete_dead_links(data))
		count_inp_out(data, 0);
	inp_forks(data);
	count_paths(data);
	printf("\n");
	alg(data);
	free_rooms(data);
	free_links(data);
	free(data->paths);
	free(data);
	return (0);
}
