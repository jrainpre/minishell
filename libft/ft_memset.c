/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:39:54 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/10 14:18:02 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)(c);
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	void	*p;
	char	str[];

	str[] = "hallo";
	p = ft_memset(str, 99, 4);
	printf("%s", (unsigned char *)(p));
}
*/
