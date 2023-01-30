/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirect_in_helper2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:31:02 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 15:39:54 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_warning(char *limit)
{
	put_error("minishell: warning: here-document");
	put_error("delimited by end-of-file (wanted `");
	put_error(limit);
	put_error("')\n");
}
