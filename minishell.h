/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:13:26 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/05 14:42:36 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"
# define ERROR "ERROR"
# define EXPORT "minishell: export: `%s': not a valid identifier\n"

typedef struct s_read_input
{
	char				*str;
	char				c;
	int					double_open;
	int					single_open;
	char				**output;
	char				**in_token;
}						t_input;

typedef struct s_redir
{
	char				*in;
	int					fd_in;
	char				*out;
	int					fd_out;
	char				*error;
	int					fd_error;
}						t_redir;

typedef struct s_parse_com
{
	char				*command;
	char				*flag;
	t_redir				redir;
}						t_parse_com;

typedef struct s_com
{
	int					numberOfArguments;
	t_parse_com			*arguments;
}						t_com;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

void					ft_split_input(t_input *input);
int						put_to_table(char **str, t_com *table);
void					include_env(t_input *input, t_env_list *env_lst);
char					*get_new_str(char *str, char *envvar, char *ptr);
int						get_new_strlen(char *str, char *value, char *ptr);
char					*get_env_name(char *arg, t_env_list *env_lst);
char					*find_unquoted_dollar(char *str);
void					fill_env_lst(t_env_list **env_lst, char **envp);
char					*get_env_value(t_env_list *env_lst, char *name);
int 					changevalue(t_env_list *env_lst, char *name_value);
void					delete_env_value(t_env_list *env_lst, char *name);
void					free_env_lst(t_env_list *env_lst);
t_env_list				*duplicate_list(t_env_list *env_lst);
t_env_list				*sort_list_alphabetically(t_env_list *env_lst);
void					print_env_list(t_env_list *env_lst);
void					print_export_list(t_env_list *env_lst);
int						is_valid_env(const char *env);
int						add_env_entry(t_env_list *env, char *str);
int						add_env_list(t_env_list *env, char **envp);
int						export_env(t_env_list *env, char **args);
int						add_env_no_value(t_env_list *env, char *str);
int						export(t_env_list *env, char **args);

#endif