
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:23:19 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/10 12:26:01 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	do_pwd(t_parse *node)
{
	int	i;
	int	j;
	int	len;
	int	saved;

	j = 0;
	i = 1;
	saved = 1;
	while (node->out[j])
	{
		if (node->out[j] >= 3)
		{
			saved = dup(STDOUT_FILENO);
			check_dup(node, j);
			pwd();
			restore_stdout(saved);
		}
		else
			pwd();
		j++;
	}
	return (0);
}

void	pwd_init(t_parse *node)
{
	char	*temp;

	if (get_env_value(node->env, "PWD") == NULL)
		add_env_entry(node->env, "PWD=' '");
	if (get_env_value(node->env, "OLDPWD") == NULL)
		add_env_entry(node->env, "OLDPWD=' '");
}

void	update_pwd(t_parse *node)
{
	char	*temp;
	char *join;

	temp = getcwd(NULL, 0);
	join = ft_strjoin("OLDPWD=", temp);
	changevalue(node->env, join);
	free(join);
	temp = getcwd(NULL, 0);
	join = ft_strjoin("PWD=", temp);
	changevalue(node->env, join);
	free(temp);
	free(join);
}

void	cd_path_not_found(char *path)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(path, 2);
}

void	do_cd(t_parse *node)
{
	char	*buf;
	char	*temp;
	int		i;

	pwd_init(node);
	if (node->full_cmd[1] == NULL)
	{
		if (get_env_value(node->env, "HOME") != NULL)
		{
			buf = get_env_value(node->env, "HOME");
			if (!chdir(buf))
				update_pwd(node);
			else
				cd_path_not_found(buf);
			free(buf);
		}
	}
	else
	{
		{
			if (!chdir(node->full_cmd[1]))
				update_pwd(node);
			else
				cd_path_not_found(node->full_cmd[1]);
		}
	}
}
