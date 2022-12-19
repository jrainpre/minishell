/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:25:33 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/01 09:32:48 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		return (ft_strlen(s));
	}
	ft_putstr_fd("(null)", fd);
	return (6);
}

int	ft_printchar_fd(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_printnbr_fd(int nbr, int fd)
{
	int		i;
	long	nb;

	nb = nbr;
	i = 0;
	if (nb <= 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	ft_putnbr_fd(nbr, fd);
	return (i);
}
