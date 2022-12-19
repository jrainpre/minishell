/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:41:49 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/12 17:04:09 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
unction name ft_substr
Prototype char *ft_substr(char const *s, unsigned int start,
size_t len);
Turn in files -
Parameters s: The string from which to create the substring.
start: The start index of the substring in the
string ’s’.
len: The maximum length of the substring.
Return value The substring.
NULL if the allocation fails.
External functs. malloc
Description Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’

*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = malloc(sizeof(char));
		p[0] = '\0';
		return (p);
	}
	i = 0;
	while (s[i + start] && i < len)
		i++;
	p = malloc((i * sizeof(char)) + 1);
	if (p == NULL)
		return (NULL);
	i = start;
	while (s[i] && (i < len + start))
	{
		p[i - start] = s[i];
		i++;
	}
	p[i - start] = '\0';
	return (&p[0]);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*p;

	p = ft_substr("tripouille", 100, 1);
	printf("%s", p);
}
*/
