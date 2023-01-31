/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:40:39 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/31 10:36:58 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    create_heredoc_space(t_parse *temp, int *i)
{
    char    *str;
    char    *temp_str;

    str = temp->full_cmd[*i];
    temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], "<");
    free(str);
    str = heredoc(temp->full_cmd[*i + 1]);
    if (str == NULL)
        return (0);
    free(temp->full_cmd[*i + 1]);
    temp_str = temp->heredoc;
    temp->full_cmd[*i + 1] = ft_strdup("");
    temp_str = temp->heredoc;
    temp->heredoc = ft_strjoin(temp->heredoc, str);
    free(str);
    free(temp_str);
    return (1);
}

int    create_heredoc_no_space(t_parse *temp, int *i)
{
    char    *str;
    char    *temp_str;

    str = temp->full_cmd[*i];
    temp->full_cmd[*i] = ft_strtrim(temp->full_cmd[*i], "<");
    free(str);
    str = heredoc(temp->full_cmd[*i]);
    if (str == NULL)
        return (0);
    free(temp->full_cmd[*i]);
    temp->full_cmd[*i] = ft_strdup("");
    temp_str = temp->heredoc;
    temp->heredoc = ft_strjoin(temp->heredoc, str);
    free(str);
    free(temp_str);
    return (1);
}

int	create_heredoc(t_parse *temp, int *i)
{
	char	*str;
	char	*temp_str;

	if (check_heredoc_error(temp, i) == 0)
		return (0);
	if (temp->full_cmd[*i][2] != '\0')
    {
        if (create_heredoc_no_space(temp, i) == 0)
            return (0);
    }
	else
    {
        if (create_heredoc_space(temp, i) == 0)
            return (0);
    }
	return (1);
}