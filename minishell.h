/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:13:26 by mkoller           #+#    #+#             */
/*   Updated: 2023/01/31 10:59:01 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
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
# define PROMPT "\001\033[1;92m\002minishell $> \033[0;37m"
# define USER "USER"

struct	s_env_list;
struct	s_read_input;
typedef struct s_parse
{
	char				**full_cmd;
	char				*full_path;
	char				*heredoc;
	struct s_parse		*next;
	int					in;
	int					out;
	struct s_env_list	*env;
	int					exit_status;
}						t_parse;

typedef struct s_prompt
{
	t_parse				*cmds;
	struct s_env_list	*env_lst;
	pid_t				pid;
	int					exit_flag;
	int					exit_return_val;
	int					rand;
	struct s_read_input	*input;
}						t_prompt;

typedef struct s_read_input
{
	char				*str;
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

typedef struct s_global
{
	int					exit_status;
}						t_global;

////put_to_table
//free_suff.c
void					free_prompt(t_prompt *struc);
void					free_table(char **table);
void					clean_interrupt(t_env_list *env_lst,
							t_input *input, t_prompt *struc);
void					clean_exit(t_prompt *struc, t_input *input);
void					clean_loop(t_prompt *struc, t_input *input);
//init_suff.c
void					init_prompt(t_prompt *struc, t_env_list *env_lst);
void					init_node(t_parse *node);
void					free_heredoc(t_parse *cmds);
void					unlink_all(t_prompt *struc);
//put_to_table_helper.c
int						count_pipes(char **split);
int						count_redirect(char **split);
int						pointer_count(char **str, int *i);
void					put_table_non_pipe(char **str, t_parse *temp, int *i,
							int *j);
void					put_table_pipe(char **str, t_parse *temp, int *k,
							int *i);
//put_to_table_helper2.c
void					check_exit_flag(t_prompt *struc,
							t_input *input);
void					set_env_lst(t_env_list *env_lst,
							t_parse *temp, t_prompt *struc);
//put_to_table.c
void					put_to_table(char **str, t_prompt *struc);
void					add_nodes(t_prompt *struc, int ammount);
char					**copie_env(char **env);
char					**trim_2d_array(char **table);
void					trim_nodes(t_prompt *struc);
////builtin
// built_path.c
char					*find_command(char **env_path, char *cmd,
							char *full_path);
void					trim_full_cmd(t_parse *node);
int						build_path(t_parse *node);
// builtin_check_and_execute.c
void					exec_cmd(t_parse *node, t_prompt *struc, int to_fork);
int						builtin(t_parse *node, t_prompt *struc);
int						is_bultin(t_parse *node);
void					cmd_exec(t_parse *node, t_prompt *struc, int to_fork);
// execute_and_file_error.c
void					error_to_fd(int fd, char *path, DIR *folder);
int						error_message(char *path);
//execute_helpter.c
int						ft_strchr_int(const char *s, int c);
char					**env_list_to_array(t_env_list *env_lst);
void					dup_fds(t_parse *node);
void					update_exit_status(void);
// executer.c
void					do_parent(int *fd, int *backup);
void					do_child(t_parse *node, t_prompt *struc, int *fd,
							int *backup);
void					wait_loop(t_parse *temp);
int						piper(t_parse *node, t_prompt *struc, int backup);
void					executer(t_parse *node, t_prompt *struc);
////echo
//echo.c
int						line_count(char **str);
int						only_n(char *str);
void					put_to_stdout_extend(t_parse *node,
							int *i, int *flag, int *k);
void					put_to_stdout(t_parse *node, int *i);
int						do_echo(t_parse *node);
//prepare_filedescriptors.c
void					check_dup_out(t_parse *node);
void					check_dup_in(t_parse *node);
void					restore_stdout(int saved);
void					restore_stdin(int saved);
////env_export
// do_env_stuff.c
int						do_unset(t_parse *node);
int						do_export(t_parse *node);
int						do_env(t_parse *node);
// env_replace_helper.c
int						not_dollar(char *arg, int i);
char					*get_new_str_env(char *str, char *envvar, char *ptr);
int						is_end_of_env(char c, char *ptr, int i);
int						get_new_strlen_env(char *str, char *value, char *ptr);
//env_replace.c
void					update_full_cmd(t_parse *node, char *name,
							char *dollar_pos, int *i);
void					include_env_node(t_parse *node);
void					include_env_struc(t_prompt *struc);
char					*get_env_name(char *arg, t_env_list *env_lst);
//expand_tilde.c
char					*get_env_tilde_value(t_env_list *env);
char					*get_new_str_tilde(char *str, char *envvar, char *ptr);
void					expand_tilde_node(t_parse *node);
void					expand_tilde_struc(t_prompt *struc);
char					*get_new_str_exitstatus(char *str, char *envvar,
							char *ptr);
//shell_level.c
int						invalid_lvl(const char *str);
int						get_shelvl(t_env_list *env_lst);
void					shell_level_plus_one(t_prompt *struc);
////export_fucntions
// export_change_get_fill.c
void					fill_env_lst(t_env_list **env_lst, char **envp);
char					*get_env_value(t_env_list *env_lst, char *name);
int						changevalue(t_env_list *env_lst, char *name_value);
//export_print_add.c
void					print_env_list(t_env_list *env_lst);
void					print_export_list(t_env_list *env_lst);
int						is_valid_env(const char *env);
int						add_env_entry(t_env_list *env, char *str);
int						add_env_no_value(t_env_list *env, char *str);
//export_sort_dup_delete.c
void					delete_env_value(t_env_list *env_lst, char *name);
void					free_env_lst(t_env_list *env_lst);
t_env_list				*duplicate_list(t_env_list *env_lst, t_env_list *new);
t_env_list				*sort_list_alphabetically(t_env_list *env_lst);
//export.c
int						export_env_helper(char *name, int *i, t_env_list *env,
							char **args);
int						export_env(t_env_list *env, char **args);
void					export_not_valid(char *str);
int						export_helper(t_env_list *env, char **args);
int						export(t_parse *node);
////fd_redirections
//fd_redirect_in_helper.c
int						ft_strncmp_special(const char *s1, const char *s2,
							size_t n);
void					print_file_error(char **str, int i);
int						fd_in_helper(t_parse *temp, int *i, t_prompt *struc);
void					heredoc_helper(char *temp, char *str[2]);
int						check_heredoc_error(t_parse *temp, int *i);
//fd_redirect_in.c
char					*heredoc(char *limit);
int						create_trunc_in(t_parse *temp, int *i);
int						heredoc_file(t_parse *node, t_prompt *struc);
int						get_all_fd_in(t_prompt *struc);
//heredoc_helper.c
int						create_heredoc_space(t_parse *temp, int *i);
int						create_heredoc_no_space(t_parse *temp, int *i);
int						create_heredoc(t_parse *temp, int *i);
//fd_redirect_in_helper2.c
void					print_warning(char *limit);
//fd_redirect_out_helper.c
int						trim_white(t_parse *node);
void					append_out_case1(char *old, t_parse *temp, int *i);
void					append_out_case2(char *old, t_parse *temp, int *i);
void					trunc_out_case1(char *old, t_parse *temp, int *i);
void					trunc_out_case2(char *old, t_parse *temp, int *i);
//fd_redirect_out.c
int						check_name(t_parse *temp, int *i);
int						check_valid_filename(t_parse *node);
int						create_append_out(t_parse *temp, int *i);
int						get_all_fd_out(t_prompt *struc);
////pwd_cd
//cd.c
void					cd_path_not_found(char *path);
int						cd_into_home(t_parse *node);
void					do_cd(t_parse *node);
//pwd.c
int						pwd(void);
int						do_pwd(t_parse *node);
void					pwd_init(t_parse *node);
void					update_pwd(t_parse *node);
////quotes
// delete_closed_quotes.c
int						new_len_no_quotes(char *str);
char					*delete_closed_quotes_str(char *str, int s_quotes,
							int d_quotes);
void					delete_closed_quotes_node(t_parse *node);
void					delete_closed_quotes_struc(t_prompt *struc);
//in_quotes_helper.c
int						check_not_in_d_quotes_inpos(char *str, int *double_q);
int						check_not_in_s_quotes_inpos(char *str, int *single_q);
int						check_not_in_s_quotes(char *str, char *pos);
//in_quotes.c
int						check_not_in_d_quotes(char *str, char *pos);
int						check_pos_not_in_quotes(char *str, char *pos);
int						check_pos_not_in_quotes_test(char *str, char *pos);
char					*find_unquoted_char(char *str, char c);
char					*find_not_in_squoutes_char(char *str, char c);
////split_input
//parse_input_helper.c
void					open_close_quotes(t_input *input, int i);
int						ft_check_str_count(t_input *input);
int						ft_strlen_sep(t_input *input, int i);
//pasre_input.c
char					*ft_word(t_input *input, int i);
void					split_input_helper(t_input *input, int *i, int *j);
void					ft_split_input(t_input *input);
// prepare_input_string_helper.c
int						prepare_input_string_do(char **str, int *i);
char					*prepare_input_string(char *str);
int						check_lastpos_is_space(char *str, int i);
int						check_nextpos_is_space(char *str, int i);
// prepare_input_string.c
int						check_if_qoute(int *single_q, int *double_q, char c);
char					*add_space_before_this_position(char *str, int *index);
char					*add_space_after_this_position(char *str, int *index);
int						check_if_unquoted_special_char(char *str, int j,
							int *s_q, int *d_q);
////error_wrapper_signals
// error.c
void					error_command_not_found(t_parse *node);
int						check_error(t_parse *node);
void					put_error(char *str);
// exit.c
int						ft_strisnum(char *str);
void					do_exit(t_prompt *struc, t_parse *node);
//signals.c
void					ctrl_d(int sig);
void					restore_prompt(int sig);
void					ctrl_c(int sig);
void					back_slash(int sig);
void					run_signals(int sig);
//wrapwer.c
void					wrapper_fork(int *pid);
void					wrapper_pipe(int *fd);
void					wrapper_dup2(int *old_fd, int new_fd);
void					wrapper_close(int *fd);
void					wrapper_wait(int *status);
//minishell.c
int						read_line_take_input(t_env_list *env_lst, \
						t_input *input, t_prompt *struc);
int						process_intput(t_prompt *struc, t_env_list *env_lst,
							t_input *input);
int						minishell(t_prompt *struc, t_env_list *env_lst);

#endif