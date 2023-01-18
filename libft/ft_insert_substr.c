/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_substr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:01:21 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/18 14:11:05 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *insert_substr(char *str, char *substr, int pos)
{
	char *temp;
	int i;
	int j;

	i = 0;
	j = 0;
	temp = ft_calloc(ft_strlen(str) + ft_strlen(substr) + 1, 1);
	while (str[i] != '\0')
	{
		if (i == pos)
		{
			while (substr[j] != '\0')
			{
				temp[i] = substr[j];
				i++;
				j++;
			}
			j = 0;
		}
		temp[i] = str[i];
		i++;
	}
	free(str);
	return (temp);
}