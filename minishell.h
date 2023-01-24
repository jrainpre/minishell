/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:13:26 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/24 15:49:55 by mkoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <errno.h>

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
	char				*heredoc;
	struct s_parse		*next;
	int					in;
	int					out;
	struct s_env_list	*env;
	int 				exit_status;
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
void					include_env(t_parse *node);
char					*get_new_str_env(char *str, char *envvar, char *ptr);
int						get_new_strlen_env(char *str, char *value, char *ptr);
char					*get_env_name(char *arg, t_env_list *env_lst);
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
int						export(t_parse *node);
int						line_count(char **str);
int						do_echo(t_parse *node);
int						do_exit(t_prompt *struc);
int						get_all_fd(t_prompt *struc);
int						builtin(t_parse *node, t_prompt *struc, int fork);
int						count_redirect(char **split);
void					alloc_fd_out(t_parse *node, int cnt);
int						get_all_fd_out(t_prompt *struc);
int						trim_white(t_parse *node);
void					alloc_fd_in(t_parse *node, int cnt);
int						get_all_fd_in(t_prompt *struc);
void					restore_stdout(int saved);
void					check_dup_out(t_parse *node);
void					check_dup_in(t_parse *node);
int						check_valid_filename(t_parse *node);
int						do_pwd(t_parse *node);
int						pwd(void);
void					do_cd(t_parse *node);
int						do_unset(t_parse *node);
int						do_env(t_parse *node);
int						do_export(t_parse *node);
void					free_table(char **table);
char					**trim_2d_array(char **table);
char					*prepare_input_string(char *str);
char					*add_space_before_this_position(char *str, int *index);
char					*add_space_after_this_position(char *str, int *index);
int						check_if_unquoted_special_char(char *str, int j,
							int *s_q, int *d_q);
int						check_lastpos_is_space(char *str, int i);
int						check_nextpos_is_space(char *str, int i);
int						check_if_qoute(int *single_q, int *double_q, char c);

int						check_not_in_d_quotes_inpos(char *str, int *double_q);
int						check_not_in_s_quotes_inpos(char *str, int *double_q);
int						check_not_in_s_quotes(char *str, char *pos);
int						check_not_in_d_quotes(char *str, char *pos);
int						check_pos_not_in_quotes(char *str, char *pos);
char					*find_unquoted_char(char *str, char c);
char					*get_env_tilde_value(t_env_list *env);
char					*get_new_str_tilde(char *str, char *envvar, char *ptr);
void					expand_tilde(t_parse *node);
//delete_closed_quotes.c
int						new_len_no_quotes(char *str);
char					*delete_closed_quotes_str(char *str, int s_quotes,
							int d_quotes);
void					delete_closed_quotes_cmd(t_parse *node);
void					put_error(char *str);
int						is_builtin(t_parse *node);
void					restore_stdin(int saved);
void					do_parent(t_parse *node, int *fd, int *backup);
void					do_child(t_parse *node, t_prompt *struc, int *fd,
							int *backup);
int						piper(t_parse *node, t_prompt *struc);
int						executer(t_parse *node, t_prompt *struc);

#endif