/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:02:54 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/12 11:36:46 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)(c))
			return ((char *)(&s[i]));
		i++;
	}
	if (s[i] == (char)(c))
		return ((char *)(&s[i]));
	return (NULL);
}

/*
int	main(void)
{
char	*p;

char	*str 
str = "hallotest";
p = ft_strchr(str, 'o');
printf("%s", p);
}
*/
