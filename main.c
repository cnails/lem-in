/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:09 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 13:13:59 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_error(t_lemin *data, char *str)
{
	if (data->print_errors)
	{
		printf("Error: %s\n", str);
	}
	else
		printf("Error\n");
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

void		parse_flags(t_lemin *data, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'e')
			data->print_errors = true;
		else if (str[i] == 'p')
			data->print_paths = true;
		else if (str[i] == 'c')
			data->print_count = true;
		else if (str[i] == 'c')
			data->print_count = true;
		else if (str[i] == 'h')
			data->print_count = true;
		i++;
	}
}

int			main(int ac, char **av)
{
	t_lemin	*data;

	data = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	init(data);
	if (ac >= 2)
	{
		if (av[1][0] == '-')
			parse_flags(data, av[1]);
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
