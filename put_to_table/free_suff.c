/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_suff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:37:57 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 18:46:16 by jrainpre         ###   ########.fr       */
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

void	free_heredoc(t_parse *cmds)
{
	t_parse	*head;
	t_parse	*help;

	head = cmds;
	help = head;
	while (help)
	{
		if (help->heredoc)
			free(help->heredoc);
		help = help->next;
	}
}

void	clean_exit(t_prompt *struc, t_input *input)
{
	unlink(".*");
	free(struc->cmds->heredoc);
	// free_heredoc(struc->cmds);
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
