/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:54:10 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 15:52:54 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global	g_global;

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

char	**env_list_to_array(t_env_list *env_lst)
{
	char		**envp;
	int			i;
	t_env_list	*temp;
	char		*to_free;

	i = 0;
	temp = env_lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	temp = env_lst;
	while (temp)
	{
		envp[++i] = ft_strjoin(temp->name, "=");
		to_free = envp[i];
		envp[i] = ft_strjoin(envp[i], temp->value);
		free(to_free);
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	dup_fds(t_parse *node)
{
	if (node->out >= 3)
		check_dup_out(node);
	if (node->in >= 3)
		check_dup_in(node);
}

void	update_exit_status(void)
{
	if (g_global.exit_status != 0 && g_global.exit_status != 1 \
		&& g_global.exit_status != 2)
		g_global.exit_status = 127;
}
