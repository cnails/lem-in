/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 16:43:51 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 13:11:39 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_paths(t_lemin *data)
{
	t_link	**paths;
	t_link	*head;
	int		i;

	i = 0;
	paths = data->paths;
	while (i < data->qty_paths)
	{
		printf("\n");
		head = paths[i];
		if (head->length)
			while (head)
			{
				printf("\033[1;36m%s", head->prev_room->name);
				if (head->next_room->is_end)
					printf("\033[0;35m->\033[1;36m%s", head->next_room->name);
				head = find_link(data, head->next_room);
				if (head)
				{
					printf("\033[0;35m->");
				}
			}
		i++;
	}
	printf("\033[0m\n");
}

void	validate_room(t_lemin *data, t_room *room)
{
	t_room *head;

	head = data->head;
	while (head)
	{
		if ((head->x == room->x && head->y == room->y) ||\
			((ft_strlen(head->name) == ft_strlen(room->name))\
				&& !ft_strcmp(head->name, room->name)))
			ft_error(data, "coordinates of the rooms are the same");
		head = head->next;
	}
}

int		ft_sstlen(char **line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int		ft_strsim(char *str1, char *str2)
{
	return ((ft_strlen(str1) == ft_strlen(str2))\
	&& !ft_strcmp(str1, str2));
}

void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
