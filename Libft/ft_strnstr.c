/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:55:19 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/12 11:49:44 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)(big));
	if (len == 0)
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		while (big[i + j] == little[j] && big[i + j] != '\0' && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)(&big[i]));
		i++;
		j = 0;
	}
	return (NULL);
}

/*
#include <stdio.h>
int main ()
{
	char	str1[50];
	char	str2[];

	str1[50] = "TEsttestzteHallosteeHllo";
	str2[] = "Hallo";
	printf("%s", ft_strnstr(str1, str2, 5));
			printf("\n");
}
*/