/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:51:39 by vvazzs            #+#    #+#             */
/*   Updated: 2025/10/12 23:13:50 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../sigma_minishell.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/wait.h>
# include <signal.h>





int						parsing(char *str);
int						is_builtin(char *cmd);
void	reset_heredoc_flags(t_binary *tree);
int						builtin_cd(char **args);
int						builtin_pwd(void);
int						builtin_echo(char **args);
int						builtin_exit(char **args, char **envp);
int						builtin_unset(char **args);
int						exec_builtin(char *cmd, char **args, char **envp);
int						builtin_export(char **args);
int						exec_path(char *cmd, char **args, char **envp);
int						exec_tree(t_binary *tree, char **args, char **envp);
int						exec_pipes(t_cmds *cmd, char **env);
int						exec_redirections(t_cmds *cmd);
int						has_redir(t_cmds *cmd);
int						print_linux_env_list(void);
int						add_temp_var(const char *str);
int						update_shell_level(int amount);
int						make_update_env(const char *str);
int						am_i_truly_myself(const char *cmd);
int						has_builtin(t_cmds *cmd);
int						is_redir_token(const char *s);
int						count_tokens(t_cmds *cmd);
int						check_path_access(char *path, char *cmd);
int						is_system_path_command(char *cmd, char **envp);
int						exec_system_path(char *cmd, char **args, char **envp);
int						count_it(char *str, int c);
int						add_new_env_var(t_os_envs **env_list, const char *str);
int						exec_single_cmd_aux(t_cmds *cmd);
bool					is_n_flag(const char *arg);
void					init_tree(char **mat);
void					export_print_env_list(void);
void					free_matrix(char **table);
void					builtin_env(char **env);
void					initialize_pwd(char **envp);
void					handle_sigint(int sig);
void					update_env_var(const char *key, const char *value);
void					discard_heredoc(t_infile *infiles);
void					init_shell_meta(void);
void					enhanced_sorting_stoled_from_jlima(t_os_envs *envs);
void					my_ffprintf(char *cmd, char *which_message);
void					expand_args(t_cmds *cmd);
void					prepare_for_exec(void);
void					clear_env_list(void);
void					rebuild_env_list(t_os_envs **env_list, char **env_vars);
void					free_env_list(t_os_envs *head);
char					*aspas(char *str, int c);
char					*remove_it(char *str, int c);
char					*remove_aspas(char *str);
char					*find_path(char **envp, char *which_env);
char					*find_path_in_list(t_os_envs *env_list,
							const char *key);
char					*get_env_var(char *name, char **envp);
char					*logical_pwd_update(const char *oldpwd,
							const char *target);
char					**array_to_exec(t_cmds *cmd);
char					**list_to_char(t_os_envs *envs);
char					**get_paths_to_search(char **envp);
char					**split_path(char **envp);
t_binary				*btree(void);
t_os_envs				**get_env_list(void);
t_os_envs				*create_env_node(char *path);
void					handle_quit(int sig);
void					process_all_heredocs(t_infile *in, int fd[2]);
int						is_numeric(const char *s);
int						add_new_env_var(t_os_envs **env_list, const char *str);
int						make_update_env(const char *str);
size_t					get_env_key_length(const char *str);
int						make_update_env_aux(t_os_envs **env_list,
							const char *str, size_t len);
int						handle_heredoc(t_cmds *cmd);
int						handle_regular_redirections(t_cmds *cmd);
void					pid_equal_zero_double(t_cmds *cmd, int p[2]);
int						exec_single_left(t_infile *in);
int						exec_out_redirections(t_outfile *out);
int						exec_double_left(t_infile *in, t_cmds *cmd);
void					buildup_new_args(char *cmd, char **envp);
int						handle_absolute_path_cmd(char *cmd, char **args,
							char **envp);
int						handle_slash_command(char *cmd, char **args,
							char **envp);
int						handle_non_slash_commands(char *cmd, char **args,
							char **envp);
int						has_heredocs(t_cmds *cmd);
int						process_command(t_cmds *cmd, int *first_fd, char **env);
void					print_cmds(t_cmds *cmds);
int						process_heredocs_and_checks(t_cmds *cmd);
void					get_single_heredoc(char *eof, int fd[2]);
char					*expand_hd(char *str);
void					expand_infiles(t_infile *infile);
void					expand_outfiles(t_outfile *outfile);
void					check_commands(char *cmd);
char					**buildup_path(t_cmds *cmd, char **args, char **envp);
int						ensure_outfile(t_outfile *out);
int						check_infiles(t_cmds *cmds);
int						check_cmds(t_cmds *cmds, char **args, char **envp);
int						check_outfiles(t_cmds *cmds);
void					double_helper(int status, int p[2], pid_t pid);
void					handle_parent(pid_t pid, int shell_should_ignore);
void					prepare_signals_and_fork(t_cmds *cmd);
int						exec_subshell(t_binary *subshell, char **args,
							char **envp);
int						cmd_has_heredoc(t_cmds *cmd);
int						is_cmd_valid(t_cmds *cmd, char **args, char **envp);
void					children_killer(int status);
int						process_command_heredocs(t_cmds *cmd);
void	megalodon_giga_chad_exit(int status, int flag);
int	pipes_builtin_exit(char **args, char **envp);
void	child_services(char **cleaned_cmd, char **envp, int status);
void	file_descriptor_closer(int fd[2]);
int	get_heredoc_fd(t_cmds *cmd);
char	**expand_matrix(t_cmds *cmd);
void	heredoc_setup(void);
void	write_heredoc_line(char *str, int fd[2]);
void	process_heredoc_lines(char *delimiter, int len, int fd[2]);
void	setup_signals_for_parent(void);
void	handle_heredoc_child(t_infile *in, int *p);
int	super_checker_goated(t_cmds *cmd, char *command, char **args);
int	exec_single_cmd(t_cmds *cmd);
int	check_helper(t_cmds *cmd, int *please);
void	reset_heredoc_flags(t_binary *tree);
void	help_to_process(t_cmds *cmd, int p[2]);




// struct_clear.c
void					binary_clear(t_binary *binary);
void					cmds_clear(t_cmds *cmds);
void					outfile_clear(t_outfile *outfile);
void					infile_clear(t_infile *infile);
void					wild_clear(t_wild *node);
void	sig_handle_heredoc_main(int sig);
int manage_heredocs(t_cmds *cmd);

// struct_new.c
t_binary				*binary_new(int shlvl, t_type type, t_binary *up,
							t_cmds *table);
t_cmds					*cmds_new(t_outfile *outfile, t_infile *infile,
							char **cmd);
t_outfile				*outfile_new(char *file, char *token);
t_infile				*infile_new(char *file, char *token);
t_wild					*wild_new(char *file, char d_type);

void					create_binary_tree(char **mat, int shlvl,
							t_binary *tree);
t_outfile				*get_outfile(char **mat);
t_cmds					*get_cmds(char **mat);
void					create_binary_tree(char **mat, int shlvl,
							t_binary *tree);
int						open_parethesis(char **mat);
void					*create_binary_lvl(char **mat, int id, t_binary *tree);

int						find_tokens(char *str, t_token tokens);

// wildcards.c
char					**bind_mat_lst(char **mat, int count, t_wild *head,
							int ind);
t_wild					*get_pattern(t_wild *head, char **pattern,
							char **limit);
void					remove_null(t_wild **head, t_wild *node, t_wild *next);
void					remove_non_start(t_wild **head, char *start, int len);
t_wild					*read_dir(char *dir, t_wild *head, char *start);
char					**wildcards(char **mat, int count, int flag);
void					remove_non_end(t_wild **head, char *end);
void					add_wild_back(t_wild **lst, t_wild *new);
int						hidden_files(char *file, char *start);
int						simple_syntax(char **mat);
void					sort_wild(t_wild *wild1);
void					quote_matrix(char **mat);
int						wildsize(t_wild *head);

// expansions.c
char					*expand(char *str, int ind, int count, int flag);
char					*quote(char *str);

// syntax_error_msg.c
void					syntax_error_msg(char *str);

// get_pattern.c
t_outfile				*get_outfile(char **mat);
t_infile				*get_infile(char **mat);
int						find_pipe(char **mat);

// check_syntax.c
int						check_syntax(char **mat, t_token tokens);

//
int						parsing_strlen(char *str, t_token tokens, char **sep);
int						word_count(char *str, t_token tokens, char **sep);

// future libft.h
char					*ft_matnstr(char **matrix, char *s, int n);
void					ft_matrix_uni(char **dest, char **src);

void					get_here_doc(char *eof, int fd[2]);

void					set_to_onethirty(int sig);
void					sig_handle_heredoc(int sig);
int						restart_signals(void);
void					free_os_envs(void);

#endif
