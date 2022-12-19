/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:18:48 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/10 13:52:41 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}
/*
void	test(unsigned int i, char *c)
{
	*c = 'b';
}

#include <stdio.h>
int	main(void)
{
	char	p[];
	void	(*testf)(unsigned int, char*);

	p[] = "Hallo";
	(testf)(unsigned int, char) = &test;
 ft_striteri(p,testf);
printf("%s", p);
}
*/
