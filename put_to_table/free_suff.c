/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_suff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:37:57 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 15:16:51 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_prompt(t_prompt *struc)
{
	int		i;
	t_parse	*head;
	t_parse	*help;

	i = 0;
	head = struc->cmds;
	help = head;
	while (help)
	{
		free_table(help->full_cmd);
		free(help->full_path);
		help = help->next;
	}
	help = head->next;
	while (head)
	{
		if (head)
			free(head);
		head = help;
		if (help)
			help = help->next;
	}
	head = NULL;
	help = NULL;
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (table != NULL)
	{
		while (table[i])
		{
			free(table[i]);
			table[i] = NULL;
			i++;
		}
		free(table);
		table = NULL;
	}
}

void	clean_interrupt(t_env_list *env_lst, t_input *input)
{
	unlink(".*");
	free(input->str);
	free_env_lst(env_lst);
}

void	clean_exit(t_prompt *struc, t_input *input)
{
	unlink(".*");
	free_prompt(struc);
	free(input->str);
	free_table(input->output);
	free_env_lst(struc->env_lst);
}

void	clean_loop(t_prompt *struc, t_input *input)
{
	unlink(".*");
	free_prompt(struc);
	free(input->str);
	free_table(input->output);
}
