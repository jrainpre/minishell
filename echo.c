/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:55:41 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/27 10:25:44 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global g_global;

int	line_count(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	check_dup_out(t_parse *node)
{
	wrapper_dup2(&node->out, STDOUT_FILENO);
	wrapper_close(&node->out);
}

void	check_dup_in(t_parse *node)
{
	wrapper_dup2(&node->in, STDIN_FILENO);
	wrapper_close(&node->in);
}

void	restore_stdout(int saved)
{
	wrapper_dup2(&saved, STDOUT_FILENO);
	wrapper_close(&saved);
}

void	restore_stdin(int saved)
{
	wrapper_dup2(&saved, STDIN_FILENO);
	wrapper_close(&saved);
}

int	only_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	put_to_stdout(t_parse *node, int *i)
{
	int	flag;
	int	k;

	k = 0;
	flag = 1;
	if (!ft_strncmp(node->full_cmd[*i], "-n", 2) && only_n(node->full_cmd[*i]))
	{
		flag = 0;
		*i += 1;
		k = *i;
		while (node->full_cmd[k])
		{
			if (!ft_strncmp(node->full_cmd[k], "-n", 2)
				&& only_n(node->full_cmd[k]))
			{
				node->full_cmd[k] = ft_strtrim(node->full_cmd[k],
						node->full_cmd[k]);
				trim_white(node);
				*i += 1;
			}
			k++;
		}
	}
	while (node->full_cmd[*i])
	{
		ft_putstr_fd(node->full_cmd[*i], 1);
		if (node->full_cmd[*i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		*i += 1;
	}
	*i = 1;
	if (flag)
		ft_putstr_fd("\n", 1);
	else
		flag = 1;
}

int	do_echo(t_parse *node)
{
	int i;
	int j;
	int len;
	int saved;

	g_global.exit_status = 0;
	j = 0;
	i = 1;
	saved = 1;
	len = line_count(node->full_cmd);
	if (len >= 2)
	{
		if (node->out >= 3)
		{
			saved = dup(STDOUT_FILENO);
			check_dup_out(node);
			put_to_stdout(node, &i);
			restore_stdout(saved);
		}
		else
			put_to_stdout(node, &i);
	}
	return (0);
}
