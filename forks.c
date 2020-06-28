/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 12:44:00 by cnails            #+#    #+#             */
/*   Updated: 2020/05/28 13:03:29 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** fuck optimization. Works and is good
*/

int		sum_out(t_lemin *data, t_room *room)
{
	t_link *head;

	head = data->head_link;
	if (room->is_start)
		return (room->output);
	while (head)
	{
		if (ft_strsim(head->next_room->name, room->name))
		{
			return (head->prev_room->output + sum_out(data, head->prev_room));
		}
		head = head->next;
	}
}

void	inp_forks(t_lemin *data)
{
	t_room *head;

	head = data->head;
	while (head)
	{
		if (head->input > 1)
		{
			printf("sum_out = %d for %s\n", sum_out(data, head), head->name);
		}
		head = head->next;
	}
}
