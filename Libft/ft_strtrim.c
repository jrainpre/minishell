/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:27:23 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/10 14:10:19 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Function name ft_strtrim
Prototype char *ft_strtrim(char const *s1, char const *set);
Turn in files -
Parameters s1: The string to be trimmed.
set: The reference set of characters to trim.
Return value The trimmed string.
NULL if the allocation fails.
External functs. malloc
Description Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.*/

#include "libft.h"

// #include <stdlib.h>
// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

static int	ft_check_set(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_find_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_check_set(s1[i], set))
		i++;
	return (i);
}

static int	ft_find_end(char const *s1, char const *set)
{
	int	i;
	int	len;

	len = ft_strlen(s1) - 1;
	i = len;
	while (s1[i] && i >= 0 && ft_check_set(s1[i], set))
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*p;

	if (!s1)
		return (NULL);
	start = ft_find_start(s1, set);
	end = ft_find_end(s1, set);
	if (start >= end)
	{
		p = malloc(1);
		if (p == NULL)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	p = malloc(end - start + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		p[i++] = s1[start++];
	p[i] = '\0';
	return (p);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*s1;
	char	*set;
	char	*p;

	s1 = "          Hello          ";
	set = " \n\t";
	p = ft_strtrim(s1, set);
	printf("%s", p);
}
*/