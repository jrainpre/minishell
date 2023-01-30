/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_in_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:31:02 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:06:04 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp_special(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	if (i < n)
	{
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	}
	return (0);
}

void	print_file_error(char **str, int i)
{
	ft_putstr_fd("minishell: no such file or directory: ", \
	2);
	ft_putstr_fd(str[i], 2);
	ft_putstr_fd("\n", 2);
}

void	fd_in_helper(t_parse *temp, int *i)
{
	if (temp->full_cmd[*i][0] == '<' && temp->full_cmd[*i][1] == '<')
	{
		create_heredoc(temp, i);
		heredoc_file(temp);
	}
	else if (temp->full_cmd[*i][0] == '<')
		create_trunc_in(temp, i);
	*i += 1;
}

void	heredoc_helper(char *temp, char *str[2])
{
	temp = str[1];
	str[1] = ft_strjoin(str[1], str[0]);
	free(temp);
	free(str[0]);
	str[0] = readline("heredoc> ");
}
