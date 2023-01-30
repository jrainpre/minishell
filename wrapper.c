/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:13:47 by jrainpre          #+#    #+#             */
/*   Updated: 2023/01/30 09:49:17 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wrapper_fork(int *pid)
{
	if ((*pid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
}

void	wrapper_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	wrapper_dup2(int *old_fd, int new_fd)
{
	if (dup2(*old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(1);
	}
}

void	wrapper_close(int *fd)
{
	if (close(*fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	wrapper_wait(int *status)
{
	if (wait(status) == -1)
	{
		perror("wait");
		exit(1);
	}
}
