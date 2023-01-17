/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:13:26 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/17 15:05:21 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"
# define ERROR "ERROR"
# define EXPORT_ERROR "minishell: export: `%s': not a valid identifier\n"
# define PARSE_ERROR "minishell: parse error near \'\\n'"
# define GREEN "\001\033[1;92m\002"
# define WHITE "\033[0;37m"
# define PROMPT "\001\033[1;92m\002 minishell $> \033[0;37m"
# define USER "USER"

struct s_env_list;
typedef struct s_parse
{
	char				**full_cmd;
	char				*full_path;
	struct s_parse		*next;
	int					*in;
	int					*out;
	struct s_env_list	*env;
}						t_parse;

typedef struct s_prompt
{
	t_parse				*cmds;
	char				**envp;
	pid_t				pid;
	int					exit_flag;
}						t_prompt;

typedef struct s_read_input
{
	char				*str;
	char				c;
	int					double_open;
	int					single_open;
	char				**output;
	char				**in_token;
}						t_input;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

void					ft_split_input(t_input *input);
int						put_to_table(char **str, t_prompt *struc);
void					include_env(t_input *input, t_env_list *env_lst);
char					*get_new_str(char *str, char *envvar, char *ptr);
int						get_new_strlen(char *str, char *value, char *ptr);
char					*get_env_name(char *arg, t_env_list *env_lst);
char					*find_unquoted_dollar(char *str);
void					fill_env_lst(t_env_list **env_lst, char **envp);
char					*get_env_value(t_env_list *env_lst, char *name);
int						changevalue(t_env_list *env_lst, char *name_value);
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
int						line_count(char **str);
int						do_echo(t_parse *node);
int						do_exit(t_prompt *struc);
int						get_all_fd(t_prompt *struc);
int						builtin(t_parse *node, t_prompt *struc);
int						count_redirect(char **split);
void					alloc_fd_out(t_parse *node, int cnt);
int						get_all_fd_out(t_prompt *struc);
int						trim_white(t_parse *node);
void					alloc_fd_in(t_parse *node, int cnt);
int						get_all_fd_in(t_prompt *struc);
void					restore_stdout(int saved);
void					check_dup(t_parse *node, int i);
int						check_valid_filename(t_parse *node);
int						do_pwd(t_parse *node);
int						pwd(void);
void					do_cd(t_parse *node);

#endif
