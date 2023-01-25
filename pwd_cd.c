
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

extern t_global g_global;

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
	int	len;
	int	saved;

	saved = 1;
	if (node->out >= 3)
	{
		saved = dup(STDOUT_FILENO);
		check_dup_out(node);
		pwd();
		restore_stdout(saved);
	}
	else
		pwd();
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
	char	*join;

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

void print_cd_error(t_parse *node)
{
    ft_putstr_fd("cd: ", 2);
    if (node->full_cmd[2])
        ft_putstr_fd("string not in pwd: ", 2);
    else
    {
		ft_putnbr_fd(errno, 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd(": ", 2);
		g_global.exit_status = 1;

    }
    ft_putendl_fd(node->full_cmd[1], 2);
}

int	cd_into_home(t_parse *node)
{
	char	*buf;

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
		return (1);
	}
	return (0);
}

void	do_cd(t_parse *node)
{
	char	*buf;
	char	*temp;
	pwd_init(node);
	if (cd_into_home(node))
		return ;
	else
	{
		if (!chdir(node->full_cmd[1]))
			update_pwd(node);
		else
		{
			print_cd_error(node);
			g_global.exit_status = 1;

		}
	}
}
