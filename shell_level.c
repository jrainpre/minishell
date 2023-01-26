/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:23:27 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/26 11:35:50 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			invalid_lvl(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int			get_shelvl(t_env_list *env_lst)
{
	char	*str;
	
	// str = get_env_value(env_lst, "SHLVL");
	// if (!str)
	// 	changevalue(env_lst, "SHLVL=1");
	// if (!ft_strisnum(str))
	// 	changevalue(env_lst, "SHLVL=1");
	// else if (ft_strlen(str) > 10 || invalid_lvl(str))
	// 	changevalue(env_lst, "SHLVL=1");
	// else if (ft_strlen(str) == 10 && ft_strcmp(str, "2147483647") > 0)
	// 	changevalue(env_lst, "SHLVL=2147483647");
	// else
		return (ft_atoi(get_env_value(env_lst, "SHLVL")));
	return (1);
}

void	shell_level_plus_one(t_prompt *struc)
{
	int		shell_level;
	char	*temp;
	char	*str;

	shell_level = get_shelvl(struc->env_lst) + 1;
	temp = ft_itoa(shell_level);
	str = ft_strjoin("SHLVL=", temp);
	changevalue(struc->env_lst, str);
	free(temp);
	free(str);
}