/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:09:03 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 13:12:26 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	else if (!s2)
		return (ft_strdup(s1));
	else if (!s1)
		return (ft_strdup(s2));
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