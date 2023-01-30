/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_filedescriptors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:08:10 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 14:04:57 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dup_out(t_parse *node)
{
	wrapper_dup2(&node->out, STDOUT_FILENO);
	wrapper_close(&node->out);
}

void	check_dup_in(t_parse *node)
{
	wrapper_dup2(&node->in, STDIN_FILENO);
	wrapper_close(&node->in);
}

void	restore_stdout(int saved)
{
	wrapper_dup2(&saved, STDOUT_FILENO);
	wrapper_close(&saved);
}

void	restore_stdin(int saved)
{
	wrapper_dup2(&saved, STDIN_FILENO);
	wrapper_close(&saved);
}
