/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:02:54 by jrainpre          #+#    #+#             */
/*   Updated: 2022/10/12 11:39:19 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == (char)(c))
			return ((char *)(&s[i]));
		i--;
	}
	if (s[i] == (char)(c))
		return ((char *)(&s[i]));
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "hallotest";
	char	*p;

	p = ft_strrchr(str, 'l');
	printf("%s", p);
}
*/