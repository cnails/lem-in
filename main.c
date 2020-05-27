/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:09 by cnails            #+#    #+#             */
/*   Updated: 2020/05/25 13:31:56 by cnails           ###   ########.fr       */
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
}

void		free_links(t_lemin *data)
{
	int i = 0;
	t_link *link;

	while (data->head_link)
	{
		i++;
		link = data->head_link->next;
		free(data->head_link);
		data->head_link = link;
	}
	printf("%d links have been cleaned\n", i);
}

void		free_rooms(t_lemin *data)
{
	int i = 0;
	t_room *room;

	while (data->head)
	{
		i++;
		room = data->head->next;
		free(data->head->name);
		free(data->head);
		data->head = room;
	}
	printf("%d rooms have been cleaned\n", i);
}

int			main(int ac, char **av)
{
	t_lemin	*data;

	data = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	init(data);
	parse_ants(data);
	bfs(data);
	free_rooms(data);
	printf("\n");
	free_links(data);
	free(data);
	return (0);
}