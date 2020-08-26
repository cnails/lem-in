/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 12:44:00 by cnails            #+#    #+#             */
/*   Updated: 2020/08/26 16:23:48 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** fuck optimization. Works and is good
*/

// int		sum_out(t_lemin *data, t_room *room)
// {
// 	t_link *head;

// 	head = data->head_link;
// 	if (room->is_start)
// 		return (room->output);
// 	while (head)
// 	{
// 		if (ft_strsim(head->next_room->name, room->name))
// 		{
// 			return (head->prev_room->output + sum_out(data, head->prev_room));
// 		}
// 		head = head->next;
// 	}
// }

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
	// printf("link = %s(%d)(%d)-%s\n", link->prev_room->name, link->prev_room->input, link->prev_room->output, link->next_room->name);
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
		// if (link == NULL)

			// return (next);
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
