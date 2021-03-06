/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_usefull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:01:29 by cnails            #+#    #+#             */
/*   Updated: 2020/08/26 19:14:46 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	delete_unusefull(t_lemin *data, t_link *tmp)
{
	t_link *head;
	t_link *prev;

	prev = NULL;
	head = data->head_link;
	while (head && head != tmp)
	{
		prev = head;
		head = head->next;
	}
	if (!prev && head)
		data->head_link = head->next;
	else if (head)
		prev->next = head->next;
	if (tmp->prev_room->output > 0)
		tmp->prev_room->output--;
	if (tmp->next_room->input > 0)
		tmp->next_room->input--;
	free(tmp);
	tmp = NULL;
}

void	delete_same_bfs(t_lemin *data)
{
	t_link *head;
	t_link *next;

	head = data->head_link;
	while (head->next)
	{
		next = head->next;
		if (head->next_room->bfs == head->prev_room->bfs)
			delete_unusefull(data, head);
		else if (!head->next_room->bfs && !head->next_room->is_start)
			delete_unusefull(data, head);
		else if (!head->prev_room->bfs && !head->prev_room->is_start)
			delete_unusefull(data, head);
		head = next;
	}
}

int		delete_dead_links(t_lemin *data)
{
	t_link	*head;
	t_link	*next;
	int		flag;

	flag = 0;
	head = data->head_link;
	next = NULL;
	while (head)
	{
		next = head->next;
		if (!head->next_room->output && !head->next_room->is_end)
		{
			delete_unusefull(data, head);
			flag = 1;
		}
		head = next;
	}
	return (flag);
}
