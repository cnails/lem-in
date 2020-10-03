/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:07:26 by dmetallo          #+#    #+#             */
/*   Updated: 2020/09/23 13:21:23 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

bool	is_valid_int(int nbr, char *str)
{
	char *tmp;

	tmp = ft_itoa(nbr);
	if (ft_strcmp(tmp, str))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	return (true);
}

void	ft_error(t_lemin *data, char *str)
{
	if (data->print_errors)
	{
		ft_printf("ERROR: %s\n", str);
	}
	else
		ft_printf("ERROR\n");
	exit(1);
}

void	free_links(t_lemin *data)
{
	t_link	*link;

	while (data->head_link)
	{
		link = data->head_link->next;
		free(data->head_link);
		data->head_link = link;
	}
}

void	free_rooms(t_lemin *data)
{
	t_room	*room;

	while (data->head)
	{
		room = data->head->next;
		free(data->head->name);
		free(data->head);
		data->head = room;
	}
}

void	print_help(void)
{
	ft_printf("\n\033[0;32m\t\t\tHELP\033[0m\n\n");
	ft_printf("\033[0;35m-e\033[0m\tDetailed error description\n");
	ft_printf("\033[0;35m-p\033[0m\tRemaining paths\n");
	ft_printf("\033[0;35m-c\033[0m\tCount of paths\n");
	ft_printf("\033[0;35m-a\033[0m\tCount of ants running along the paths\n");
	exit(1);
}
