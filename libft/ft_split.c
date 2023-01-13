/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:15:27 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/13 14:56:43 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_str_count(const char *str, char c)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			word_count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (word_count);
}

static int	ft_strlen_sep(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_word(const char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (word == NULL)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (ft_check_str_count(s, c) + 1));
	if (strings == NULL)
		return (NULL);
	while (s[j])
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j])
		{
			strings[i] = ft_word(&s[j], c);
			i++;
		}
		while (s[j] && s[j] != c)
			j++;
	}
	strings[i] = 0;
	return (strings);
}

// /*
// #include <stdio.h>
// int	main()
// {
// 	int		index;
// 	char	**split;

// 	split = ft_split("      split       this for  me  !       ", ' ');
// 	index = 0;
// 	while (split[index] != 0)
// 	{
// 		printf("%s\n", split[index]);
// 		index++;
// 	}
// }
// */