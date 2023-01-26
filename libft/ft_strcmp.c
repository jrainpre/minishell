/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:09:43 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/26 10:46:22 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (-99);
	else
	{
		while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
}
