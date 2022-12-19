/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:09:03 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/12 12:23:18 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function name ft_strjoin
Prototype char *ft_strjoin(char const *s1, char const *s2);
Turn in files -
Parameters s1: The prefix string.
s2: The suffix string.
Return value The new string.
NULL if the allocation fails.
External functs. malloc
Description Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
*/
/*
#include <stdlib.h>
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[++j])
		p[i++] = s1[j];
	j = -1;
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	return (&p[0]);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*p;

	s1 = "test";
	s2 = "Hallo";
	
	p = ft_strjoin(s1, s2);
	printf("%s", p);
}
*/