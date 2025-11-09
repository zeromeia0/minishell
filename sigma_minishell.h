/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigma_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:59:13 by vvazzs            #+#    #+#             */
/*   Updated: 2025/11/09 01:44:56 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGMA_MINISHELL_H
# define SIGMA_MINISHELL_H

# include "parse/jojo_libft/libft.h"
# include "typedef.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include "exec/minishell.h"

int			parsing(char *str);
int			is_builtin(char *cmd);
void		reset_heredoc_flags(t_binary *tree);
int			builtin_cd(char **args);
int			builtin_pwd(void);
int			builtin_echo(char **args);
int			builtin_exit(char **args, char **envp);
int			builtin_unset(char **args);
void		write_dolar_home(char **envp);
int			exec_builtin(char *cmd, char **args, char **envp);
int			builtin_export(char **args);
int			exec_path(char *cmd, char **args, char **envp);
int			exec_tree(t_binary *tree, char **args, char **envp);
int			exec_pipes(t_cmds *cmd, char **env);
int			has_redir(t_cmds *cmd);
int			print_linux_env_list(void);
int			add_temp_var(const char *str);
int			update_shell_level(int amount);
int			make_update_env(const char *str);
int			am_i_truly_myself(const char *cmd);
int			has_builtin(t_cmds *cmd);
int			is_redir_token(const char *s);
int			count_tokens(t_cmds *cmd);
int			check_path_access(char *path, char *cmd);
int			is_system_path_command(char *cmd, char **envp);
int			exec_system_path(char *cmd, char **args, char **envp);
int			count_it(char *str, int c);
int			add_new_env_var(t_os_envs **env_list, const char *str);
int			exec_single_cmd_aux(t_cmds *cmd);
bool		is_n_flag(const char *arg);
void		init_tree(char **mat);
void		export_print_env_list(void);
void		free_matrix(char **table);
void		builtin_env(char **env);
void		initialize_pwd(char **envp);
void		handle_sigint(int sig);
void		update_env_var(const char *key, const char *value);
void		discard_heredoc(t_infile *infiles);
void		init_shell_meta(void);
void		enhanced_sorting_stoled_from_jlima(t_os_envs *envs);
void		my_ffprintf(char *cmd, char *which_message);
void		expand_args(t_cmds *cmd);
void		prepare_for_exec(void);
void		clear_env_list(void);
void		rebuild_env_list(t_os_envs **env_list, char **env_vars);
void		free_env_list(t_os_envs *head);
char		*aspas(char *str, int c);
char		*remove_it(char *str, int c);
void		remove_aspas(char *dest, const char *src);
char		*find_path(char **envp, char *which_env);
char		*find_path_in_list(t_os_envs *env_list, const char *key);
char		*get_env_var(char *name, char **envp);
char		*logical_pwd_update(const char *oldpwd, const char *target);
char		**array_to_exec(t_cmds *cmd);
char		**list_to_char(t_os_envs *envs);
char		**get_paths_to_search(char **envp);
char		**split_path(char **envp);
t_binary	*btree(void);
t_os_envs	**get_env_list(void);
t_os_envs	*create_env_node(char *path);
void		handle_quit(int sig);
void		process_all_heredocs(t_infile *in, int fd[2]);
int			is_numeric(const char *s);
int			add_new_env_var(t_os_envs **env_list, const char *str);
int			make_update_env(const char *str);
size_t		get_env_key_length(const char *str);
int			make_update_env_aux(t_os_envs **env_list, const char *str,
				size_t len);
int			handle_heredoc(t_cmds *cmd);
int			handle_regular_redirections(t_cmds *cmd);
void		pid_equal_zero_double(t_cmds *cmd, int p[2]);
int			exec_out_redirections(t_outfile *out);
int			exec_double_left(t_infile *in, t_cmds *cmd);
void		buildup_new_args(char *cmd, char **envp);
int			handle_absolute_path_cmd(char *cmd, char **args, char **envp);
int			handle_slash_command(char *cmd, char **args, char **envp);
int			handle_non_slash_commands(char *cmd, char **args, char **envp);
int			has_heredocs(t_cmds *cmd);
int			process_command(t_cmds *cmd, int *first_fd, char **env);
void		print_cmds(t_cmds *cmds);
int			process_heredocs_and_checks(t_cmds *cmd);
void		get_single_heredoc(char *eof, int fd[2]);
char		*expand_hd(char *str);
void		expand_infiles(t_infile *infile);
void		expand_outfiles(t_outfile *outfile);
int			ensure_outfile(t_outfile *out);
int			check_infiles(t_cmds *cmds);
int			check_cmds(t_cmds *cmds, char **args, char **envp);
int			check_outfiles(t_cmds *cmds);
void		double_helper(int status, int p[2], pid_t pid);
void		handle_parent(pid_t pid, int shell_should_ignore);
void		prepare_signals_and_fork(t_cmds *cmd);
int			exec_subshell(t_binary *subshell, char **args, char **envp);
int			cmd_has_heredoc(t_cmds *cmd);
int			is_cmd_valid(t_cmds *cmd, char **args, char **envp);
void		exec_child(t_cmds *cmd);
void		children_killer(int status);
int			process_command_heredocs(t_cmds *cmd);

// struct_clear.c
void		binary_clear(t_binary *binary);
void		cmds_clear(t_cmds *cmds);
void		outfile_clear(t_outfile *outfile);
void		infile_clear(t_infile *infile);
void		wild_clear(t_wild *node);
void		sig_handle_heredoc_main(int sig);
int			manage_heredocs(t_cmds *cmd);
char		*single_expand(char *s, int i, int count);
void		single_error_msg(char wc);

// struct_new.c
t_binary	*binary_new(int shlvl, t_type type, t_binary *up, t_cmds *table);
t_cmds		*cmds_new(t_outfile *outfile, t_infile *infile, char **cmd);
t_outfile	*outfile_new(char *file, char *token);
t_infile	*infile_new(char *file, char *token);
t_wild		*wild_new(char *file, char d_type);

void		create_binary_tree(char **mat, int shlvl, t_binary *tree);
t_outfile	*get_outfile(char **mat);
t_cmds		*get_cmds(char **mat);
void		create_binary_tree(char **mat, int shlvl, t_binary *tree);
int			open_parethesis(char **mat);
void		*create_binary_lvl(char **mat, int id, t_binary *tree);
int			find_tokens(char *str, t_token tokens);

// wildcards.c
char		**bind_mat_lst(char **mat, int count, t_wild *head, int ind);
t_wild		*get_pattern(t_wild *head, char **pattern, char **limit);
void		remove_null(t_wild **head, t_wild *node, t_wild *next);
void		remove_non_start(t_wild **head, char *start, int len);
t_wild		*read_dir(char *dir, t_wild *head, char *start);
char		**wildcards(char **mat, int count, int flag);
void		remove_non_end(t_wild **head, char *end);
void		add_wild_back(t_wild **lst, t_wild *new);
int			hidden_files(char *file, char *start);
int			simple_syntax(char **mat);
void		sort_wild(t_wild *wild1);
void		quote_matrix(char **mat);
int			wildsize(t_wild *head);

// expansions.c
char		*expand(char *str, int ind, int count, int flag);
char		*quote(char *str);

// syntax_error_msg.c
void		syntax_error_msg(char *str);

// get_pattern.c
t_outfile	*get_outfile(char **mat);
t_infile	*get_infile(char **mat);
int			find_pipe(char **mat);

// check_syntax.c
int			check_syntax(char **mat, t_token tokens);

int			parsing_strlen(char *str, t_token tokens, char **sep);
int			word_count(char *str, t_token tokens, char **sep);

// future libft.h
char		*ft_matnstr(char **matrix, char *s, int n);
void		ft_matrix_uni(char **dest, char **src);

void		get_here_doc(char *eof, int fd[2]);

void		set_to_onethirty(int sig);
void		sig_handle_heredoc(int sig);
int			restart_signals(void);
void		free_os_envs(void);
void		rm_quote(char *dest, char *src);

#endif