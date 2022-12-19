/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:25:33 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/01 09:32:45 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_strlen_for_int(unsigned long n, char *base)
{
	int	l;
	int	l_base;

	l_base = ft_strlen(base);
	l = 0;
	if (n <= 0)
		l++;
	while (n != 0)
	{
		l++;
		n = n / l_base;
	}
	return (l);
}

int	ft_printhex_adress(unsigned long n, int fd, char *base_to)
{
	int	i;

	if (n != 0)
	{
		i = get_strlen_for_int(n, base_to);
		i = i + 2;
		ft_putchar_fd('0', fd);
		ft_putchar_fd('x', fd);
		ft_puthex_fd(n, 1, base_to);
	}
	else
		i = ft_printstr_fd("(nil)", fd);
	return (i);
}

int	ft_printhex(unsigned int n, int fd, char *base_to)
{
	int	i;

	i = get_strlen_for_int(n, base_to);
	ft_puthex_fd(n, fd, base_to);
	return (i);
}

void	ft_puthex_fd(unsigned long n, int fd, char *base_to)
{
	if (n < 16)
		ft_putchar_fd(base_to[n], fd);
	else
	{
		ft_puthex_fd(n / 16, fd, base_to);
		ft_puthex_fd(n % 16, fd, base_to);
	}
}
