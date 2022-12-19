/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:05:53 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/12 17:11:31 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (n >= 1)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
		n--;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	void *p = ft_memchr(s, 0, 0);
	if (ft_memchr(s, 0, 0) == NULL)
		printf("%s", ft_memchr(s, 0, 0)); 
}*/