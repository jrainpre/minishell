/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:38 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/24 16:02:15 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_parse *node)
{
	int		l;

	if (!node->full_cmd)
		return (0);
	if ((node->full_cmd && ft_strchr(*node->full_cmd, '/')) || (node->full_path && \
		ft_strchr(node->full_path, '/')))
		return (0);
	l = ft_strlen(*node->full_cmd);
	if (!ft_strncmp(*node->full_cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}

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

void dup_fds(t_parse *node)
{
	if (node->out >= 3)
		check_dup_out(node);
		
	if (node->in >= 3)
		check_dup_in(node);
}

void	exec_cmd(t_parse *node, int to_fork)
{
	char	*path;
	char	**split;
	int		pid;
	int saved_out;
	int saved_in;
	
	saved_out = dup(STDOUT_FILENO);
	saved_in = dup(STDIN_FILENO);
	pid = 0;
	path = NULL;
	path = get_env_value(node->env, "PATH");
	split = ft_split(path, ':');
	if (node->full_cmd[0][0] == '/')
	{
		node->full_path = ft_strdup(node->full_cmd[0]);
		trim_full_cmd(node);
	}
	else
		node->full_path = find_command(split, node->full_cmd[0],
				node->full_path);
	dup_fds(node);
	pid = fork();
	if (pid == 0)
		execve(node->full_path, node->full_cmd, env_list_to_array(node->env));
	else
		wait(0);
	restore_stdout(saved_out);
	restore_stdin(saved_in);
}

int	builtin(t_parse *node, t_prompt *struc, int to_fork)
{
	if (!ft_strncmp(node->full_cmd[0], ECHO, 4))
		do_echo(node);
	else if (!ft_strncmp(node->full_cmd[0], EXIT, 4))
		do_exit(struc);
	else if (!ft_strncmp(node->full_cmd[0], CD, 2))
		do_cd(node);
	else if (!ft_strncmp(node->full_cmd[0], PWD, 3))
		do_pwd(node);
	else if (!ft_strncmp(node->full_cmd[0], ENV, 3))
		do_env(node);
	else if (!ft_strncmp(node->full_cmd[0], EXPORT, 6))
		do_export(node);
	else if (!ft_strncmp(node->full_cmd[0], UNSET, 5))
		do_unset(node);
	else
		exec_cmd(node, to_fork);
	return (0);
}