/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:15:27 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:07:23 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_word(t_input *input, int i)
{
	int		len_word;
	char	*word;
	char	*temp_str;

	temp_str = &input->str[i];
	len_word = ft_strlen_sep(input, i);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len_word)
	{
		word[i] = temp_str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	split_input_helper(t_input *input, int *i, int *j)
{
	while (input->str[*j] && input->str[*j] == ' ')
		*j += 1;
	if (input->str[*j])
	{
		input->output[*i] = ft_word(input, *j);
		*i += 1;
	}
	while (input->str[*j] && ((input->str[*j] != ' ') || input->single_open
			|| input->double_open))
	{
		open_close_quotes(input, *j);
		*j += 1;
	}
}

void	ft_split_input(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (input->str == NULL)
		return ;
	input->output = (char **)malloc(sizeof(char *) * (ft_check_str_count(input)
				+ 1));
	if (input->output == NULL)
		return ;
	while (input->str[j])
		split_input_helper(input, &i, &j);
	input->output[i] = 0;
}
