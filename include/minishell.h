/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schouite <schouite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:07:13 by azaytsev          #+#    #+#             */
/*   Updated: 2026/05/18 10:30:45 by schouite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE 200809L
# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_APPEND,
}								t_token_type;

typedef enum e_quote_state
{
	DEFAULT,
	IN_SQUOTE,
	IN_DQUOTE,
}								t_quote_state;

typedef struct s_pipe
{
	int							prev_pipe;
	int							pfd[2];
}								t_pipe;

typedef struct s_gc
{
	void						*ptr;
	struct s_gc					*next;

}								t_gc;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef struct s_redir
{
	t_token_type				type;
	char						*file;
	int							heredoc_quoted;
	char						*heredoc_content;
	struct s_redir				*next;
}								t_redir;

typedef struct s_hd_line
{
	char						*text;
	struct s_hd_line			*next;
}								t_hd_line;

typedef struct s_hd_ctx
{
	t_hd_line					*head;
	t_hd_line					*tail;
	size_t						total;
}								t_hd_ctx;

typedef struct s_cmd
{
	char						**args;
	t_redir						*redirs;
	pid_t						pid;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_shell
{
	t_env						*env;
	int							exit_status;
	int							running;
	t_gc						*gc;
}								t_shell;

extern volatile sig_atomic_t	g_signal;

t_env							*env_new_node(const char *key,
									const char *value);
void							env_add_back(t_env **env, t_env *new_node);
t_env							*env_init(char **envp);
char							*env_get(t_env *env, const char *key);
int								env_set(t_env **env, const char *key,
									const char *value);
int								env_unset(t_env **env, const char *key);
char							**env_to_array(t_env *env);
int								env_size(t_env *env);
void							free_env(t_env *env);
void							free_str_array(char **arr);
void							print_error(const char *context,
									const char *message);
void							debug_print_tokens(t_token *tokens);
void							debug_print_cmds(t_cmd *cmds);
void							debug_print_env(t_env *env);
void							setup_signals_interactive(void);
void							setup_signals_exec(void);
void							setup_signals_child(void);
void							setup_signals_heredoc(void);
int								builtin_pwd(t_shell *shell, char **args);
int								builtin_env(t_shell *shell, char **args);
int								builtin_echo(t_shell *shell, char **args);
int								builtin_exit(t_shell *shell, char **args);
int								builtin_unset(t_shell *shell, char **args);
int								builtin_cd(t_shell *shell, char **args);
int								builtin_export(t_shell *shell, char **args);
int								export_print(t_shell *shell);
int								init_shell(t_shell *shell, int argc,
									char **argv, char **envp);
void							shell_loop(t_shell *shell);
void							cleanup_shell(t_shell *shell);
t_token							*lex(t_shell *shell, char *line);
t_token_type					set_type(t_token *new_node);
bool							lex_operator(t_shell *shell, t_token **token,
									char *line, int *i);
bool							lex_word(t_shell *shell, t_token **token,
									char *line, int *i);
bool							is_operator(char c);
void							lstadd_back_token(t_token **lst, t_token *new);
int								syntax_check(t_token *tokens);
t_cmd							*parse(t_shell *shell, t_token *tokens);
t_cmd							*cmd_new(t_shell *shell);
void							cmd_add_back(t_cmd **list, t_cmd *new_cmd);
int								is_redir_type(t_token_type type);
int								count_cmd_args(t_token *tokens);
int								parse_redir(t_shell *shell, t_token **cur,
									t_redir **redirs);
t_redir							*create_redir(t_shell *shell, t_token_type type,
									const char *file_val);
t_cmd							*expand(t_cmd *cmds, t_shell *shell);
int								expand_args(t_cmd *cmd, t_shell *shell);
int								field_has_quotes(const char *str);
int								field_count_words(char *str);
int								field_append_words(t_shell *shell, char **args,
									int *j, char *str);
char							*expand_str(const char *str, t_shell *shell);
char							*resolve_dollar(const char *str, int *i,
									t_shell *shell);
char							*char_to_str(t_shell *shell, char c);
char							*emit_one(t_shell *shell, char c, int nosplit);
char							*escape_ws(t_shell *shell, const char *src);
void							unescape_ws(char *s);
char							*gc_strjoin(t_shell *shell, char const *s1,
									char const *s2);
size_t							calculate_len(char **tab_path);
char							*is_valid_pathname(char **tab_pathname);
char							**make_pathname(t_shell *shell, t_cmd *cmd);
bool							run_executor(t_shell *shell, t_cmd *cmd);
int								run_redir(t_redir *redirs, int fd);
bool							is_builtin(t_cmd *cmd);
int								run_builtin(t_shell *shell, t_cmd *cmd,
									t_cmd *header);
bool							handle_executor(t_shell *shell, t_cmd *cmd);
void							wait_all(t_shell *shell, t_cmd *cmd);
char							*is_valid_cmd(t_shell *shell, t_cmd *cmd);
void							child_exit_error(t_shell *shell, char *name);
bool							setup_pipe(t_shell *shell, t_cmd *cmd,
									t_pipe *pipe_ctx);
int								run_noargs(t_shell *shell, t_cmd *cmd);
char							*read_line_fd(int fd);
int								collect_heredocs(t_cmd *cmds, t_shell *shell);
void							warn_heredoc_eof(const char *delim);
char							*hd_finalize(t_shell *shell, t_hd_ctx *ctx);
int								push_heredoc_line(t_shell *shell,
									t_redir *redir, char *line, t_hd_ctx *ctx);
int								apply_heredoc(t_redir *redir);
#endif
