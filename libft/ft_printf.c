/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:23:00 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/04 12:54:43 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_format(char c, va_list ptr)
{
	int	char_count;

	char_count = 0;
	if (c == 'c')
		char_count += ft_printchar_fd(va_arg(ptr, int), 1);
	else if (c == 's')
		char_count += ft_printstr_fd(va_arg(ptr, char *), 1);
	else if (c == 'i' || c == 'd')
		char_count += ft_printnbr_fd(va_arg(ptr, int), 1);
	else if (c == 'p')
		char_count += ft_printhex_adress((unsigned long)va_arg(ptr, void *), 1,
				"0123456789abcdef");
	else if (c == 'u')
		char_count += ft_printnbr_unsigned_fd(va_arg(ptr, unsigned int), 1);
	else if (c == 'x')
		char_count += ft_printhex(va_arg(ptr, unsigned int), 1, \
		"0123456789abcdef");
	else if (c == 'X')
		char_count += ft_printhex(va_arg(ptr, unsigned int), 1, \
		"0123456789ABCDEF");
	else if (c == '%')
		char_count += ft_printchar_fd('%', 1);
	return (char_count);
}

int	ft_printf(const char *speci, ...)
{
	int		i;
	int		char_count;
	va_list	ptr;

	va_start(ptr, speci);
	i = 0;
	char_count = 0;
	while (speci[i])
	{
		if (speci[i] == '%')
			char_count += check_format(speci[++i], ptr);
		else if (speci[i])
			char_count += ft_printchar_fd(speci[i], 1);
		i++;
	}
	return (char_count);
}

// int	main(void)
// {
// 	int test = 0;

// // 	count = 0;
// //  count = ft_printf("%c123%d", 'c', 123);
// test = ft_printf(" %u ", 0);
// printf("%d", test);
// test = printf(" %u ", 0);
// printf("%d", test);
// }