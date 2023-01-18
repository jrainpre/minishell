/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:38 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/18 17:18:17 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr_int(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

static char	*find_command(char **env_path, char *cmd, char *full_path)
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
	int	i;

	i = ft_strlen(node->full_cmd[0]) - 1;
	while (node->full_cmd[0][i] != '/')
		i--;
	i++;
	node->full_cmd[0] = ft_strdup(&node->full_cmd[0][i]);
}

char	**env_list_to_array(t_env_list *env_lst)
{
	char		**envp;
	int			i;
	t_env_list	*temp;

	i = 0;
	temp = env_lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp = env_lst;
	while (temp)
	{
		envp[i] = ft_strjoin(temp->name, "=");
		envp[i] = ft_strjoin(envp[i], temp->value);
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	exec_cmd(t_parse *node)
{
	char	*path;
	char	**split;
	int		pid;
	int		t;

	pid = 0;
	path = NULL;
	path = get_env_value(node->env, "PATH");
	split = ft_split(path, ':');
	//free(path);
	if (node->full_cmd[0][0] == '/')
	{
		node->full_path = ft_strdup(node->full_cmd[0]);
		trim_full_cmd(node);
	}
	else
		node->full_path = find_command(split, node->full_cmd[0],
				node->full_path);
	pid = fork();
	if (pid == 0)
		execve(node->full_path, node->full_cmd, env_list_to_array(node->env));
	else
		wait(0);
}

int	builtin(t_parse *node, t_prompt *struc)
{
    if (!ft_strncmp(node->full_cmd[0], ECHO, 4))
        do_echo(node);
    else if (!ft_strncmp(node->full_cmd[0], EXIT, 4))
        do_exit(struc);
     else if (!ft_strcmp(node->full_cmd[0], CD))
         do_cd(node);
    else if (!ft_strcmp(node->full_cmd[0], PWD))
        do_pwd(node);
    else if (!ft_strcmp(node->full_cmd[0], ENV))
        do_env(node);
    else if (!ft_strcmp(node->full_cmd[0], EXPORT))
        do_export(node);
    else if (!ft_strcmp(node->full_cmd[0], UNSET))
        do_unset(node);
    else
    {
        exec_cmd(node);
    }
    return (0);
}