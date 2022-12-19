/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:25:33 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/01 09:32:41 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	unsigned long	l;

	l = n;
	if (l < 10)
		ft_putchar_fd(l + 48, fd);
	else
	{
		ft_putnbr_unsigned_fd(l / 10, fd);
		ft_putnbr_unsigned_fd(l % 10, fd);
	}
}

int	ft_printnbr_unsigned_fd(unsigned int nbr, int fd)
{
	int				i;
	unsigned long	nb;

	nb = nbr;
	i = 0;
	if (nb == 0)
		i++;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	ft_putnbr_unsigned_fd(nbr, fd);
	return (i);
}
