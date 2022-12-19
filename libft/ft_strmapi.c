/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:14:55 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/13 08:36:52 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	unsigned int	i;

	if (!s)
		return (NULL);
	p = malloc(ft_strlen(s) + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = (*f)(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}

/*
char	test(unsigned int i, char c)
{
return('a');
}

#include <stdio.h>
int	main(void)
{
	char	*p;
	char	(*testf)(unsigned int, char);

	(testf)(unsigned int, char) = &test;
p = ft_strmapi("",testf);
printf("%s", p);
}
*/