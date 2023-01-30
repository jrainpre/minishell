/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:40:54 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:06:44 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	put_to_table(char **str, t_prompt *struc)
{
	int		i;
	int		j;
	int		k;
	int		count;
	t_parse	*temp;

	count = count_pipes(str);
	i = 0;
	j = 0;
	k = 0;
	add_nodes(struc, count);
	temp = struc->cmds;
	temp->full_cmd = ft_calloc((pointer_count(str, &k) + 1), sizeof(char *));
	while (str[i])
	{
		if (str[i][0] != '|')
			put_table_non_pipe(str, temp, &i, &j);
		else if (str[i][0] == '|')
		{
			temp = temp->next;
			put_table_pipe(str, temp, &k, &i);
			j = 0;
		}
	}
	return (0);
}

void	add_nodes(t_prompt *struc, int ammount)
{
	t_parse	*node;
	t_parse	*head;
	int		i;
	int		first;

	first = 0;
	i = ammount;
	while (i >= 0)
	{
		node = malloc(sizeof(t_parse) + 1);
		init_node(node);
		if (first == 0)
		{
			struc->cmds = node;
			head = struc->cmds;
			first++;
		}
		else
		{
			head->next = node;
			head = head->next;
		}
		i--;
	}
	node = NULL;
}

char	**copie_env(char **env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		new_env[j] = ft_strjoin(env[j], "\0");
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**trim_2d_array(char **table)
{
	int		i;
	int		j;
	int		k;
	char	**new_table;

	i = 0;
	j = 0;
	k = 0;
	while (table[i])
		i++;
	new_table = malloc(sizeof(char *) * (i + 1));
	while (table[j])
	{
		if (table[j][0] != '\0')
		{
			new_table[k] = ft_strdup(table[j]);
			k++;
		}
		j++;
	}
	free_table(table);
	new_table[k] = NULL;
	return (new_table);
}

void	trim_nodes(t_prompt *struc)
{
	t_parse	*node;

	node = struc->cmds;
	while (node)
	{
		node->full_cmd = trim_2d_array(node->full_cmd);
		node = node->next;
	}
}
