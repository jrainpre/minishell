/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:23:08 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/26 13:42:56 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ctrl_d(int sig)
{
    //g_global = 130;
    exit(0);
    (void)sig;
}

void	restore_prompt(int sig)
{
	//g_global = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	//g_global = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	//g_global = 131;
	printf("Quit! (core dumped)\n");
	(void)sig;
}

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
}