/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:23:19 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:15:28 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

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
	free(temp);
	free(join);
	temp = getcwd(NULL, 0);
	join = ft_strjoin("PWD=", temp);
	changevalue(node->env, join);
	free(temp);
	free(join);
}
