/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:13:26 by mkoller           #+#    #+#             */
/*   Updated: 2022/12/19 10:00:47 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"
# define ERROR "ERROR"

typedef struct s_redir
{
	char		*in;
	int			fd_in;
	char		*out;
	int			fd_out;
	char		*error;
	int			fd_error;
}				t_redir;

typedef struct s_parse_com
{
	char		*command;
	char		*flag;
	t_redir		redir;
}				t_parse_com;

typedef struct s_com
{
	int			numberOfArguments;
	t_parse_com	*arguments;
}				t_com;

#endif