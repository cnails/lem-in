/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 16:43:51 by cnails            #+#    #+#             */
/*   Updated: 2020/06/28 13:34:04 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_sstlen(char **line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int		ft_strsim(char *str1, char *str2)
{
	return (ft_strlen(str1) == ft_strlen(str2))\
	&& !ft_strcmp(str1, str2);
}

void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
