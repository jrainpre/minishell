/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:15:27 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:07:19 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_close_quotes(t_input *input, int i)
{
	if (input->str[i] == '\"' && !input->double_open && !input->single_open && \
		(ft_strchr(&input->str[i + 1], '\"') != NULL))
		input->double_open = 1;
	else if (input->str[i] == '\"' && input->double_open)
		input->double_open = 0;
	else if (input->str[i] == '\'' && !input->double_open \
			&& !input->single_open && (ft_strchr(&input->str[i + 1], \
			'\'') != NULL))
		input->single_open = 1;
	else if (input->str[i] == '\'' && input->single_open)
		input->single_open = 0;
}

int	ft_check_str_count(t_input *input)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (input->str[i])
	{
		while (input->str[i] && input->str[i] == ' ')
			i++;
		if (input->str[i])
			word_count++;
		input->double_open = 0;
		input->single_open = 0;
		while (input->str[i] && ((input->str[i] != ' ')
				|| input->single_open || input->double_open))
		{
			open_close_quotes(input, i);
			i++;
		}
	}
	return (word_count);
}

int	ft_strlen_sep(t_input *input, int i)
{
	int	j;

	j = 0;
	input->double_open = 0;
	input->single_open = 0;
	while (input->str[i] && ((input->str[i] != ' ') || input->single_open
			|| input->double_open))
	{
		open_close_quotes(input, i);
		i++;
		j++;
	}
	return (j);
}
