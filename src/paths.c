/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 13:19:19 by cnails            #+#    #+#             */
/*   Updated: 2020/10/03 13:01:13 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	make_step(t_lemin *data, t_link *link)
{
	if (!link->next_room->is_end)
	{
		link->next_room->ant_id = data->ant_id;
		data->ants_in_road++;
	}
	data->ant_id++;
	data->qty_ants--;
	if (!link->next_room->is_end)
		print_step(link->next_room, link->next_room->ant_id);
	else
		print_step(link->next_room, data->ant_id - 1);
}

void	form_paths(t_lemin *data)
{
	t_link	*head;
	int		min;
	int		i;

	i = 0;
	while (i < data->qty_paths)
	{
		head = data->head_link;
		min = 999999;
		while (head)
		{
			if (head->length && head->is_used == false)
			{
				if (head->length < min)
					min = head->length;
			}
			head = head->next;
		}
		add_path(data, find_link_by_len(data, min));
		i++;
	}
}

void	add_path(t_lemin *data, t_link *link)
{
	t_link		**paths;
	int			i;

	i = 0;
	paths = data->paths;
	while (paths[i])
		i++;
	paths[i] = link;
}

void	calc_len_paths(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	data->var.y = 0;
	while ((int)data->var.y < data->qty_paths)
	{
		if (head->prev_room->is_start)
		{
			head->is_used = false;
			head->length = calc_len(data, head);
			data->var.y++;
		}
		head = head->next;
	}
}

void	count_paths(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->prev_room->is_start)
			data->qty_paths++;
		head = head->next;
	}
	data->paths = (t_link **)ft_memalloc(sizeof(t_link *) * data->qty_paths);
}
