/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_usefull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:01:29 by cnails            #+#    #+#             */
/*   Updated: 2020/06/28 14:08:59 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	dont work :(
*/

void	delete_unusefull(t_lemin *data)
{
	t_link *head;
	t_link *prev;
	t_link *tmp;

	prev = NULL;
	head = data->head_link;
	while (head)
	{
		if (head->is_unusefull)
		{
			if (prev)
			{
				prev = head->next;
				head = prev;
			}
		}
		prev = head;
		head = head->next;
	}
}

void	delete_same_bfs(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->next_room->bfs == head->prev_room->bfs)
			head->is_unusefull = true;
		if (!head->next_room->bfs && !head->next_room->is_start)
			head->is_unusefull = true;
		if (!head->prev_room->bfs && !head->prev_room->is_start)
			head->is_unusefull = true;
		if (head->is_unusefull)
			printf("del link %s-%s\n", head->prev_room->name, head->next_room->name);
		head = head->next;
	}
}

int		delete_dead_links(t_lemin *data)
{
	t_link	*head;
	int		flag;

	flag = 0;
	head = data->head_link;
	while (head)
	{
		if (!head->next_room->output && !head->next_room->is_end && !head->is_unusefull)
		{
			printf("del link %s-%s\n", head->prev_room->name, head->next_room->name);
			head->prev_room->output -= 1;
			head->is_unusefull = true;
			flag = 1;
		}
		head = head->next;
	}
	return (flag);
}
