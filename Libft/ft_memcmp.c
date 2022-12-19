/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:55:36 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/07 12:59:41 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
int main ()
{
	char	str1[50];
	char	str2[];

	str1[50] = "Hallo test Hallo";
	str2[] = "Aallo";
	printf("%d", ft_memcmp(&str1[0], str2, 5));
	printf("%d", memcmp(&str1[0], str2, 5));
}
*/
