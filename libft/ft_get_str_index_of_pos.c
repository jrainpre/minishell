/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_str_index_of_pos.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:12:56 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/20 08:14:12 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_str_index_of_pos(char *str, char *pos)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (&str[i] == pos)
			return (i);
		i++;
	}
	return (-1);
}
