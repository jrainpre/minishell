/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:15:27 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/29 20:35:49 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_close_quotes(t_input *input, int i)
{
	if (input->str[i] == '\"' && !input->double_open && !input->single_open &&
		(ft_strchr(&input->str[i + 1], '\"') != NULL))
		input->double_open = 1;
	else if (input->str[i] == '\"' && input->double_open)
		input->double_open = 0;
	else if (input->str[i] == '\'' && !input->double_open &&
				!input->single_open && (ft_strchr(&input->str[i + 1],
							'\'') != NULL))
		input->single_open = 1;
	else if (input->str[i] == '\'' && input->single_open)
		input->single_open = 0;
}

static int	ft_check_str_count(t_input *input)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (input->str[i])
	{
		while (input->str[i] && input->str[i] == input->c)
			i++;
		if (input->str[i])
			word_count++;
		input->double_open = 0;
		input->single_open = 0;
		while (input->str[i] && ((input->str[i] != input->c)
				|| input->single_open || input->double_open))
		{
			open_close_quotes(input, i);
			i++;
		}
	}
	return (word_count);
}

static int	ft_strlen_sep(t_input *input, int i)
{
	int	j;

	j = 0;
	input->double_open = 0;
	input->single_open = 0;
	while (input->str[i] && ((input->str[i] != input->c) || input->single_open
			|| input->double_open))
	{
		open_close_quotes(input, i);
		i++;
		j++;
	}
	return (j);
}

static char	*ft_word(t_input *input, int i)
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
	while (input->str[*j] && input->str[*j] == input->c)
		*j += 1;
	if (input->str[*j])
	{
		input->output[*i] = ft_word(input, *j);
		*i += 1;
	}
	while (input->str[*j] && ((input->str[*j] != input->c)
			|| input->single_open || input->double_open))
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
