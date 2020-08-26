/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:22:36 by cnails            #+#    #+#             */
/*   Updated: 2020/08/26 18:07:32 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_link	*find_link(t_lemin *data, t_room *room)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->prev_room == room)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	clear_rooms(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		head->next_room->is_used = false;
		head->prev_room->is_used = false;
		head = head->next;
	}
}

void	move_ants(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->prev_room->ant_id && !head->length && !head->prev_room->is_used)
		{
			if (!head->ant_id)
			{
				if (head->next_room->ant_id)
				{
					head->ant_id = head->prev_room->ant_id;
					print_step(data, head->next_room, head->prev_room->ant_id, 1);
					head->prev_room->ant_id = 0;

				if (head->next_room->is_end)
					data->ants_in_road--;
				}
			}
			if (!head->next_room->ant_id)
			{
				if (!head->next_room->is_end)
				head->next_room->ant_id = head->prev_room->ant_id;
					head->next_room->is_used = true;
					print_step(data, head->next_room, head->prev_room->ant_id, 1);
				head->prev_room->ant_id = 0;
				if (head->next_room->is_end)
					data->ants_in_road--;
			}
		}
		head = head->next;
	}
	head = data->head_link;
	while (head)
	{
		if (head->ant_id && !head->next_room->ant_id)
		{
			head->next_room->ant_id = head->ant_id;
			head->ant_id = 0;
		}
		head = head->next;
	}
}

void	print_step(t_lemin *data, t_room *room, int ant_id, bool debug)
{
	printf("L%d-%s ", ant_id, room->name);
}

int		count_sum(t_lemin *data, t_link *link)
{
	t_link	**head;
	int		sum;
	int		i;

	sum = 0;
	i = 0;
	head = data->paths;
	while (head[i] != link)
	{
		sum += head[i]->length - link->length;
		i++;
	}
	return (sum);
}

void	make_step(t_lemin *data, t_link *link)
{
	link->next_room->ant_id = data->ant_id;
	data->ants_in_road++;
	data->ant_id++;
	data->qty_ants--;
	print_step(data, link->next_room, link->next_room->ant_id, 0);
}

void	move_ants_from_start(t_lemin *data)
{
	t_link **paths;

	paths = data->paths;
	data->var.x = 0;
	while (data->var.x < data->qty_paths && data->qty_ants)
	{
		if (paths[data->var.x]->length > count_sum(data, paths[data->var.x]))
		{
			make_step(data, paths[data->var.x]);
		}
		data->var.x++;
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

int		calc_len(t_lemin *data, t_link *link)
{
	if (link == NULL)
		return (-9999999);
	if (link->next_room->is_end)
		return (1);
	return (1 + calc_len(data, find_link(data, link->next_room)));
}

void	calc_len_paths(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	data->var.y = 0;
	while (data->var.y < data->qty_paths)
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

t_link	*find_link_by_len(t_lemin *data, int len)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->length == len && !head->is_used)
		{
			head->is_used = true;
			return (head);
		}
		head = head->next;
	}
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

void	alg(t_lemin *data)
{
	calc_len_paths(data);
	form_paths(data);
	while (data->qty_ants || data->ants_in_road)
	{
		clear_rooms(data);
		if (data->ants_in_road)
			move_ants(data);
		move_ants_from_start(data);
		printf("\n");
	}
}
