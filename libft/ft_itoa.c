/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:49:20 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/10 11:48:15 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_str_len(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		l;
	long	nb;

	nb = n;
	l = get_str_len(nb);
	p = malloc((l + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	p[l] = '\0';
	l--;
	if (nb == 0)
		p[l] = '0';
	if (nb < 0)
	{
		p[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		p[l] = (nb % 10) + '0';
		nb = nb / 10;
		l--;
	}
	return (p);
}
/*
#include <limits.h>
#include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
}
*/