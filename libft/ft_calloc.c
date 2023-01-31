/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:03:40 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/31 13:14:58 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;
	long	space;

	space = size * nmemb;
	if (size > 4294967294 || nmemb > 4294967294)
		return (NULL);
	p = malloc(space + 100);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		*(char *)(p + i) = '\0';
		i++;
	}
	return (p);
}

/*
#include <stdlib.h>
int main ()
{
void	*ft;
void	*original;

ft = ft_calloc(SIZE_MAX,SIZE_MAX);
original = calloc(SIZE_MAX, SIZE_MAX);
}
*/
