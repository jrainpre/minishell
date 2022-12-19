/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:31:45 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/12 11:19:06 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_l;
	size_t	src_l;

	if (!dst && !size)
		return (0);
	dst_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	i = 0;
	j = dst_l;
	if (dst_l < size - 1 && size > 0)
	{
		while (src[i] && dst_l + i < size - 1)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	if (dst_l >= size)
		dst_l = size;
	return (dst_l + src_l);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main ()
{
	char	str1[50];
	char	str2[];
	char	str3[50];
	char	str4[];
	char	dest[100];

	str1[50] = "1234567890";
	str2[] = "1234567890";
	str3[50] = "This part";
	str4[] = " was appended.";
	printf("%zu", ft_strlcat(NULL, str2, 0));
	printf("\n");
	printf("%s", str1);
	printf("\n");
			memset(dest, 'r', 15);
		printf("%ld",ft_strlcat(dest, "lorem ipsum dolor sit amet", 5));
		write(1, "\n", 1);
		write(1, dest, 15);
}
*/