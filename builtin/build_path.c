/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:47:37 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:04:30 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

void	trim_full_cmd(t_parse *node)
{
	int		i;
	char	*temp;

	temp = node->full_cmd[0];
	i = ft_strlen(node->full_cmd[0]) - 1;
	while (node->full_cmd[0][i] != '/')
		i--;
	i++;
	node->full_cmd[0] = ft_strdup(&node->full_cmd[0][i]);
	free(temp);
}

int	build_path(t_parse *node)
{
	char	*path;
	char	**split;

	path = NULL;
	path = get_env_value(node->env, "PATH");
	split = ft_split(path, ':');
	if (node->full_cmd[0][0] == '/' || node->full_cmd[0][0] == '.')
	{
		node->full_path = ft_strdup(node->full_cmd[0]);
		trim_full_cmd(node);
	}
	else
		node->full_path = find_command(split, node->full_cmd[0],
				node->full_path);
	free_table(split);
	return (1);
}
