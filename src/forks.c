/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 12:44:00 by cnails            #+#    #+#             */
/*   Updated: 2020/08/26 19:26:59 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_link	*prev_link(t_lemin *data, t_room *room)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->next_room == room)
			return (head);
		head = head->next;
	}
	return (NULL);
}

int		has_output_forks(t_lemin *data, t_link *link)
{
	if (!link)
		return (1);
	if (link->prev_room->is_start)
		return (0);
	if (link->prev_room->output > 1)
		return (1);
	return (has_output_forks(data, prev_link(data, link->prev_room)));
}

t_link	*delete_line(t_lemin *data, t_room *room, t_link *next)
{
	t_link *link;
	t_room *prev_room;

	while (room->output == 0)
	{
		link = prev_link(data, room);
		if (link == next)
			next = link->next;
		prev_room = link->prev_room;
		delete_unusefull(data, link);
		room = prev_room;
	}
	return (next);
}

void	inp_forks(t_lemin *data)
{
	t_link *head;
	t_link *next;
	t_room *room;

	head = data->head_link;
	while (head)
	{
		room = head->prev_room;
		next = head->next;
		if (head->next_room->input > 1)
		{
			if (has_output_forks(data, head))
				delete_unusefull(data, head);
			next = delete_line(data, room, next);
		}
		head = next;
	}
}
