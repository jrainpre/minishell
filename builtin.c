/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:38 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/13 15:21:19 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr(const char *s, int c)
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

char	*getenvp(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

void exec_cmd(t_parse *node, char **envp)
{
    char *path;
    char **split;
    int pid;
    int t;
    
    pid = 0;
    path = NULL;
    path = getenvp("PATH", envp, 4);
	split = ft_split(path, ':');
	free(path);
	node->full_path = find_command(split, node->full_cmd[0], node->full_path);
    pid = fork();
    if (pid == 0)
    {
        execve(node->full_path, node->full_cmd, envp);
    }
    else 
        wait();
}

int builtin(t_parse *node, t_prompt *struc, char **envp)
{
    if (!ft_strncmp(node->full_cmd[0], ECHO, 4))
        do_echo(node);
    else if (!ft_strncmp(node->full_cmd[0], EXIT, 4))
        do_exit(struc);
    // else if (!ft_strcmp(node->full_cmd, CD))
    //     do_cd(node);
    // else if (!ft_strcmp(node->full_cmd, PWD))
    //     do_pwd(node);
    // else if (!ft_strcmp(node->full_cmd, ENV))
    //     do_env(node);
    // else if (!ft_strcmp(node->full_cmd, EXPORT))
    //     do_export(node);
    // else if (!ft_strcmp(node->full_cmd, UNSET))
    //     do_unset(node);
    else
    {
        exec_cmd(node, envp);
        // printf("Right now command is unknown!\n");   
    }
    return (0);
}