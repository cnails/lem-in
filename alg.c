/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:22:36 by cnails            #+#    #+#             */
/*   Updated: 2020/08/17 09:22:48 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_link	*find_link(t_lemin *data, t_room *room)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		// printf("link = %s-%s\n", head->prev_room->name, head->next_room->name);
		if (head->prev_room == room)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	move_ants(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->prev_room->ant_id)
		{
			print_step(data, head->next_room, head->prev_room->ant_id);
			head->next_room = head->prev_room->ant_id;
			head->prev_room->ant_id = 0;
			if (head->next_room->is_end)
				data->ants_in_road--;
		}
		head = head->next;
	}	
}

void	print_step(t_lemin *data, t_room *room, int ant_id)
{
	printf("L%d-%s ", ant_id, room->name);
}

void	move_ants_from_start(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	data->var.x = 0;
	while (data->var.x < data->qty_paths)
	{
		if (head->prev_room->is_start)
		{
			if (head->length)
			{

			}
			data->var.x++;
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

int		calc_len(t_lemin *data, t_link *link)
{
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
			printf("len = %d\n", head->length);
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
	// printf("paths[%d] = %s-%s\n", i, paths[i]->prev_room->name, paths[i]->next_room->name);
}

t_link	*find_link_by_len(t_lemin *data, int len)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->length == len)
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
	form_paths(data); // rabotaet))
	// TODO: PROVER' DOROGI 
	// while (data->qty_ants || data->ants_in_road)
	// {
	// 	if (data->ants_in_road)
	// 		move_ants(data);
	// 	move_ants_from_start(data);
	// 	printf("\n");
	// }
}

// t_path	*form_path(t_lemin *data, t_link *head)
// {
// 	t_path	*path;
// 	t_link	*head_link;
// 	t_link	*tmp;
// 	t_link	*link;
// 	t_steps	*step;
// 	t_steps	*head_step;

// 	head_link = NULL;
// 	path = (t_path *)ft_memalloc(sizeof(t_path));
// 	step = (t_steps *)ft_memalloc(sizeof(t_steps));
// 	// path->steps->link = 
// 	head_step = step;
// 	link = head;
// 	head_link = link;
// 	// path->steps->link = (t_link)ft_memalloc(sizeof(t_link));
// 	path->steps->link = *head;
// 	path->steps->next = ft_memalloc(sizeof(t_link));
// 	path->steps = path->steps->next;
// 	while (tmp = find_link(data, link->next_room))
// 	{
// 		printf("%s-%s\n", tmp->prev_room->name, tmp->next_room->name);
// 		// link->next = (t_link *)ft_memalloc(sizeof(t_link));
// 		path->steps->link = *tmp;
// 		// path
// 		link->next = tmp;
// 		// link->next = (t_link *)ft_memalloc(sizeof(t_link));
// 		// link = link->next;
// 		link = link->next;
// 		path->steps->next = (t_path *)ft_memalloc(sizeof(t_path));
// 		path->steps = path->steps->next;
// 		// link->next = NULL;
// 	}
// 	path->steps = head_step;
// 	// path->links = head_link;
// 	return (path);
// }

// void	print_path(t_path *head)
// {
// 	// t_path *head;

// 	// head = data->paths;
// 	// printf("1\n");
// 	while (head->steps)
// 	{
// 		printf("%s-%s\n", head->steps->link.prev_room->name, head->steps->link.next_room->name);
// 		if (head->steps->link.next_room->is_end)
// 			break;
// 		head->steps = head->steps->next;
// 	}
// }

// void	form_paths(t_lemin *data)
// {
// 	t_link *head;
// 	t_path *path;
// 	t_path *head_path;

// 	head = data->head_link;
// 	head_path = NULL;
// 	while (head)
// 	{
// 		printf("here\n");
// 		if (head->prev_room->is_start)
// 		{
// 			path = form_path(data, head);
// 			print_path(path);
// 			// exit(1);
// 		}
// 		head = head->next;
// 	}
// }
