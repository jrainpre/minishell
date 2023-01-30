/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:23:19 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:14:23 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

void	cd_path_not_found(char *path)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(path, 2);
}

void	print_cd_error(t_parse *node)
{
	ft_putstr_fd("cd: ", 2);
	if (node->full_cmd[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": ", 2);
		g_global.exit_status = 1;
	}
	ft_putendl_fd(strerror(errno), 2);
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
