/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 12:42:43 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 13:11:03 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	parse_ants(t_lemin *data)
{
	while (get_next_line(0, &data->var.line) > 0)
	{
		printf("%s\n", data->var.line);
		if (ft_isdigit(data->var.line[0]))
		{
			data->qty_ants = ft_atoi(data->var.line);
			free(data->var.line);
			break ;
		}
		else if (data->var.line[0] == '#')
		{
			free(data->var.line);
			continue;
		}
		else
			ft_error(data, "parse_ants");
		free(data->var.line);
	}
	ft_parse(data);
}

void	check_error(t_lemin *data, bool start, bool end)
{
	if (!data->var.line)
		ft_error(data, "USAGE: ./lem-in < map");
	if (!(start && end))
		ft_error(data, "missing start or end");
	if (!data->head_link)
		ft_error(data, "0 link");
}

void	ft_parse(t_lemin *data)
{
	bool	start;
	bool	end;

	start = false;
	end = false;
	while (get_next_line(0, &data->var.line) > 0)
	{
		printf("%s\n", data->var.line);
		if (!ft_strcmp("##start", data->var.line))
		{
			parse_room(data, true, false);
			start = true;
		}
		else if (!ft_strcmp("##end", data->var.line))
		{
			parse_room(data, false, true);
			end = true;
		}
		else if (data->var.line[0] == '#')
			free(data->var.line);
		else
			parse_room(data, false, false);
	}
	check_error(data, start, end);
}
